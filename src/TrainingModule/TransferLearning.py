# %%

# %env CUDA_VISIBLE_DEVICES=2
import sys

import torch
from torchvision import datasets, models, transforms
import torch.nn as nn
import torch.optim as optim
from torch.utils.data import DataLoader
import time
import numpy as np
import matplotlib.pyplot as plt
import os
#import shutil

from PIL import Image


def train_and_validate(model, loss_criterion, optimizer, epochs):
    """
    Function to train and validate
    Parameters
        :param model: Model to train and validate
        :param loss_criterion: Loss Criterion to minimize
        :param optimizer: Optimizer for computing gradients
        :param epochs: Number of epochs (default=13)

    Returns
        model: Trained Model with best validation accuracy
        history: (dict object): Having training loss, accuracy and validation loss, accuracy
    """

    history = []

    for epoch in range(epochs):
        epoch_start = time.time()
        print("Epoch: {}/{}".format(epoch + 1, epochs), file=file_log)

        # Set to training mode
        model.train()

        # Loss and Accuracy within the epoch
        train_loss = 0.0
        train_acc = 0.0

        valid_loss = 0.0
        valid_acc = 0.0

        for i, (inputs, labels) in enumerate(train_data_loader):
            inputs = inputs.to(device)
            labels = labels.to(device)

            # Clean existing gradients
            optimizer.zero_grad()

            # Forward pass - compute outputs on input data using the model
            outputs = model(inputs)

            # Compute loss
            loss = loss_criterion(outputs, labels)

            # Backpropagate the gradients
            loss.backward()

            # Update the parameters
            optimizer.step()

            # Compute the total loss for the batch and add it to train_loss
            train_loss += loss.item() * inputs.size(0)

            # Compute the accuracy
            ret, predictions = torch.max(outputs.data, 1)
            correct_counts = predictions.eq(labels.data.view_as(predictions))

            # Convert correct_counts to float and then compute the mean
            acc = torch.mean(correct_counts.type(torch.FloatTensor))

            # Compute total accuracy in the whole batch and add to train_acc
            train_acc += acc.item() * inputs.size(0)

            print("Batch number: {:03d}, Training: Loss: {:.4f}, Accuracy: {:.4f}".format(i, loss.item(), acc.item()),
                  file=file_log)

        # Validation - No gradient tracking needed
        with torch.no_grad():

            # Set to evaluation mode
            model.eval()

            # Validation loop
            for j, (inputs, labels) in enumerate(valid_data_loader):
                inputs = inputs.to(device)
                labels = labels.to(device)

                # Forward pass - compute outputs on input data using the model
                outputs = model(inputs)

                # Compute loss
                loss = loss_criterion(outputs, labels)

                # Compute the total loss for the batch and add it to valid_loss
                valid_loss += loss.item() * inputs.size(0)

                # Calculate validation accuracy
                ret, predictions = torch.max(outputs.data, 1)
                correct_counts = predictions.eq(labels.data.view_as(predictions))

                # Convert correct_counts to float and then compute the mean
                acc = torch.mean(correct_counts.type(torch.FloatTensor))

                # Compute total accuracy in the whole batch and add to valid_acc
                valid_acc += acc.item() * inputs.size(0)

                print(
                    "Validation Batch number: {:03d}, Validation: Loss: {:.4f}, Accuracy: {:.4f}".format(j, loss.item(),
                                                                                                         acc.item()),
                    file=file_log)

        # Find average training loss and training accuracy
        avg_train_loss = train_loss / train_data_size
        avg_train_acc = train_acc / train_data_size

        # Find average training loss and training accuracy
        avg_valid_loss = valid_loss / valid_data_size
        avg_valid_acc = valid_acc / valid_data_size

        history.append([avg_train_loss, avg_valid_loss, avg_train_acc, avg_valid_acc])

        epoch_end = time.time()

        print(
            "Result of Epoch {}: \n\tTraining: Loss: {:.4f}, Accuracy: {:.4f}%, \n\tValidation : Loss : {:.4f}, Accuracy: {:.4f}%, Time: {:.4f}s\n".format(
                epoch + 1, avg_train_loss, avg_train_acc * 100, avg_valid_loss, avg_valid_acc * 100,
                epoch_end - epoch_start), file=file_log)

    # Save the model for Python
    torch.save(model, folderName + '/' + dataset_name + '_model_python' + '.pt')

    # Save the model for C++
    traced_script_module = torch.jit.trace(model, torch.rand(1, 3, 224, 224))
    traced_script_module.save(folderName+'/'+dataset_name + '_model' + '.pt')

    return model, history


def computeTestSetAccuracy(model, loss_criterion):
    """
    Function to compute the accuracy on the test set
    Parameters
        :param model: Model to test
        :param loss_criterion: Loss Criterion to minimize
    """

    device = torch.device("cpu")

    test_acc = 0.0
    test_loss = 0.0

    # Validation - No gradient tracking needed
    with torch.no_grad():
        # Set to evaluation mode
        model.eval()

        # Validation loop
        for j, (inputs, labels) in enumerate(test_data_loader):
            inputs = inputs.to(device)
            labels = labels.to(device)

            # Forward pass - compute outputs on input data using the model
            outputs = model(inputs)

            # Compute loss
            loss = loss_criterion(outputs, labels)

            # Compute the total loss for the batch and add it to valid_loss
            test_loss += loss.item() * inputs.size(0)

            # Calculate validation accuracy
            ret, predictions = torch.max(outputs.data, 1)
            correct_counts = predictions.eq(labels.data.view_as(predictions))

            # Convert correct_counts to float and then compute the mean
            acc = torch.mean(correct_counts.type(torch.FloatTensor))

            # Compute total accuracy in the whole batch and add to valid_acc
            test_acc += acc.item() * inputs.size(0)

            print("Test Batch number: {:03d}, Test: Loss: {:.4f}, Accuracy: {:.4f}".format(j, loss.item(), acc.item()),
                  file=file_log)

    # Find average test loss and test accuracy
    avg_test_acc = test_acc / test_data_size

    print("Test accuracy : " + str(avg_test_acc), file=file_log)


def predict(model, test_image_name):
    """
    Function to predict the class of a single test image
    Parameters
        :param model: Model to test
        :param test_image_name: Test image

    """

    transform = image_transforms['test']

    test_image = Image.open(test_image_name)
    #plt.imshow(test_image)

    test_image_tensor = transform(test_image)

    test_image_tensor = test_image_tensor.view(1, 3, 224, 224)

    with torch.no_grad():
        model.eval()
        # Model outputs log probabilities
        out = model(test_image_tensor)
        ps = torch.exp(out)
        topk, topclass = ps.topk(5, dim=1)
        for i in range(5):
            print("Predcition", i + 1, ":", idx_to_class[topclass.cpu().numpy()[0][i]], ", Score: ",
                  topk.cpu().numpy()[0][i])


# Folder fot temp files
#folderName = '/home/dmitrii/AlexLens/resources'
dirpath = os.getcwd()
dirpath = dirpath[0:dirpath.rfind('/', 0, len(dirpath))]
dirpath = dirpath[0:dirpath.rfind('/', 0, len(dirpath))] #for Linux
folderName = dirpath + "/resources"
# Delete a folder
#shutil.rmtree(folderName, ignore_errors=True)

# Applying Transforms to the Data
image_transforms = {
    'train': transforms.Compose([
        transforms.RandomResizedCrop(size=256, scale=(0.8, 1.0)),
        transforms.RandomRotation(degrees=15),
        transforms.RandomHorizontalFlip(),
        transforms.CenterCrop(size=224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406],
                             [0.229, 0.224, 0.225])
    ]),
    'valid': transforms.Compose([
        transforms.Resize(size=256),
        transforms.CenterCrop(size=224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406],
                             [0.229, 0.224, 0.225])
    ]),
    'test': transforms.Compose([
        transforms.Resize(size=256),
        transforms.CenterCrop(size=224),
        transforms.ToTensor(),
        transforms.Normalize([0.485, 0.456, 0.406],
                             [0.229, 0.224, 0.225])
    ])
}

# Load the Data
# Set train and valid directory paths
# PATH!!!!!!!!
#dataset = '/Users/eismont/PycharmProjects/test/pse_dataset_test'
dataset = sys.argv[0] #for initialize
#dataset = sys.argv[1] #for syscall
dataset_name = dataset[dataset.rfind('/', 0, len(dataset)) + 1:len(dataset)]
folderName = folderName + '/' + dataset_name
if not(os.path.isdir(folderName)):
    os.makedirs(folderName)
file_log = open((folderName + '/' + dataset_name + '_log' + '.txt'), "w+")
file_labels = open((folderName + '/' + dataset_name + '_labels' + '.txt'), "w+")

train_directory = os.path.join(dataset, 'train')
valid_directory = os.path.join(dataset, 'valid')
test_directory = os.path.join(dataset, 'test')

# Batch size
bs = 32

# Number of classes
num_classes = len(os.listdir(valid_directory)) - 1

# Load Data from folders
data = {
    'train': datasets.ImageFolder(root=train_directory, transform=image_transforms['train']),
    'valid': datasets.ImageFolder(root=valid_directory, transform=image_transforms['valid']),
    'test': datasets.ImageFolder(root=test_directory, transform=image_transforms['test'])
}

# Get a mapping of the indices to the class names, in order to see the output classes of the test images.
idx_to_class = {v: k for k, v in data['train'].class_to_idx.items()}
labels = str(data['train'].classes)
while labels != ']':
    label = labels[
            labels.find("'", 0, len(dataset)) + 1:labels.find("'", labels.find("'", 0, len(dataset)) + 1, len(dataset))]
    labels = labels[labels.find("'", labels.find("'", 0, len(dataset)) + 1, len(dataset)) + 1:len(labels)]
    print(label, file=file_labels)
file_labels.close()

# Size of Data, to be used for calculating Average Loss and Accuracy
train_data_size = len(data['train'])
valid_data_size = len(data['valid'])
test_data_size = len(data['test'])

# Create iterators for the Data loaded using DataLoader module
train_data_loader = DataLoader(data['train'], batch_size=bs, shuffle=True)
valid_data_loader = DataLoader(data['valid'], batch_size=bs, shuffle=True)
test_data_loader = DataLoader(data['test'], batch_size=bs, shuffle=True)

# Load pretrained AlexNet Model
alexnet = models.alexnet(pretrained=True)

# Freeze model parameters
for param in alexnet.parameters():
    param.requires_grad = False

# Change the final layer of AlexNet Model for Transfer Learning
fc_inputs = alexnet.classifier[6].in_features

alexnet.classifier[6] = nn.Sequential(
    nn.Linear(fc_inputs, 4096),
    nn.ReLU(),
    nn.Dropout(0.4),
    nn.Linear(4096, num_classes),
    nn.LogSoftmax(dim=1)  # For using NLLLoss()
)

# Define Optimizer and Loss Function
loss_func = nn.NLLLoss()
optimizer = optim.Adam(alexnet.parameters())

device = torch.device("cpu")

# Train the model for 13 epochs
num_epochs = 1
trained_model, history = train_and_validate(alexnet, loss_func, optimizer, num_epochs)

file_log.close()

# torch.save(history, dataset+'_history.pt')

history = np.array(history)
plt.plot(history[:, 0:2])
plt.legend(['Train Loss', 'Validate Loss'])
plt.xlabel('Epoch Number')
plt.ylabel('Loss')
plt.ylim(0, 1)
plt.savefig(os.path.join(folderName, dataset_name + '_loss_curve.png'))
plt.clf()

plt.plot(history[:, 2:4])
plt.legend(['Train Accuracy', 'Validate Accuracy'])
plt.xlabel('Epoch Number')
plt.ylabel('Accuracy')
plt.ylim(0, 1)
plt.savefig(os.path.join(folderName, dataset_name + '_accuracy_curve.png'))


# Test a particular model on a test image
#model = torch.load(folderName + '/' + dataset_name + '_model' + '.pt')
#predict(model, 'shrimp.jpeg')

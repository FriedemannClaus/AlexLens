/**
* Project Entwurf_PSE_KNN
* @author Friedemann Claus
* @coauthor Viet Pham
* @version 1.2
*/


#include "NeuralNet.h"

/**
* NeuralNet implementation
*/

#include <iostream>
#include <fstream>
#include <iomanip>

#include <stdlib.h>
#include <vector>
#include <Eigen/Core>
#include "Layer.h"
#include "Conv2DLayer.h"
#include "FCLayer.h"
#include <list>

using namespace std;

void NeuralNet::init() {
    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

    //Weight Matrices:

    // Wheights for the conv-layers are stored in a matrix of matrices
    // A row of the outer matrix represents a kernel
    // For example a 11x11x3 kernel of the first conv-layer is represented as 3 11x11 matrices in one row (RGB in that case).
    // So conv1 is a matrix with width 3 (input depth/ kernel depth) and length 96 (kernels of Conv1).

    FourDMatrix conv1;

    // AlexNet (and therfore our weights) is built for two GPUs. The first Conv-Layer can be calculated as is, but the rest have to be split.
    // They are split in the kernel-dimension (Each gpu applies half of the kernels). So conv41 and conv42 have 192 kernels each instead of 384.
    // This results in two output-matrices with half the depth (two times 13x13x192 instead of 13x13x384).
    // So conv51 and conv52 therefore have kernels with depth 192 instead of 384.
    // Conv31 and Conv32 are exceptions to this, as they are calculated cross-gpu instead of parallel to the gpus.
    // So conv31 sees the output of conv21 AND of conv22 whereas conv51 only sees the output of conv41.
    // That's why we have to split the output-matrices of conv1, merge the outputmatrices of conv2 (and of conv5, because the fc-layers aren't parallelized too).
    FourDMatrix conv21;
    FourDMatrix conv22;
    FourDMatrix conv31;
    FourDMatrix conv32;
    FourDMatrix conv41;
    FourDMatrix conv42;
    FourDMatrix conv51;
    FourDMatrix conv52;

    // resize the 4d-Matrices accordingly
    int a;
    int b;
    conv1.resize(96, 3);
    for(a = 0; a < 96; a++) {
        for(b = 0; b < 3; b++) {
            conv1(a, b).resize(11, 11);
        }
    }

    conv21.resize(128, 48);
    for(a = 0; a < 128; a++) {
        for(b = 0; b < 48; b++) {
            conv21(a, b).resize(5, 5);
        }
    }

    conv22.resize(128, 48);
    for(a = 0; a < 128; a++) {
        for(b = 0; b < 48; b++) {
            conv22(a, b).resize(5, 5);
        }
    }

    conv31.resize(192, 256);
    for(a = 0; a < 192; a++) {
        for(b = 0; b < 256; b++) {
            conv31(a, b).resize(3, 3);
        }
    }

    conv32.resize(192, 256);
    for(a = 0; a < 192; a++) {
        for(b = 0; b < 256; b++) {
            conv32(a, b).resize(3, 3);
        }
    }

    conv41.resize(192, 192);
    for(a = 0; a < 192; a++) {
        for(b = 0; b < 192; b++) {
            conv41(a, b).resize(3, 3);
        }
    }

    conv42.resize(192, 192);
    for(a = 0; a < 192; a++) {
        for(b = 0; b < 192; b++) {
            conv42(a, b).resize(3, 3);
        }
    }

    conv51.resize(128, 192);
    for(a = 0; a < 128; a++) {
        for(b = 0; b < 192; b++) {
            conv51(a, b).resize(3, 3);
        }
    }

    conv52.resize(128, 192);
    for(a = 0; a < 128; a++) {
        for(b = 0; b < 192; b++) {
            conv52(a, b).resize(3, 3);
        }
    }

    // Every Neuron has weights to every neuron of the previous layer. Hence weights are a 2D-matrix.
    // Every Row contains the weights of one neuron.
    Matrix fc6;
    Matrix fc7;
    Matrix fc8;

    // resize the matrices
    fc6.resize(4096, 9216); // (Number of Neurons, Number of Connections per Neuron)
    fc7.resize(4096, 4096);
    fc8.resize(1000, 4096);

    //Bias Vectors:
    Vector conv1Bias;
    Vector conv21Bias;
    Vector conv22Bias;
    Vector conv31Bias;
    Vector conv32Bias;
    Vector conv41Bias;
    Vector conv42Bias;
    Vector conv51Bias;
    Vector conv52Bias;

    Vector fc6Bias;
    Vector fc7Bias;
    Vector fc8Bias;

    // resize the bias vectors
    // One bias per kernel.
    conv1Bias.resize(96);
    conv21Bias.resize(128);
    conv22Bias.resize(128);
    conv31Bias.resize(192);
    conv32Bias.resize(192);
    conv41Bias.resize(192);
    conv42Bias.resize(192);
    conv51Bias.resize(128);
    conv52Bias.resize(128);

    // One bias per neuron.
    fc6Bias.resize(4096);
    fc7Bias.resize(4096);
    fc8Bias.resize(1000);

    // load the weight.txt file
    ifstream inFile;
    inFile.open("../weights.txt");

    if (!inFile) {
        cerr << "Unable to load weight-file, please place it at the top of the project-structure.";
        exit(1);
    }

    //Calculate the borders where the layers end in the weights.txt file
    int conv1Border = conv1.rows() * conv1.cols() * conv1(0, 0).rows() * conv1(0, 0).cols();
    int conv1BiasBorder = conv1Bias.rows() + conv1Border;
    // The layers in the weights.txt file are not ordered intuitively

    // We halfed the kernels because of the two gpus, so now double the parameters
    // The weights for both gpu-layers are within one sector of the weights.txt file

    int conv4Border = 2 * (conv41.rows() * conv41.cols() * conv41(0, 0).rows() * conv41(0, 0).cols()) + conv1BiasBorder;
    int conv4BiasBorder = 2 * conv41Bias.rows() + conv4Border;
    int fc6Border = fc6.rows() * fc6.cols() + conv4BiasBorder;
    int fc6BiasBorder = fc6Bias.rows() + fc6Border;
    int conv3Border = 2 * (conv31.rows() * conv31.cols() * conv31(0, 0).rows() * conv31(0, 0).cols()) + fc6BiasBorder;
    int conv3BiasBorder = 2 * conv31Bias.rows() + conv3Border;
    int conv5Border = 2 * (conv51.rows() * conv51.cols() * conv51(0, 0).rows() * conv51(0, 0).cols()) + conv3BiasBorder;
    int conv5BiasBorder = 2 * conv51Bias.rows() + conv5Border;
    int fc7Border = fc7.rows() * fc7.cols() + conv5BiasBorder;
    int fc7BiasBorder = fc7Bias.rows() + fc7Border;
    int conv2Border = 2 * (conv21.rows() * conv21.cols() * conv21(0, 0).rows() * conv21(0, 0).cols()) + fc7BiasBorder;
    int conv2BiasBorder = 2 * conv21Bias.rows() + conv2Border;
    int fc8Border = fc8.rows() * fc8.cols() + conv2BiasBorder;
    int fc8BiasBorder = fc8Bias.rows() + fc8Border;
    // Funfact: fc8BiasBorder is the total number of parameters of AlexNet and is 60.965.224


    setlocale(LC_ALL, "C"); //Tell the stof (string to float) function to use english number notation (1.2 instead of 1,2)

    // Parse the file
    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0;
    for (string line; getline(inFile, line, ','); ) {
        // Conv-Layer 1
        if( i < conv1Border) { // 11*11*3*96 = 34848 Parameters for Conv-Layer 1
            conv1(i % 96, (i / 96) % 3)((i / 288) / 11, (i / 288) % 11) = stof(line);
            // i % 96 next kernel.
            // i / 96 % 3 every 96th value next colour. Only 3 colours (first conv-layer).
            // i / 363 / 11 every 96*3 = 288th value next pixel. Every 11th pixel next row.
            // i / 363 % 11 every 96*3 = 288th value next pixel. Only count cyclically from 0 to 10 for the next column.
        }
        if ( i == conv1Border) { cout << "Conv-Layer 1 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 1
        if( (conv1Border <= i) && (i < conv1BiasBorder) ) { // 96 kernels -> 96 biases for Conv-Layer 1.
            int z = 0;
            conv1Bias(z, 0) = stof(line); //Just a vector
            j++;
        }
        if ( i == conv1BiasBorder && j == 96) { cout << "Conv-Layer 1 biases loaded successfully.\n";} //Sanity-check and user-info

        // The layers in the weights.txt file are not ordered intuitively

        // Weights of Conv-Layer 4
        // Looks as if they use the same weights on both gpus, even though many parts of the internet say differently.
        if( (conv1BiasBorder <= i) && (i < conv4Border) ) { // 3*3*192*384 =  663.552  Parameters for Conv-Layer 4.
            if ((k % 384) < 192) {
                conv41(k % 192, (k / 384) % 192)((k / 73728) / 3, (k / 73728) % 3) = stof(line);
            } else {
                conv42(k % 192, (k / 384) % 192)((k / 73728) / 3, (k / 73728) % 3) = stof(line);
            }
            // As in Conv-Layer 1 but 384 kernels of size 3*3*192 (input depth is not 3 (colours) but 192
            // (kernels of previous layer divided by 2, because they use 2 gpus)).
            k++;
        }
        if ( i == conv4Border && k == 663552) { cout << "Conv-Layer 4 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 4
        if( (conv4Border <= i) && (i < conv4BiasBorder) )  { // 384 kernels -> 384 biases for Conv-Layer 4.
            if (l < 192) {
                conv41Bias(l) = stof(line); //Just a vector
            } else {
                conv42Bias(l - 192) = stof(line); //Just a vector
            }
            l++;
        }
        if ( i == conv4BiasBorder && l == 384) { cout << "Conv-Layer 4 biases loaded successfully.\n";} //Sanity-check and user-info


        // Weights of first FC-Layer (Layer 6)
        if( (conv4BiasBorder <= i) && (i < fc6Border) ) { // 4096 neurons, 256*6*6 Pixel Input-Size from Max-Pooled Conv-Layer 5 ->
            // 4096 * 256*6*6 = 37.748.736 parameters.
            fc6(m / 9216, m % 9216) = stof(line);
            // 4096 neurons (rows), each connected to input size of 256*6*6 = 9216.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc6, every row represents a neuron.
            m++;
        }
        if ( i == fc6Border && m == 37748736) { cout << "FC-Layer 6 weights (37.748.736) loaded successfully.\n";} //Sanity-check and user-info

        // Biases of first FC-Layer (Layer 6)
        if( (fc6Border <= i) && (i < fc6BiasBorder) ) { // 4096 neurons -> 4096 biases for first FC-Layer.
            fc6Bias(n,0) = stof(line); //Just a vector
            n++;
        }
        if ( i == fc6BiasBorder && n == 4096) { cout << "FC-Layer 6 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of Conv-Layer 3
        if( (fc6BiasBorder <= i) && (i < conv3Border) ) { // 3*3*256*384 = 884736 Parameters for Conv-Layer 3.
            if ((o % 384) < 192) {
                conv31(o % 192, (o / 384) % 256)((o / 98304) / 3, (o / 98304) % 3) = stof(line);
            } else {
                conv32(o % 192, (o / 384) % 256)((o / 98304) / 3, (o / 98304) % 3) = stof(line);
            }
            // As in Conv-Layer 1 but 384 kernels of size 3*3*256 (input depth is not 3 (colours) but 256 (kernels of previous layer,
            // not halved because layer 3 is calculated across gpus instead of parallelly)).
            o++;
        }
        if ( i == conv3Border && o == 884736) { cout << "Conv-Layer 3 weights loaded successfully.\n";} //Sanity-check and user-info

        //maybe that matrice needs later slicing (into 2 parts), as conv-3 reads cross-gpu instead of parallel.

        // Biases of Conv-Layer 3
        if( (conv3Border <= i) && (i < conv3BiasBorder) ) { // 384 kernels -> 384 biases for Conv-Layer 3.
            if (p < 192) {
                conv31Bias(p) = stof(line); //Just a vector
            } else {
                conv32Bias(p - 192) = stof(line); //Just a vector
            }
            p++;
        }
        if ( i == conv3BiasBorder && p == 384) { cout << "Conv-Layer 3 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of Conv-Layer 5
        if( (conv3BiasBorder <= i) && (i < conv5Border) ) { // 3*3*192*256 = 442.368 Parameters for Conv-Layer 5.
            if ((q % 384) < 128) {
                conv51(q % 128, (q / 256) % 192)((q / 49152) / 3, (q / 49152) % 3) = stof(line);
            } else {
                conv52(q % 128, (q / 256) % 192)((q / 49152) / 3, (q / 49152) % 3) = stof(line);
            }
            // As in Conv-Layer 1 but 256 kernels of size 3*3*192
            q++;
        }
        if ( i == conv5Border && q == 442368) { cout << "Conv-Layer 5 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 5
        if( (conv5Border <= i) && (i < conv5BiasBorder) ) { // 256 kernels -> 256 biases for Conv-Layer 3.
            if( r < 128) {
                conv51Bias(r) = stof(line); //Just a vector
            } else {
                conv52Bias(r - 128) = stof(line); //Just a vector
            }
            r++;
        }
        if ( i == conv5BiasBorder && r == 256) { cout << "Conv-Layer 5 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of second FC-Layer (Layer 7)
        if( (conv5BiasBorder <= i) && (i < fc7Border) ) { // 4096 neurons, 4096 Neurons has the previous Layer, so 4096²= 16.777.216
            fc7(s / 4096, s % 4096) = stof(line);
            // 4096 neurons (rows), each connected to input size of 4096.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc7, every row represents a neuron.
            s++;
        }
        if ( i == fc7Border && s == 16777216) { cout << "FC-Layer 7 weights (16.777.216) loaded successfully.\n";} //Sanity-check and user-info

        // Biases of second FC-Layer (Layer 7)
        if( (fc7Border <= i) && (i < fc7BiasBorder) ) { // 4096 neurons -> 4096 biases for second FC-Layer.
            fc7Bias(t) = stof(line); //Just a vector
            t++;
        }
        if ( i == fc7BiasBorder && t == 4096) { cout << "FC-Layer 7 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of Conv-Layer 2
        if( (fc7BiasBorder <= i) && (i < conv2Border) ) { // 5*5*48*256 = 307.200 Parameters for Conv-Layer 2.
            if ((u % 256) < 128) {
                conv21(u % 128, (u / 256) % 48)((u / 12288) / 5, (u / 12288) % 5) = stof(line);
            } else {
                conv22(u % 128, (u / 256) % 48)((u / 12288) / 5, (u / 12288) % 5) = stof(line);
            }
            // As in Conv-Layer 4 but 256 kernels of size 5*5*48
            u++;
        }
        if ( i == conv2Border && u == 307200) { cout << "Conv-Layer 2 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 2
        if( (conv2Border <= i) && (i < conv2BiasBorder) ) { // 256 kernels -> 256 biases for Conv-Layer 2.
            if (v < 128) {
                conv21Bias(v) = stof(line); //Just a vector
            } else {
                conv22Bias(v - 128) = stof(line); //Just a vector
            }
            v++;
        }
        if ( i == conv2BiasBorder && v == 256) { cout << "Conv-Layer 2 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of last FC-Layer (Layer 8)
        if( (conv2BiasBorder <= i) && (i < fc8Border) ) { // 1000 neurons, 4096 Neurons has the previous Layer, so 1000 * 4096= 4.096.000
            fc8(w / 4096, w % 4096) = stof(line);
            // 4096 neurons (rows), each connected to input size of 4096.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc7, every row represents a neuron.
            w++;
        }
        if ( i == fc8Border && w == 4096000) { cout << "The weights of the final layer have been loaded successfully.\n";} //Sanity-check and user-info

        // Biases of last FC-Layer (Layer 8)
        if( (fc8Border <= i) && (i < fc8BiasBorder) ) { // 1000 neurons -> 1000 biases for second FC-Layer.
            fc8Bias(x) = stof(line); //Just a vector
            x++;
        }
        i++;
        // in the end, for-loop doesn't get executed again (file is completely read through), so i++ is not executed again and has to be in front of the two next messages.
        if ( i == fc8BiasBorder && x == 1000) { cout << "The biases of the final layer have been loaded successfully.\n";} //Sanity-check and user-info
        if (i == fc8BiasBorder) { cout << "60.965.224 parameters successfully loaded.\n";}
        if (i == fc8BiasBorder + 1) { cout << "This line should not be reached\n";}
    }


    //Now create the layers of AlexNet
    layers.resize(25);

    layers(0) = new Conv2DLayer(227, 4, 0, conv1, conv1Bias);
    layers(1) = new ReLULayer();
    layers(2) = new MaxPool2D(55, 55, 96, 3, 3, 2);
    layers(3) = new NormLayer(27, 27, 96, 2, 0.0001, 0.75, 5);

    layers(4) = new Conv2DLayer(27, 1, 2, conv21, conv21Bias);
    layers(5) = new Conv2DLayer(27, 1, 2, conv22, conv22Bias);
    layers(6) = new ReLULayer();
    layers(7) = new MaxPool2D(27, 27, 128, 3, 3, 2); //Use it for both gpus (2 times)
    layers(8) = new NormLayer(13, 13, 128, 2, 0.0001, 0.75, 5); //Use it for both gpus (2 times)

    layers(9) = new Conv2DLayer(13, 1, 1, conv31, conv31Bias);
    layers(10) = new Conv2DLayer(13, 1, 1, conv32, conv32Bias);
    layers(11) = new ReLULayer();

    layers(12) = new Conv2DLayer(13, 1, 1, conv41, conv41Bias);
    layers(13) = new Conv2DLayer(13, 1, 1, conv42, conv42Bias);
    layers(14) = new ReLULayer();

    layers(15) = new Conv2DLayer(13, 1, 1, conv51, conv51Bias);
    layers(16) = new Conv2DLayer(13, 1, 1, conv52, conv52Bias);
    layers(17) = new ReLULayer();
    layers(18) = new MaxPool2D(13, 13, 128, 3, 3, 2);

    layers(19) = new FCLayer(fc6, fc6Bias);
    layers(20) = new ReLULayer();

    layers(21) = new FCLayer(fc7, fc7Bias);
    layers(22) = new ReLULayer();

    layers(23) = new FCLayer(fc8, fc8Bias);
    layers(24) = new ReLULayer();
}


void NeuralNet::classify(Layer::ThreeDMatrix &picture, Layer::Vector &result) {

    //Forward-Propagate

    //The input and outputmatrices of the layers, which are calculated on only one simulated GPU.
    Eigen::Matrix<Layer::ThreeDMatrix, Eigen::Dynamic, 1> io;
    io.resize(13);
    io(0) = picture;

    //debug
    cout << "input in classify (should match): ";
    cout<< " r:" << io(0)(0)(0, 0) << " g:" << io(0) (1)(226, 0) << " b:" << io(0) (2)(226, 226) << endl;

    for (int i = 0; i <= 3; ++i) { // 0 to i=3, conv2 needs special treatment (two gpus in AlexNet)
        layers(i)->forward(io(i), io(i+1));
        cout << "layer " << i << " applied itself successfully" << endl;
        cout << "it returned a matrix of size " << io(i+1)(0).rows()
             << " x " << io(i+1)(0).cols()
             << " and depth " << io(i+1).rows() << endl;

        //debug print first 2D-Matrix of output
        for (int row = 0; row < io(i+1)(0).rows(); ++row) {
            for (int col = 0; col < io(i+1)(0).cols(); ++col) {
                cout << io(i+1)(0)(row, col) << ", ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }

    //Two io-Arrays for the two simulated gpus
    Eigen::Matrix<Layer::ThreeDMatrix, Eigen::Dynamic, 1> io1;
    io1.resize(12);
    Eigen::Matrix<Layer::ThreeDMatrix, Eigen::Dynamic, 1> io2;
    io2.resize(12);

    //slice the input of conv2 into two pieces.
    io1(0).resize(48);
    io2(0).resize(48);
    for (int depth = 0; depth < 48; ++depth) {
        io1(0)(depth).resize(27, 27);
        io2(0)(depth).resize(27, 27);
        for (int i = 0; i < 27; ++i) {
            for (int j = 0; j < 27; ++j) {
                io1(0)(depth)(i, j) = io(4)(depth)(i, j);
                io2(0)(depth)(i, j) = io(4)(depth + 48)(i, j);
            }
        }
    }
    cout << "split the output" << endl
    << "Result from splitting for the first gpu is:" << endl;
    //debug print first 2D-Matrix of splitting-output
    for (int row = 0; row < io1(0)(0).rows(); ++row) {
        for (int col = 0; col < io1(0)(0).cols(); ++col) {
            cout << io1(0)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    cout << "Result from splitting for the second gpu is:" << endl;
    //debug print first 2D-Matrix of splitting-output
    for (int row = 0; row < io2(0)(0).rows(); ++row) {
        for (int col = 0; col < io2(0)(0).cols(); ++col) {
            cout << io2(0)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    //Conv-Layer 2 on each gpu:
    layers(4)->forward(io1(0), io1(1));
    cout << "Conv-Layer 2.1 applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io1(1)(0).rows()
         << " x " << io1(1)(0).cols()
         << " and depth " << io1(1).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io1(1)(0).rows(); ++row) {
        for (int col = 0; col < io1(1)(0).cols(); ++col) {
            cout << io1(1)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    layers(5)->forward(io2(0), io2(1));
    cout << "Conv-Layer 2.2 applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io2(1)(0).rows()
         << " x " << io2(1)(0).cols()
         << " and depth " << io2(1).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io2(1)(0).rows(); ++row) {
        for (int col = 0; col < io2(1)(0).cols(); ++col) {
            cout << io2(1)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // calculate Relu, Max Pool and Norm on the two simulated gpus:
    for (int i = 6; i <= 8; ++i) {
        layers(i)->forward(io1(i-5), io1(i-4));
        layers(i)->forward(io2(i-5), io2(i-4));
        cout << "layer " << i << " applied itself successfully" << endl;
        cout << "it returned two matrices of size " << io1(i-4)(0).rows()
             << " x " << io1(i-4)(0).cols()
             << " and depth " << io1(i-4).rows() << endl;
        //debug print first 2D-Matrix of output
        cout <<"GPU1 Layer" << i << endl;
        for (int row = 0; row < io1(i-4)(0).rows(); ++row) {
            for (int col = 0; col < io1(i-4)(0).cols(); ++col) {
                cout << io1(i-4)(0)(row, col) << ", ";
            }
            cout << endl;
        }
        cout << endl << endl;
        //debug print first 2D-Matrix of output
        cout <<"GPU2 Layer" << i << endl;
        for (int row = 0; row < io2(i-4)(0).rows(); ++row) {
            for (int col = 0; col < io2(i-4)(0).cols(); ++col) {
                cout << io2(i-4)(0)(row, col) << ", ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }


    //conv-Layer 3 is cross-GPU, so merge the outputs of the previous layer:
    //resize the new input matrix of conv-layer 3
    io(5).resize(256);
    for (int depth = 0; depth < 256; ++depth) {
        io(5)(depth).resize(13, 13);
    }
    io(5) <<  io1(4),
                    io2(4);
    //merged (vertically as a vector of Matrices (3rd-Dimension), Eigen does it right automatically)
    cout << "merged the output \n Output after merging is: " << endl;
    //debug print merging-output
    for (int row = 0; row < io(5)(0).rows(); ++row) {
        for (int col = 0; col < io(5)(0).cols(); ++col) {
            cout << io(5)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;


    //Conv-Layer 3 on each gpu:
    layers(9)->forward(io(5), io1(5));
    cout << "Conv-Layer 3.1 applied itself successfully" << endl;
    cout << "it returned a matrix of size " << io1(5)(0).rows()
         << " x " << io1(5)(0).cols()
         << " and depth " << io1(5).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io1(5)(0).rows(); ++row) {
        for (int col = 0; col < io1(5)(0).cols(); ++col) {
            cout << io1(5)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    layers(10)->forward(io(5), io2(5));
    cout << "Conv-Layer 3.2 applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io2(5)(0).rows()
         << " x " << io2(5)(0).cols()
         << " and depth " << io2(5).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io2(5)(0).rows(); ++row) {
        for (int col = 0; col < io2(5)(0).cols(); ++col) {
            cout << io2(5)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // calculate ReLU
    layers(11)->forward(io1(5), io1(6));
    layers(11)->forward(io2(5), io2(6));
    cout << "ReLu Layer applied itself successfully" << endl;

    //Conv-Layer 4 on each gpu:
    layers(12)->forward(io1(6), io1(7));
    cout << "Conv-Layer 4.1 applied itself successfully" << endl;
    cout << "it returned a matrix of size " << io1(7)(0).rows()
         << " x " << io1(7)(0).cols()
         << " and depth " << io1(7).rows() << endl;
    layers(13)->forward(io2(6), io2(7));
    cout << "Conv-Layer 4.2 applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io2(7)(0).rows()
         << " x " << io2(7)(0).cols()
         << " and depth " << io2(7).rows() << endl;

    // calculate ReLU
    layers(14)->forward(io1(7), io1(8));
    layers(14)->forward(io2(7), io2(8));
    cout << "ReLu Layer applied itself successfully" << endl;

    //Conv-Layer 5 on each gpu:
    layers(15)->forward(io1(8), io1(9));
    cout << "Conv-Layer 5.1 applied itself successfully" << endl;
    cout << "it returned a matrix of size " << io1(9)(0).rows()
         << " x " << io1(9)(0).cols()
         << " and depth " << io1(9).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io1(9)(0).rows(); ++row) {
        for (int col = 0; col < io1(9)(0).cols(); ++col) {
            cout << io1(9)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    layers(16)->forward(io2(8), io2(9));
    cout << "Conv-Layer 5.2 applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io2(9)(0).rows()
         << " x " << io2(9)(0).cols()
         << " and depth " << io2(9).rows() << endl;

    //debug print first 2D-Matrix of output
    for (int row = 0; row < io2(9)(0).rows(); ++row) {
        for (int col = 0; col < io2(9)(0).cols(); ++col) {
            cout << io2(9)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // calculate ReLU
    layers(17)->forward(io1(9), io1(10));
    layers(17)->forward(io2(9), io2(10));
    cout << "ReLu Layer applied itself successfully" << endl;

    //apply Max-Pooling
    layers(18)->forward(io1(10), io1(11));
    layers(18)->forward(io2(10), io2(11));
    cout << "Max-Pooling Layer applied itself successfully" << endl;
    cout << "it returned two matrices of size " << io2(11)(0).rows()
         << " x " << io2(11)(0).cols()
         << " and depth " << io2(11).rows() << endl;

    //First FC-Layer is cross-GPU, so merge the outputs of the previous layer:
    //resize the new input matrix of conv-layer 5 //probably not necessary, test another time TODO Above too
    io(6).resize(256);
    for (int depth = 0; depth < 256; ++depth) {
        io(6)(depth).resize(6, 6);
    }
    io(6) <<  io1(11),
                    io2(11);
    //merged (vertically as a vector of Matrices (3rd-Dimension), Eigen does it right automatically)

    cout << "merged the output \n Output after merging for first FC-Layer is: " << endl;
    //debug print merging-output
    for (int row = 0; row < io(6)(0).rows(); ++row) {
        for (int col = 0; col < io(6)(0).cols(); ++col) {
            cout << io(6)(0)(row, col) << ", ";
        }
        cout << endl;
    }
    cout << endl << endl;

    // last 6 Layers (3 FC and 3 ReLu)
    for (int i = 19; i <= 24; ++i) {
        layers(i)->forward(io(i - 13), io(i - 12));
        cout << "layer " << i << " applied itself successfully" << endl;
        cout << "it returned a matrix of size " << io(i - 12)(0).rows()
             << " x " << io(i - 12)(0).cols()
             << " and depth " << io(i - 12).rows() << endl;

        //debug print output-vector
        for (int row = 0; row < io(i-12).rows(); ++row) {
                cout << io(i-12)(row)(0, 0) << ", ";
                if(row %50 == 49) { //50 per line
                    cout << endl;
            }
        }
        cout << endl << endl;
    }

    result.resize(1000);
    for (int i = 0; i < 1000; ++i) { //Last Layer always has a Vector in a ThreeDMatrix
        result(i) = io(12)(i)(0, 0);
    }
}
/**
 * Project Entwurf_PSE_KNN
 * @author Jakub Trzcinsi, Viet Pham, Friedemann Claus, Dima Seletkov, Alexandr Eismont
 * @version 1.2
 */


#include "NeuralNet.h"

/**
 * NeuralNet implementation
 */


//Weight Matrices:

// For example a 11x11x3 kernel is represented in the matrix as 3 11x11 matrices in one row.
// So one row has three 11x11 matrices and represents a kernel.
// So conv1 is a very long matrix with width 3

FourDMatrix conv1;
FourDMatrix conv2;
FourDMatrix conv3;
FourDMatrix conv4;
FourDMatrix conv5;


// Every Neuron has weights to every neuron of its previous layer. Hence weights are a 2D-matrix.
// Every Row contains the weights of one neuron.
Matrix fc6;
Matrix fc7;
Matrix fc8;

//Bias Vectors:
Vector conv1Bias;
Vector conv2Bias;
Vector conv3Bias;
Vector conv4Bias;
Vector conv5Bias;

Vector fc6Bias;
Vector fc7Bias;
Vector fc8Bias;
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

    // Wheights for the conv-layers are stored in a Matrix of Matrices
    // A row of the outer matrix represents a kernel
    // For example a 11x11x3 kernel of the first conv-layer is represented as 3 11x11 matrices in one row (RGB in that case).
    // So conv1 is a very long matrix with width 3.

    FourDMatrix conv1;
    FourDMatrix conv2;
    FourDMatrix conv3;
    FourDMatrix conv4;
    FourDMatrix conv5;

    // resize the 4d-Matrices
    // for explanations see the parsings of the layers
    int a;
    int b;
    conv1.resize(96, 3);
    for(a = 0; a < 96; a++) {
        for(b = 0; b < 3; b++) {
            conv1(a, b).resize(11, 11);
        }
    }

    conv2.resize(256, 48);
    for(a = 0; a < 256; a++) {
        for(b = 0; b < 48; b++) {
            conv2(a, b).resize(5, 5);
        }
    }

    conv3.resize(384, 256);
    for(a = 0; a < 384; a++) {
        for(b = 0; b < 256; b++) {
            conv3(a, b).resize(3, 3);
        }
    }

    conv4.resize(384, 192);
    for(a = 0; a < 384; a++) {
        for(b = 0; b < 192; b++) {
            conv4(a, b).resize(3, 3);
        }
    }

    conv5.resize(256, 192);
    for(a = 0; a < 256; a++) {
        for(b = 0; b < 192; b++) {
            conv5(a, b).resize(3, 3);
        }
    }

    // Every Neuron has weights to every neuron of its previous layer. Hence weights are a 2D-matrix.
    // Every Row contains the weights of one neuron.
    Matrix fc6;
    Matrix fc7;
    Matrix fc8;

    // resize the matrices
    fc6.resize(4096, 9216);
    fc7.resize(4096, 4096);
    fc8.resize(1000, 4096);


    //Bias Vectors:
    Vector conv1Bias;
    Vector conv2Bias;
    Vector conv3Bias;
    Vector conv4Bias;
    Vector conv5Bias;

    Vector fc6Bias;
    Vector fc7Bias;
    Vector fc8Bias;

    // resize the bias vectors
    conv1Bias.resize(96);
    conv2Bias.resize(256);
    conv3Bias.resize(384);
    conv4Bias.resize(384);
    conv5Bias.resize(256);

    fc6Bias.resize(4096);
    fc7Bias.resize(4096);
    fc8Bias.resize(1000);

    //load the weight.txt file
    ifstream inFile;
    inFile.open("../weights.txt");

    if (!inFile) {
        cerr << "Unable to load weight-file.";
        exit(1);
    }

    //Calculate the Borders where the layers end in the weights.txt file
    int conv1Border = conv1.rows() * conv1.cols() * conv1(0, 0).rows() * conv1(0, 0).cols();
    int conv1BiasBorder = conv1Bias.rows() + conv1Border;
    // The layers in the weights.txt file are not ordered intuitively
    int conv4Border = conv4.rows() * conv4.cols() * conv4(0, 0).rows() * conv4(0, 0).cols()+ conv1BiasBorder;
    int conv4BiasBorder = conv4Bias.rows() + conv4Border;
    int fc6Border = fc6.rows() * fc6.cols() + conv4BiasBorder;
    int fc6BiasBorder = fc6Bias.rows() + fc6Border;
    int conv3Border = conv3.rows() * conv3.cols() * conv3(0, 0).rows() * conv3(0, 0).cols() + fc6BiasBorder;
    int conv3BiasBorder = conv3Bias.rows() + conv3Border;
    int conv5Border = conv5.rows() * conv5.cols() * conv5(0, 0).rows() * conv5(0, 0).cols() + conv3BiasBorder;
    int conv5BiasBorder = conv5Bias.rows() + conv5Border;
    int fc7Border = fc7.rows() * fc7.cols() + conv5BiasBorder;
    int fc7BiasBorder = fc7Bias.rows() + fc7Border;
    int conv2Border = conv2.rows() * conv2.cols() * conv2(0, 0).rows() * conv2(0, 0).cols() + fc7BiasBorder;
    int conv2BiasBorder = conv2Bias.rows() + conv2Border;
    int fc8Border = fc8.rows() * fc8.cols() + conv2BiasBorder;
    int fc8BiasBorder = fc8Bias.rows() + fc8Border;
    // Funfact: fc8BiasBorder is the total number of parameters of the AlexNet and is 60.965.224


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
        // Looks as if they use the same wheights on both gpus, even though many parts of the internet say differently.
        if( (conv1BiasBorder <= i) && (i < conv4Border) ) { // 3*3*192*384 =  663.552  Parameters for Conv-Layer 4.
            conv4(k % 384, (k / 384) % 192)((k / 73728) / 3, (k / 73728) % 3) = stof(line);
            // As in Conv-Layer 1 but 384 kernels of size 3*3*192 (input depth is not 3 (colours) but 192
            // (kernels of previous layer divided by 2, because they use 2 gpus)).
            k++;
        }
        if ( i == conv4Border && k == 663552) { cout << "Conv-Layer 4 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 4
        if( (conv4Border <= i) && (i < conv4BiasBorder) )  { // 384 kernels -> 384 biases for Conv-Layer 4.
            conv4Bias(l) = stof(line); //Just a vector
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
            conv3(o % 384, (o / 384) % 256)((o / 98304) / 3, (o / 98304) % 3) = stof(line);
            // As in Conv-Layer 1 but 384 kernels of size 3*3*256 (input depth is not 3 (colours) but 256 (kernels of previous layer,
            // not halved because layer 3 is calculated across gpus instead of parallelly)).
            o++;
        }
        if ( i == conv3Border && o == 884736) { cout << "Conv-Layer 3 weights loaded successfully.\n";} //Sanity-check and user-info

        //maybe that matrice needs later slicing (into 2 parts), as conv-3 reads cross-gpu instead of parallel.

        // Biases of Conv-Layer 3
        if( (conv3Border <= i) && (i < conv3BiasBorder) ) { // 384 kernels -> 384 biases for Conv-Layer 3.
            conv3Bias(p) = stof(line); //Just a vector
            p++;
        }
        if ( i == conv3BiasBorder && p == 384) { cout << "Conv-Layer 3 biases loaded successfully.\n";} //Sanity-check and user-info

        // Weights of Conv-Layer 5
        if( (conv3BiasBorder <= i) && (i < conv5Border) ) { // 3*3*192*256 = 442.368 Parameters for Conv-Layer 5.
            conv5(q % 256, (q / 256) % 192)((q / 49152) / 3, (q / 49152) % 3) = stof(line);
            // As in Conv-Layer 1 but 256 kernels of size 3*3*192
            q++;
        }
        if ( i == conv5Border && q == 442368) { cout << "Conv-Layer 5 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 5
        if( (conv5Border <= i) && (i < conv5BiasBorder) ) { // 256 kernels -> 256 biases for Conv-Layer 3.
            conv5Bias(r) = stof(line); //Just a vector
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
            conv2(u % 256, (u / 256) % 48)((u / 12288) / 5, (u / 12288) % 5) = stof(line);
            // As in Conv-Layer 4 but 256 kernels of size 5*5*48
        }
        if ( i == conv2Border && u == 307200) { cout << "Conv-Layer 2 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 2
        if( (conv2Border <= i) && (i < conv2BiasBorder) ) { // 256 kernels -> 256 biases for Conv-Layer 2.
            conv2Bias(v) = stof(line); //Just a vector
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


        //Now create the layers

        Conv2DLayer conv1Layer = new Conv2DLayer();
        conv1Layer.setWeights(conv1, conv1Bias);

    }
}
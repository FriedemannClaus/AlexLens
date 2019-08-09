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
#include "NeuralNet.h"
#include "Layer.h"
#include <list>

using namespace std;

void NeuralNet::init() {

    typedef Eigen::Matrix<float, Eigen::Dynamic, 1> Vector;
    typedef Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic> Matrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, 1> ThreeDMatrix;
    typedef Eigen::Matrix<Matrix, Eigen::Dynamic, Eigen::Dynamic> FourDMatrix;

    //Weight Matrices:

    // For example a 11x11x3 kernel is represented in the matrix as 3 11x11 matrices in one row.
    // So one row has three 11x11 matrices and represents a kernel.
    // So conv1 is a very long matrix with width 3

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
            conv2(a, b).resize(3, 3);
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


    ifstream inFile;
    inFile.open("/home/friedemann/CLionProjects/AlexLens/weights.txt");

    if (!inFile) {
        cerr << "Unable to load weight-file.";
        exit(1);
    }

    int i = 0, j = 0, k = 0, l = 0, m = 0, n = 0, o = 0, p = 0, q = 0, r = 0, s = 0, t = 0, u = 0, v = 0, w = 0, x = 0;

    for (string line; getline(inFile, line, ','); ) {
        // Conv-Layer 1
        if( i < 34848) { // 11*11*3*96 = 34848 Parameters for Conv-Layer 1
            conv1(i % 96, (i / 96) % 3)((i / 288) / 11, (i / 288) % 11) = stof(line);
            // i % 96 next kernel.
            // i / 96 % 3 every 96th value next colour. Only 3 colours (first conv-layer).
            // i / 363 / 11 every 96*3 = 288th value next pixel. Every 11th pixel next row.
            // i / 363 % 11 every 96*3 = 288th value next pixel. Only count cyclically from 0 to 10 for the next column.
        }
        if ( i == 34848) { cout << "Conv-Layer 1 weights loaded successfully.\n";} //Sanity-check and user-info

        // Biases of Conv-Layer 1
        if( (34848 <= i) && (i < 34944) ) { // 96 kernels -> 96 biases for Conv-Layer 1. 34848 + 96 = 34944
            int z = 0;
            conv1Bias(z, 0) = stof(line); //Just a vector
            j++;
        }
        if ( i == 34944 && j == 96) { cout << "Conv-Layer 1 biases loaded successfully.\n";} //Sanity-check and user-info

        // The layers in the weights.txt file are not ordered intuitively

        // Weights of Conv-Layer 4
        if( (34944 <= i) && (i < 698496) ) { // 3*3*192*384 =  663.552‬ Parameters for Conv-Layer 4. 34944 + 663.552 = 698.496‬
            conv4(k % 384, (k / 384) % 192)((k / 73728) / 3, (k / 73728) % 3) = stof(line);
            // As in Conv-Layer 1 but 384 kernels of size 3*3*192 (input depth is not 3 (colours) but 192
            // (kernels of previous layer / 2, because they use 2 gpus)).
            k++;
        }
        if ( i == 698496 && k == 663552) { cout << "Conv-Layer 4 weights loaded successfully.\n";} //Sanity-check and user-info

        // scheint so, als würden  einfach beide gpus die gleichen gewichte verwenden
        // aber im internet steht doppelt so viele gewichte eigentlich

        // Biases of Conv-Layer 4
        if( (698496 <= i) && (i < 698880) )  { // 384 kernels -> 384 biases for Conv-Layer 4. 698.496 + 384 = 698.880
            conv4Bias(l) = stof(line); //Just a vector
            l++;
        }
        if ( i == 698880 && l == 384) { cout << "Conv-Layer 4 biases loaded successfully.\n";} //Sanity-check and user-info


        // Weights of first FC-Layer (Layer 6)
        if( (698880 <= i) && (i < 38447616) ) { // 4096 neurons, 256*6*6 Pixel Input-Size from Max-Pooled Conv-Layer 5 ->
                                      // 4096 * 256*6*6 = 37.748.736 parameters. 698.880 + 37.748.736 = 38.447.616
            fc6(m / 9216, m % 9216) = stof(line);
            // 4096 neurons (rows), each connected to input size of 256*6*6 = 9216.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc 6, every row represents a neuron.
            m++;
        }
        if ( i == 38447616 && m == 37748736) { cout << "FC-Layer 6 weights (37.748.736) loaded successfully.\n";} //Sanity-check and user-info

        // Biases of first FC-Layer (Layer 6)
        if( (38447616 <= i) && (i < 38451712) ) { // 4096 neurons -> 4096 biases for first FC-Layer. 38.447.616 + 4096 = 38.451.712
            fc6Bias(n,0) = stof(line); //Just a vector
            n++;
        }
        if ( i == 38451712 && n == 4096) { cout << "FC-Layer 6 biases loaded successfully.\n";} //Sanity-check and user-info


        // Weights of Conv-Layer 3
        if( (38451712 <= i) && (i < 39336448) ) { // 3*3*256*384 = 884736 Parameters for Conv-Layer 3. 38.451.712 + 884.736 = 39.336.448
            conv3(o % 384, (o / 384) % 256)((o / 98304) / 3, (o / 98304) % 3) = stof(line);
            // As in Conv-Layer 1 but 384 kernels of size 3*3*256 (input depth is not 3 (colours) but 256 (kernels of previous layer)).
            o++;
        }
        if ( i == 39336448 && o == 884736) { cout << "Conv-Layer 3 weights loaded successfully.\n";} //Sanity-check and user-info

        //maybe that matrice needs later slicing (ni 2 parts), as conv-3 reads cross-gpu instead of parallel.

        // Biases of Conv-Layer 3
        if( (39336448 <= i) && (i < 39336832) ) { // 384 kernels -> 384 biases for Conv-Layer 3. 39.336.448 + 384 = 39.336.832
            conv3Bias(p) = stof(line); //Just a vector
            p++;
        }
        if ( i == 39336832 && p == 384) { cout << "Conv-Layer 3 biases loaded successfully.\n";} //Sanity-check and user-info

        //corrected until here. Rest will be adjusted soon, but works analogically.

        // Weights of Conv-Layer 5
        if( (39336832 <= i) && (i <= 39778816) ) { // 3*3*192*256 = 442.368 Parameters for Conv-Layer 5. 39.336.448 + 442.368 = 39.778.816
            conv5(q % 256, (q / 256) % 192)((q / 49152) / 3, (q / 49152) % 3) = stof(line);
            // As in Conv-Layer 1 but 256 kernels of size 3*3*192 (input depth is not 3 (colours) but 192 (kernels of previous layer)).
            q++;
        }

        // Biases of Conv-Layer 5
        if( (39778816 <= i) && (i < 39779072) ) { // 256 kernels -> 256 biases for Conv-Layer 3. 39778816 + 256 = 39.779.072
            conv5Bias(r) = stof(line); //Just a vector
            r++;
        }

        // Weights of second FC-Layer (Layer 7)
        if( (39779072 <= i) && (i < 56556288) ) { // 4096 neurons, 4096 Neurons has the previous Layer, so 4096²= 16.777.216
            // 39.779.072 + 16.777.216 = 56.556.288‬
            fc7(s / 4096, s % 4096) = stof(line);
            // 4096 neurons (rows), each connected to input size of 4096.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc7, every row represents a neuron.
            s++;
        }
        //if ( i == 56556288 && s == 16777216) { cout << "FC-Layer 7 weights (16.777.216) loaded successfully.\n";} //Sanity-check and user-info

        // Biases of second FC-Layer (Layer 7)
        if( (56556288 <= i) && (i < 56560384) ) { // 4096 neurons -> 4096 biases for second FC-Layer. 56.556.288 + 4096 = 56.560.384‬
            fc7Bias(t) = stof(line); //Just a vector
            t++;
        }

        // Weights of Conv-Layer 2
        if( (56560384 <= i) && (i < 56867584) ) { // 5*5*48*256 = 307.200 Parameters for Conv-Layer 2. 56.560.384‬ + 307.200 = 56.867.584‬
            conv2(u % 256, (u / 256) % 48)((u / 12288) / 5, (u / 12288) % 5) = stof(line);
            // As in Conv-Layer 4 but 256 kernels of size 5*5*48.
            u++;
        }

        // Biases of Conv-Layer 2
        if( (56867584 <= i) && (i < 56867840) ) { // 256 kernels -> 256 biases for Conv-Layer 2. 56.867.584 + 256 = 56.867.840‬
            conv2Bias(v) = stof(line); //Just a vector
            v++;
        }

        // Weights of last FC-Layer (Layer 8)
        if( (56867840 <= i) && (i < 60963840) ) { // 1000 neurons, 4096 Neurons has the previous Layer, so 1000 * 4096= 4.096.000
            // 56.867.840 + 4.096.000 = 60.963.840
            fc8(w / 4096, w % 4096) = stof(line);
            // 4096 neurons (rows), each connected to input size of 4096.
            // (I hope that's the way it is coded in the weights.txt, and not the other way around).
            // As described at the initialization of fc7, every row represents a neuron.
            w++;
        }
        if ( w == 4096000) { cout << "The weights of the final layer have been loaded successfully.\n";} //Sanity-check and user-info

        // Biases of last FC-Layer (Layer 8)
        if( (60963840 <= i) && (i < 60964840) ) { // 1000 neurons -> 1000 biases for second FC-Layer. 60.963.840 + 1000 = 60.964.840
            fc8Bias(x) = stof(line); //Just a vector
            x++;
        }

        i++;
        if (i == 60964840) { cout << "60.964.840 parameters successfully loaded.\n";}

    }
}
//
// Created by Viet Pham.
//
#include <iostream>
#include "AlexNetWeightParser.h"

using namespace std;




AlexNetWeightParser::AlexNetWeightParser(FourDMatrix &eigen_conv1_w, Vector &eigen_conv1_b, FourDMatrix &eigen_conv2_1_w, Vector &eigen_conv2_1_b,
                                         FourDMatrix &eigen_conv2_2_w, Vector &eigen_conv2_2_b, FourDMatrix &eigen_conv3_w, Vector &eigen_conv3_b,
                                         FourDMatrix &eigen_conv4_1_w, Vector &eigen_conv4_1_b, FourDMatrix &eigen_conv4_2_w, Vector &eigen_conv4_2_b,
                                         FourDMatrix &eigen_conv5_1_w, Vector &eigen_conv5_1_b, FourDMatrix &eigen_conv5_2_w, Vector &eigen_conv5_2_b,
                                         Matrix &eigen_dense1_w, Vector &eigen_dense1_b, Matrix &eigen_dense2_w, Vector &eigen_dense2_b, Matrix &eigen_dense3_w, Vector &eigen_dense3_b)
{
    this->eigen_conv1_w = &eigen_conv1_w;
    this->eigen_conv1_b = &eigen_conv1_b;

    this->eigen_conv2_1_w = &eigen_conv2_1_w;
    this->eigen_conv2_1_b = &eigen_conv2_1_b;

    this->eigen_conv2_2_w = &eigen_conv2_2_w;
    this->eigen_conv2_2_b = &eigen_conv2_2_b;

    this->eigen_conv3_w = &eigen_conv3_w;
    this->eigen_conv3_b = &eigen_conv3_b;

    this->eigen_conv4_1_w = &eigen_conv4_1_w;
    this->eigen_conv4_1_b = &eigen_conv4_1_b;

    this->eigen_conv4_2_w = &eigen_conv4_2_w;
    this->eigen_conv4_2_b = &eigen_conv4_2_b;

    this->eigen_conv5_1_w = &eigen_conv5_1_w;
    this->eigen_conv5_1_b = &eigen_conv5_1_b;

    this->eigen_conv5_2_w = &eigen_conv5_2_w;
    this->eigen_conv5_2_b = &eigen_conv5_2_b;

    this->eigen_dense1_w = &eigen_dense1_w;
    this->eigen_dense1_b = &eigen_dense1_b;

    this->eigen_dense2_w = &eigen_dense2_w;
    this->eigen_dense2_b = &eigen_dense2_b;

    this->eigen_dense3_w = &eigen_dense3_w;
    this->eigen_dense3_b = &eigen_dense3_b;
    //initArrays();
    initMatrices();
}

void AlexNetWeightParser::parse() {
    //TODO
    try
    {
        H5File file(FILE_NAME, H5F_ACC_RDONLY);
        cout << "Weight file opened readonly." << endl;

        /*
        * Parse Conv1 weights
        */
        DataSet conv1WeightsDataSet = file.openDataSet(CONV1_W);
        DataSpace conv1WeightsDataSpace = conv1WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv1_w_dims[4];
        conv1_w_dims[0] = CONV1_W_NK;
        conv1_w_dims[1] = CONV1_W_NZ;
        conv1_w_dims[2] = CONV1_W_NY;
        conv1_w_dims[3] = CONV1_W_NX;
        DataSpace conv1WeightsMemSpace(CONV1_W_RANK_OUT, conv1_w_dims);

        conv1WeightsDataSet.read(conv1_w, PredType::NATIVE_FLOAT, conv1WeightsMemSpace, conv1WeightsDataSpace);

        /*
        * Parse Conv1 bias
        */
        DataSet conv1BiasDataSet = file.openDataSet(CONV1_b);
        DataSpace conv1BiasDataSpace = conv1BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv1_b_dims[1];
        conv1_b_dims[0] = CONV1_b_N;
        DataSpace conv1BiasMemSpace(CONV1_b_RANK_OUT, conv1_b_dims);

        conv1BiasDataSet.read(conv1_b, PredType::NATIVE_FLOAT, conv1BiasMemSpace, conv1BiasDataSpace);

        /*
        * Parse Conv2_1 weights
        */
        DataSet conv2_1WeightsDataSet = file.openDataSet(CONV2_1_W);
        DataSpace conv2_1WeightsDataSpace = conv2_1WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv2_1_w_dims[4];
        conv2_1_w_dims[0] = CONV2_1_W_NK;
        conv2_1_w_dims[1] = CONV2_1_W_NZ;
        conv2_1_w_dims[2] = CONV2_1_W_NY;
        conv2_1_w_dims[3] = CONV2_1_W_NX;
        DataSpace conv2_1WeightsMemSpace(CONV2_1_W_RANK_OUT, conv2_1_w_dims);

        conv2_1WeightsDataSet.read(conv2_1_w, PredType::NATIVE_FLOAT, conv2_1WeightsMemSpace, conv2_1WeightsDataSpace);

        /*
        * Parse Conv2_1 bias
        */
        DataSet conv2_1BiasDataSet = file.openDataSet(CONV2_1_b);
        DataSpace conv2_1BiasDataSpace = conv2_1BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv2_1_b_dims[1];
        conv2_1_b_dims[0] = CONV2_1_b_N;
        DataSpace conv2_1BiasMemSpace(CONV2_1_b_RANK_OUT, conv2_1_b_dims);

        conv2_1BiasDataSet.read(conv2_1_b, PredType::NATIVE_FLOAT, conv2_1BiasMemSpace, conv2_1BiasDataSpace);

        /*
        * Parse Conv2_2 weights
        */
        DataSet conv2_2WeightsDataSet = file.openDataSet(CONV2_2_W);
        DataSpace conv2_2WeightsDataSpace = conv2_2WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv2_2_w_dims[4];
        conv2_2_w_dims[0] = CONV2_2_W_NK;
        conv2_2_w_dims[1] = CONV2_2_W_NZ;
        conv2_2_w_dims[2] = CONV2_2_W_NY;
        conv2_2_w_dims[3] = CONV2_2_W_NX;
        DataSpace conv2_2WeightsMemSpace(CONV2_2_W_RANK_OUT, conv2_2_w_dims);

        conv2_2WeightsDataSet.read(conv2_2_w, PredType::NATIVE_FLOAT, conv2_2WeightsMemSpace, conv2_2WeightsDataSpace);

        /*
        * Parse Conv2_2 bias
        */
        DataSet conv2_2BiasDataSet = file.openDataSet(CONV2_2_b);
        DataSpace conv2_2BiasDataSpace = conv2_2BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv2_2_b_dims[1];
        conv2_2_b_dims[0] = CONV2_2_b_N;
        DataSpace conv2_2BiasMemSpace(CONV2_2_b_RANK_OUT, conv2_2_b_dims);

        conv2_2BiasDataSet.read(conv2_2_b, PredType::NATIVE_FLOAT, conv2_2BiasMemSpace, conv2_2BiasDataSpace);

        /*
        * Parse Conv3 weights
        */
        DataSet conv3WeightsDataSet = file.openDataSet(CONV3_W);
        DataSpace conv3WeightsDataSpace = conv3WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv3_w_dims[4];
        conv3_w_dims[0] = CONV3_W_NK;
        conv3_w_dims[1] = CONV3_W_NZ;
        conv3_w_dims[2] = CONV3_W_NY;
        conv3_w_dims[3] = CONV3_W_NX;
        DataSpace conv3WeightsMemSpace(CONV3_W_RANK_OUT, conv3_w_dims);

        conv3WeightsDataSet.read(conv3_w, PredType::NATIVE_FLOAT, conv3WeightsMemSpace, conv3WeightsDataSpace);

        /*
        * Parse Conv3 bias
        */
        DataSet conv3BiasDataSet = file.openDataSet(CONV3_b);
        DataSpace conv3BiasDataSpace = conv3BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv3_b_dims[1];
        conv3_b_dims[0] = CONV3_b_N;
        DataSpace conv3BiasMemSpace(CONV3_b_RANK_OUT, conv3_b_dims);

        conv3BiasDataSet.read(conv3_b, PredType::NATIVE_FLOAT, conv3BiasMemSpace, conv3BiasDataSpace);

        /*
        * Parse Conv4_1 weights
        */
        DataSet conv4_1WeightsDataSet = file.openDataSet(CONV4_1_W);
        DataSpace conv4_1WeightsDataSpace = conv4_1WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv4_1_w_dims[4];
        conv4_1_w_dims[0] = CONV4_1_W_NK;
        conv4_1_w_dims[1] = CONV4_1_W_NZ;
        conv4_1_w_dims[2] = CONV4_1_W_NY;
        conv4_1_w_dims[3] = CONV4_1_W_NX;
        DataSpace conv4_1WeightsMemSpace(CONV4_1_W_RANK_OUT, conv4_1_w_dims);

        conv4_1WeightsDataSet.read(conv4_1_w, PredType::NATIVE_FLOAT, conv4_1WeightsMemSpace, conv4_1WeightsDataSpace);

        /*
        * Parse Conv4_1 bias
        */
        DataSet conv4_1BiasDataSet = file.openDataSet(CONV4_1_b);
        DataSpace conv4_1BiasDataSpace = conv4_1BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv4_1_b_dims[1];
        conv4_1_b_dims[0] = CONV4_1_b_N;
        DataSpace conv4_1BiasMemSpace(CONV4_1_b_RANK_OUT, conv4_1_b_dims);

        conv4_1BiasDataSet.read(conv4_1_b, PredType::NATIVE_FLOAT, conv4_1BiasMemSpace, conv4_1BiasDataSpace);

        /*
        * Parse Conv4_2 weights
        */
        DataSet conv4_2WeightsDataSet = file.openDataSet(CONV4_2_W);
        DataSpace conv4_2WeightsDataSpace = conv4_2WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv4_2_w_dims[4];
        conv4_2_w_dims[0] = CONV4_2_W_NK;
        conv4_2_w_dims[1] = CONV4_2_W_NZ;
        conv4_2_w_dims[2] = CONV4_2_W_NY;
        conv4_2_w_dims[3] = CONV4_2_W_NX;
        DataSpace conv4_2WeightsMemSpace(CONV4_2_W_RANK_OUT, conv4_2_w_dims);

        conv4_2WeightsDataSet.read(conv4_2_w, PredType::NATIVE_FLOAT, conv4_2WeightsMemSpace, conv4_2WeightsDataSpace);

        /*
        * Parse Conv4_2 bias
        */
        DataSet conv4_2BiasDataSet = file.openDataSet(CONV4_2_b);
        DataSpace conv4_2BiasDataSpace = conv4_2BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv4_2_b_dims[1];
        conv4_2_b_dims[0] = CONV4_2_b_N;
        DataSpace conv4_2BiasMemSpace(CONV4_2_b_RANK_OUT, conv4_2_b_dims);

        conv4_2BiasDataSet.read(conv4_2_b, PredType::NATIVE_FLOAT, conv4_2BiasMemSpace, conv4_2BiasDataSpace);

        /*
        * Parse Conv5_1 weights
        */
        DataSet conv5_1WeightsDataSet = file.openDataSet(CONV5_1_W);
        DataSpace conv5_1WeightsDataSpace = conv5_1WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv5_1_w_dims[4];
        conv5_1_w_dims[0] = CONV5_1_W_NK;
        conv5_1_w_dims[1] = CONV5_1_W_NZ;
        conv5_1_w_dims[2] = CONV5_1_W_NY;
        conv5_1_w_dims[3] = CONV5_1_W_NX;
        DataSpace conv5_1WeightsMemSpace(CONV5_1_W_RANK_OUT, conv5_1_w_dims);

        conv5_1WeightsDataSet.read(conv5_1_w, PredType::NATIVE_FLOAT, conv5_1WeightsMemSpace, conv5_1WeightsDataSpace);

        /*
        * Parse Conv5_1 bias
        */
        DataSet conv5_1BiasDataSet = file.openDataSet(CONV5_1_b);
        DataSpace conv5_1BiasDataSpace = conv5_1BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv5_1_b_dims[1];
        conv5_1_b_dims[0] = CONV5_1_b_N;
        DataSpace conv5_1BiasMemSpace(CONV5_1_b_RANK_OUT, conv5_1_b_dims);

        conv5_1BiasDataSet.read(conv5_1_b, PredType::NATIVE_FLOAT, conv5_1BiasMemSpace, conv5_1BiasDataSpace);

        /*
        * Parse Conv5_2 weights
        */
        DataSet conv5_2WeightsDataSet = file.openDataSet(CONV5_2_W);
        DataSpace conv5_2WeightsDataSpace = conv5_2WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t conv5_2_w_dims[4];
        conv5_2_w_dims[0] = CONV5_2_W_NK;
        conv5_2_w_dims[1] = CONV5_2_W_NZ;
        conv5_2_w_dims[2] = CONV5_2_W_NY;
        conv5_2_w_dims[3] = CONV5_2_W_NX;
        DataSpace conv5_2WeightsMemSpace(CONV5_2_W_RANK_OUT, conv5_2_w_dims);

        conv5_2WeightsDataSet.read(conv5_2_w, PredType::NATIVE_FLOAT, conv5_2WeightsMemSpace, conv5_2WeightsDataSpace);

        /*
        * Parse Conv5_2 bias
        */
        DataSet conv5_2BiasDataSet = file.openDataSet(CONV5_2_b);
        DataSpace conv5_2BiasDataSpace = conv5_2BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t conv5_2_b_dims[1];
        conv5_2_b_dims[0] = CONV5_2_b_N;
        DataSpace conv5_2BiasMemSpace(CONV5_2_b_RANK_OUT, conv5_2_b_dims);

        conv5_2BiasDataSet.read(conv5_2_b, PredType::NATIVE_FLOAT, conv5_2BiasMemSpace, conv5_2BiasDataSpace);

        /*
        * Parse Dense1 weights
        */
        DataSet dense1WeightsDataSet = file.openDataSet(DENSE1_W);
        DataSpace dense1WeightsDataSpace = dense1WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t dense1_w_dims[2];
        dense1_w_dims[0] = DENSE1_W_NY;
        dense1_w_dims[1] = DENSE1_W_NX;
        DataSpace dense1WeightsMemSpace(DENSE1_W_RANK_OUT, dense1_w_dims);

        dense1WeightsDataSet.read(dense1_w, PredType::NATIVE_FLOAT, dense1WeightsMemSpace, dense1WeightsDataSpace);

        /*
        * Parse Dense1 bias
        */
        DataSet dense1BiasDataSet = file.openDataSet(DENSE1_b);
        DataSpace dense1BiasDataSpace = dense1BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t dense1_b_dims[1];
        dense1_b_dims[0] = DENSE1_b_N;
        DataSpace dense1BiasMemSpace(DENSE1_b_RANK_OUT, dense1_b_dims);

        dense1BiasDataSet.read(dense1_b, PredType::NATIVE_FLOAT, dense1BiasMemSpace, dense1BiasDataSpace);

        /*
        * Parse Dense2 weights
        */
        DataSet dense2WeightsDataSet = file.openDataSet(DENSE2_W);
        DataSpace dense2WeightsDataSpace = dense2WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t dense2_w_dims[2];
        dense2_w_dims[0] = DENSE2_W_NY;
        dense2_w_dims[1] = DENSE2_W_NX;
        DataSpace dense2WeightsMemSpace(DENSE2_W_RANK_OUT, dense2_w_dims);

        dense2WeightsDataSet.read(dense2_w, PredType::NATIVE_FLOAT, dense2WeightsMemSpace, dense2WeightsDataSpace);

        /*
        * Parse Dense2 bias
        */
        DataSet dense2BiasDataSet = file.openDataSet(DENSE2_b);
        DataSpace dense2BiasDataSpace = dense2BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t dense2_b_dims[1];
        dense2_b_dims[0] = DENSE2_b_N;
        DataSpace dense2BiasMemSpace(DENSE2_b_RANK_OUT, dense2_b_dims);

        dense2BiasDataSet.read(dense2_b, PredType::NATIVE_FLOAT, dense2BiasMemSpace, dense2BiasDataSpace);

        /*
        * Parse Dense3 weights
        */
        DataSet dense3WeightsDataSet = file.openDataSet(DENSE3_W);
        DataSpace dense3WeightsDataSpace = dense3WeightsDataSet.getSpace();

        // Define the memory dataspace.
        hsize_t dense3_w_dims[2];
        dense3_w_dims[0] = DENSE3_W_NY;
        dense3_w_dims[1] = DENSE3_W_NX;
        DataSpace dense3WeightsMemSpace(DENSE3_W_RANK_OUT, dense3_w_dims);

        dense3WeightsDataSet.read(dense3_w, PredType::NATIVE_FLOAT, dense3WeightsMemSpace, dense3WeightsDataSpace);

        /*
        * Parse Dense3 bias
        */
        DataSet dense3BiasDataSet = file.openDataSet(DENSE3_b);
        DataSpace dense3BiasDataSpace = dense3BiasDataSet.getSpace();

        // Define the memory dataspace.

        hsize_t dense3_b_dims[1];
        dense3_b_dims[0] = DENSE3_b_N;
        DataSpace dense3BiasMemSpace(DENSE3_b_RANK_OUT, dense3_b_dims);

        dense3BiasDataSet.read(dense3_b, PredType::NATIVE_FLOAT, dense3BiasMemSpace, dense3BiasDataSpace);
        cout << "Weights and biases parsed." << endl;
    }  // end of try block

        // catch failure caused by the H5File operations
    catch( FileIException &error )
    {
        error.printError();
    }
        // catch failure caused by the DataSet operations
    catch( DataSetIException &error )
    {
        error.printError();
    }
        // catch failure caused by the DataSpace operations
    catch( DataSpaceIException &error )
    {
        error.printError();
    }
        // catch failure caused by the DataSpace operations
    catch( DataTypeIException &error )
    {
        error.printError();
    }
}

void AlexNetWeightParser::initArrays() {
    int i, j, k, l;

    // conv1_w array
    for (i = 0; i < CONV1_W_NK; i++) {
        for (j = 0; j < CONV1_W_NZ; j++) {
            for (k = 0; k < CONV1_W_NY; k++) {
                for (l = 0; l < CONV1_W_NX ; l++) {
                    conv1_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv1_b array
    for (i = 0; i < CONV1_b_N; i++) {
        conv1_b[i] = 0;
    }

    // conv2_1_w array
    for (i = 0; i < CONV2_1_W_NK; i++) {
        for (j = 0; j < CONV2_1_W_NZ; j++) {
            for (k = 0; k < CONV2_1_W_NY; k++) {
                for (l = 0; l < CONV2_1_W_NX ; l++) {
                    conv2_1_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv2_1_b array
    for (i = 0; i < CONV2_1_b_N; i++) {
        conv2_1_b[i] = 0;
    }

    // conv2_2_w array
    for (i = 0; i < CONV2_2_W_NK; i++) {
        for (j = 0; j < CONV2_2_W_NZ; j++) {
            for (k = 0; k < CONV2_2_W_NY; k++) {
                for (l = 0; l < CONV2_2_W_NX ; l++) {
                    conv2_2_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv2_2_b array
    for (i = 0; i < CONV2_2_b_N; i++) {
        conv2_2_b[i] = 0;
    }

    // conv3_w array
    for (i = 0; i < CONV3_W_NK; i++) {
        for (j = 0; j < CONV3_W_NZ; j++) {
            for (k = 0; k < CONV3_W_NY; k++) {
                for (l = 0; l < CONV3_W_NX ; l++) {
                    conv3_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv3_b array
    for (i = 0; i < CONV3_b_N; i++) {
        conv3_b[i] = 0;
    }

    // conv4_1_w array
    for (i = 0; i < CONV4_1_W_NK; i++) {
        for (j = 0; j < CONV4_1_W_NZ; j++) {
            for (k = 0; k < CONV4_1_W_NY; k++) {
                for (l = 0; l < CONV4_1_W_NX ; l++) {
                    conv4_1_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv4_1_b array
    for (i = 0; i < CONV4_1_b_N; i++) {
        conv4_1_b[i] = 0;
    }

    // conv4_2_w array
    for (i = 0; i < CONV4_2_W_NK; i++) {
        for (j = 0; j < CONV4_2_W_NZ; j++) {
            for (k = 0; k < CONV4_2_W_NY; k++) {
                for (l = 0; l < CONV4_2_W_NX ; l++) {
                    conv4_2_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv4_2_b array
    for (i = 0; i < CONV4_2_b_N; i++) {
        conv4_2_b[i] = 0;
    }

    // conv5_1_w array
    for (i = 0; i < CONV5_1_W_NK; i++) {
        for (j = 0; j < CONV5_1_W_NZ; j++) {
            for (k = 0; k < CONV5_1_W_NY; k++) {
                for (l = 0; l < CONV5_1_W_NX ; l++) {
                    conv5_1_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv5_1_b array
    for (i = 0; i < CONV5_1_b_N; i++) {
        conv5_1_b[i] = 0;
    }

    // conv5_2_w array
    for (i = 0; i < CONV5_2_W_NK; i++) {
        for (j = 0; j < CONV5_2_W_NZ; j++) {
            for (k = 0; k < CONV5_2_W_NY; k++) {
                for (l = 0; l < CONV5_2_W_NX ; l++) {
                    conv5_2_w[i][j][k][l] = 0;
                }
            }
        }
    }

    // conv5_2_b array
    for (i = 0; i < CONV5_2_b_N; i++) {
        conv5_2_b[i] = 0;
    }

    // dense1_w array
    for (i = 0; i < DENSE1_W_NY; i++) {
        for (j = 0; j < DENSE1_W_NX; j++) {
            //dense1_w[i][j] = 0;
        }
    }

    // dense1_b array
    for (i = 0; i < DENSE1_b_N; i++) {
        dense1_b[i] = 0;
    }

    // dense2_w array
    for (i = 0; i < DENSE2_W_NY; i++) {
        for (j = 0; j < DENSE2_W_NX; j++) {
            dense2_w[i][j] = 0;
        }
    }

    // dense2_b array
    for (i = 0; i < DENSE2_b_N; i++) {
        dense2_b[i] = 0;
    }

    // dense3_w array
    for (i = 0; i < DENSE3_W_NY; i++) {
        for (j = 0; j < DENSE3_W_NX; j++) {
            dense3_w[i][j] = 0;
        }
    }

    // dense3_b array
    for (i = 0; i < DENSE3_b_N; i++) {
        dense3_b[i] = 0;
    }
    cout << "Inited arrays." << endl;
}

void AlexNetWeightParser::initMatrices() {
    int i, j;

    // eigen_conv1_w FourDMatrix
    eigen_conv1_w->resize(CONV1_W_NK, CONV1_W_NZ);
    for (i = 0; i < CONV1_W_NK; i++) {
        for (j = 0; j < CONV1_W_NZ; j++) {
            (*eigen_conv1_w)(i, j).resize(CONV1_W_NY, CONV1_W_NX);
        }
    }

    // eigen_conv1_b Vector
    eigen_conv1_b->resize(CONV1_b_N);

    // eigen_conv2_1_w FourDMatrix
    eigen_conv2_1_w->resize(CONV2_1_W_NK, CONV2_1_W_NZ);
    for (i = 0; i < CONV2_1_W_NK; i++) {
        for (j = 0; j < CONV2_1_W_NZ; j++) {
            (*eigen_conv2_1_w)(i, j).resize(CONV2_1_W_NY, CONV2_1_W_NX);
        }
    }

    // eigen_conv2_1_b Vector
    eigen_conv2_1_b->resize(CONV2_1_b_N);

    // eigen_conv2_2_w FourDMatrix
    eigen_conv2_2_w->resize(CONV2_2_W_NK, CONV2_2_W_NZ);
    for (i = 0; i < CONV2_2_W_NK; i++) {
        for (j = 0; j < CONV2_2_W_NZ; j++) {
            (*eigen_conv2_2_w)(i, j).resize(CONV2_2_W_NY, CONV2_2_W_NX);
        }
    }

    // eigen_conv2_2_b Vector
    eigen_conv2_2_b->resize(CONV2_2_b_N);

    // eigen_conv3_w FourDMatrix
    eigen_conv3_w->resize(CONV3_W_NK, CONV3_W_NZ);
    for (i = 0; i < CONV3_W_NK; i++) {
        for (j = 0; j < CONV3_W_NZ; j++) {
            (*eigen_conv3_w)(i, j).resize(CONV3_W_NY, CONV3_W_NX);
        }
    }

    // eigen_conv3_b Vector
    eigen_conv3_b->resize(CONV3_b_N);

    // eigen_conv4_1_w FourDMatrix
    eigen_conv4_1_w->resize(CONV4_1_W_NK, CONV4_1_W_NZ);
    for (i = 0; i < CONV4_1_W_NK; i++) {
        for (j = 0; j < CONV4_1_W_NZ; j++) {
            (*eigen_conv4_1_w)(i, j).resize(CONV4_1_W_NY, CONV4_1_W_NX);
        }
    }

    // eigen_conv4_1_b Vector
    eigen_conv4_1_b->resize(CONV4_1_b_N);

    // eigen_conv4_2_w FourDMatrix
    eigen_conv4_2_w->resize(CONV4_2_W_NK, CONV4_2_W_NZ);
    for (i = 0; i < CONV4_2_W_NK; i++) {
        for (j = 0; j < CONV4_2_W_NZ; j++) {
            (*eigen_conv4_2_w)(i, j).resize(CONV4_2_W_NY, CONV4_2_W_NX);
        }
    }

    // eigen_conv4_2_b Vector
    eigen_conv4_2_b->resize(CONV4_2_b_N);

    // eigen_conv5_1_w FourDMatrix
    eigen_conv5_1_w->resize(CONV5_1_W_NK, CONV5_1_W_NZ);
    for (i = 0; i < CONV5_1_W_NK; i++) {
        for (j = 0; j < CONV5_1_W_NZ; j++) {
            (*eigen_conv5_1_w)(i, j).resize(CONV5_1_W_NY, CONV5_1_W_NX);
        }
    }

    // eigen_conv5_1_b Vector
    eigen_conv5_1_b->resize(CONV5_1_b_N);

    // eigen_conv5_2_w FourDMatrix
    eigen_conv5_2_w->resize(CONV5_2_W_NK, CONV5_2_W_NZ);
    for (i = 0; i < CONV5_2_W_NK; i++) {
        for (j = 0; j < CONV5_2_W_NZ; j++) {
            (*eigen_conv5_2_w)(i, j).resize(CONV5_2_W_NY, CONV5_2_W_NX);
        }
    }

    // eigen_conv5_2_b Vector
    eigen_conv5_2_b->resize(CONV5_2_b_N);

    // eigen_dense1_w Matrix
    eigen_dense1_w->resize(DENSE1_W_NY, DENSE1_W_NX);

    // eigen_dense1_b Vector
    eigen_dense1_b->resize(DENSE1_b_N);

    // eigen_dense2_w Matrix
    eigen_dense2_w->resize(DENSE2_W_NY, DENSE2_W_NX);

    // eigen_dense2_b Vector
    eigen_dense2_b->resize(DENSE2_b_N);

    // eigen_dense3_w Matrix
    eigen_dense3_w->resize(DENSE3_W_NY, DENSE3_W_NX);

    // eigen_dense3_b Vector
    eigen_dense3_b->resize(DENSE3_b_N);

    cout << "Inited matrices." << endl;
}

void AlexNetWeightParser::setWeights() {
    int i, j, k, l;

    // eigen_conv1_w
    for (i = 0; i < CONV1_W_NK; i++) {
        for (j = 0; j < CONV1_W_NZ; j++) {
            for (k = 0; k < CONV1_W_NY; k++) {
                for (l = 0; l < CONV1_W_NX; l++) {
                    (*eigen_conv1_w)(i, j)(k, l) = conv1_w[i][j][k][l];
                }
            }
        }
    }


    // eigen_conv1_b
    /*for (i = 0; i < CONV1_b_N; i++) {
        (*eigen_conv1_b)(i) = conv1_b[i];
    }*/

    (*eigen_conv1_b) = Eigen::Map<Vector>(conv1_b, CONV1_b_N);


    // eigen conv2_1_w
    for (i = 0; i < CONV2_1_W_NK; i++) {
        for (j = 0; j < CONV2_1_W_NZ; j++) {
            for (k = 0; k < CONV2_1_W_NY; k++) {
                for (l = 0; l < CONV2_1_W_NX; l++) {
                    (*eigen_conv2_1_w)(i, j)(k, l) = conv2_1_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv2_1_b
    /*for (i = 0; i < CONV2_1_b_N; i++) {
        (*eigen_conv2_1_b)(i) = conv2_1_b[i];
    }*/

    (*eigen_conv2_1_b) = Eigen::Map<Vector>(conv2_1_b, CONV2_1_b_N);

    // eigen conv2_2_w
    for (i = 0; i < CONV2_2_W_NK; i++) {
        for (j = 0; j < CONV2_2_W_NZ; j++) {
            for (k = 0; k < CONV2_2_W_NY; k++) {
                for (l = 0; l < CONV2_2_W_NX; l++) {
                    (*eigen_conv2_2_w)(i, j)(k, l) = conv2_2_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv2_2_b
    /*for (i = 0; i < CONV2_2_b_N; i++) {
        (*eigen_conv2_2_b)(i) = conv2_2_b[i];
    }*/

    (*eigen_conv2_2_b) = Eigen::Map<Vector>(conv2_2_b, CONV2_2_b_N);

    // eigen_conv3_w
    for (i = 0; i < CONV3_W_NK; i++) {
        for (j = 0; j < CONV3_W_NZ; j++) {
            for (k = 0; k < CONV3_W_NY; k++) {
                for (l = 0; l < CONV3_W_NX; l++) {
                    (*eigen_conv3_w)(i, j)(k, l) = conv3_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv3_b
    /*for (i = 0; i < CONV3_b_N; i++) {
        (*eigen_conv3_b)(i) = conv3_b[i];
    }*/

    (*eigen_conv3_b) = Eigen::Map<Vector>(conv3_b, CONV3_b_N);

    // eigen conv4_1_w
    for (i = 0; i < CONV4_1_W_NK; i++) {
        for (j = 0; j < CONV4_1_W_NZ; j++) {
            for (k = 0; k < CONV4_1_W_NY; k++) {
                for (l = 0; l < CONV4_1_W_NX; l++) {
                    (*eigen_conv4_1_w)(i, j)(k, l) = conv4_1_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv4_1_b
    /*for (i = 0; i < CONV4_1_b_N; i++) {
        (*eigen_conv4_1_b)(i) = conv4_1_b[i];
    }*/
    (*eigen_conv4_1_b) = Eigen::Map<Vector>(conv4_1_b, CONV4_1_b_N);

    // eigen conv4_2_w
    for (i = 0; i < CONV4_2_W_NK; i++) {
        for (j = 0; j < CONV4_2_W_NZ; j++) {
            for (k = 0; k < CONV4_2_W_NY; k++) {
                for (l = 0; l < CONV4_2_W_NX; l++) {
                    (*eigen_conv4_2_w)(i, j)(k, l) = conv4_2_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv4_2_b
    /*for (i = 0; i < CONV4_2_b_N; i++) {
        (*eigen_conv4_2_b)(i) = conv4_2_b[i];
    }*/

    (*eigen_conv4_2_b) = Eigen::Map<Vector>(conv4_2_b, CONV4_2_b_N);

    // eigen conv5_1_w
    for (i = 0; i < CONV5_1_W_NK; i++) {
        for (j = 0; j < CONV5_1_W_NZ; j++) {
            for (k = 0; k < CONV5_1_W_NY; k++) {
                for (l = 0; l < CONV5_1_W_NX; l++) {
                    (*eigen_conv5_1_w)(i, j)(k, l) = conv5_1_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv5_1_b
    /*for (i = 0; i < CONV5_1_b_N; i++) {
        (*eigen_conv5_1_b)(i) = conv5_1_b[i];
    }*/

    (*eigen_conv5_1_b) = Eigen::Map<Vector>(conv5_1_b, CONV5_1_b_N);

    // eigen conv5_2_w
    for (i = 0; i < CONV5_2_W_NK; i++) {
        for (j = 0; j < CONV5_2_W_NZ; j++) {
            for (k = 0; k < CONV5_2_W_NY; k++) {
                for (l = 0; l < CONV5_2_W_NX; l++) {
                    (*eigen_conv5_2_w)(i, j)(k, l) = conv5_2_w[i][j][k][l];
                }
            }
        }
    }

    // eigen_conv5_2_b
    /*for (i = 0; i < CONV5_2_b_N; i++) {
        (*eigen_conv5_2_b)(i) = conv5_2_b[i];
    }*/
    (*eigen_conv5_2_b) = Eigen::Map<Vector>(conv5_2_b, CONV5_2_b_N);

    // eigen_dense1_w
    for (i = 0; i < DENSE1_W_NY; i++) {
        for (j = 0; j < DENSE1_W_NX; j++) {
            (*eigen_dense1_w)(i, j) = dense1_w[i][j];
        }
    }
    //(*eigen_dense1_w) = Eigen::Map<Matrix>(dense1_w, DENSE1_W_NY, DENSE1_W_NX);

    // eigen_dense1_b
    /*for (i = 0; i < DENSE1_b_N; i++) {
        (*eigen_dense1_b)(i) = dense1_b[i];
    }*/

    (*eigen_dense1_b) = Eigen::Map<Vector>(dense1_b, DENSE1_b_N);

    // eigen_dense2_w
    for (i = 0; i < DENSE2_W_NY; i++) {
        for (j = 0; j < DENSE2_W_NX; j++) {
            (*eigen_dense2_w)(i, j) = dense2_w[i][j];
        }
    }

    // eigen_dense2_b
    /*for (i = 0; i < DENSE2_b_N; i++) {
        (*eigen_dense2_b)(i) = dense2_b[i];
    }*/

    (*eigen_dense2_b) = Eigen::Map<Vector>(dense2_b, DENSE2_b_N);


    // eigen_dense3_w
    for (i = 0; i < DENSE3_W_NY; i++) {
        for (j = 0; j < DENSE3_W_NX; j++) {
            (*eigen_dense3_w)(i, j) = dense3_w[i][j];
        }
    }

    // eigen_dense3_b
    /*for (i = 0; i < DENSE3_b_N; i++) {
        (*eigen_dense3_b)(i) = dense3_b[i];
    }*/

    (*eigen_dense3_b) = Eigen::Map<Vector>(dense3_b, DENSE3_b_N);


    cout << "Weights and biases set." << endl;
}

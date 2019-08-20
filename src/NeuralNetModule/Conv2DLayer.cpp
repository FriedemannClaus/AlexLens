/**
* Project Entwurf_PSE_KNN
* @author Friedemann Claus
*/



#include "Conv2DLayer.h"

Conv2DLayer::Conv2DLayer(int forcedInputSize, int stride, int zeroPadWidth, FourDMatrix& weights, Vector& bias) :
        FORCED_INPUT_SIZE(forcedInputSize),
        STRIDE(stride),
        ZERO_PAD_WIDTH(zeroPadWidth),
        weights(weights),
        bias(bias)
{}


void Conv2DLayer::forward(ThreeDMatrix &input, ThreeDMatrix &output) {

    // Calculate some Parameters
    int kernels = weights.rows();
    int kernelSize = weights(0, 0).cols(); //rows() would work too, kernels are a square.
    int inputDepth = weights.cols(); //inputDepth shall be the depth of the kernels. Get's asserted later
    int paddedInputSize = FORCED_INPUT_SIZE + (2 * ZERO_PAD_WIDTH);

    int outputSize = (FORCED_INPUT_SIZE - kernelSize + 2 * ZERO_PAD_WIDTH)/STRIDE + 1; //(227 - 11 - 2*0)/4 + 1 = 55 at Conv-1

    int lastTopLeftPosition = paddedInputSize - kernelSize; //last position of top left pixel of kernel.

    int slides = (lastTopLeftPosition/ STRIDE) + 1;
    cout << "this layer performs" << slides << "slides in one direction";
    assert(slides > 0);

    // Assert the input-size
    assert(input.rows() == inputDepth);
    assert(input(0).rows() == FORCED_INPUT_SIZE);
    assert(input(0).cols() == FORCED_INPUT_SIZE);


    //Zero-Pad the input
    ThreeDMatrix paddedInput;
    if (ZERO_PAD_WIDTH != 0) {
        zeroPad(input,paddedInput, ZERO_PAD_WIDTH);
    } else {
        paddedInput = input; //We calculate with the paddedInput
    }

    assert(paddedInput.rows() == inputDepth);
    assert(paddedInput(0).cols() == paddedInputSize );

    //resize output 3DMatrix
    output.resize(kernels);
    for (int i = 0; i < kernels; ++i) {
        output(i).resize(outputSize, outputSize);
    }

    //Needed for iteration:
    float kernelResult;
    //apply filters
    for (int kernel = 0; kernel < kernels; ++kernel) { //for every kernel
        for (int row = 0; row <= lastTopLeftPosition; row += STRIDE) {
            for (int col = 0; col <= lastTopLeftPosition; col += STRIDE) { //slide over 2DPosition of kernel
                kernelResult = 0;

                for (int depth = 0; depth < inputDepth; ++depth) {
                    //In Eigen, iterating firstly over the columns and secondly over the rows is more efficient.
                    for (int j = 0; j < kernelSize; ++j) {
                        for (int i = 0; i < kernelSize; ++i) {
                            kernelResult += weights(kernel, depth)(i, j) * paddedInput(depth)(row + i, col + j);
                        }
                    }
                }
                output(kernel)(row / STRIDE, col / STRIDE) = kernelResult + bias(kernel); //Finished a position of a kernel.
                // There are (lastTopLeftPosition / STRIDE)² positions a kernel gets applied to.
            }
        }
    }
}



void Conv2DLayer::zeroPad(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output, int zeroPadWidth) {

//    if(zeroPadWidth == 0) {
//        throw NeuralNetException();
//    }
    int sideLength = input(0).cols() + 2 * zeroPadWidth;
    output.resize(input.rows()); // Matrices get resized in the overall for-loop
    assert(output.rows() == input.rows());

    int oldSideLength = input(0).cols();
    for (int depth = 0; depth < input.rows(); ++depth) {
        output(depth).resize(sideLength, sideLength);
        output(depth).setZero(); //TODO should work

        //In Eigen, iterating firstly over the columns and secondly over the rows is more efficient.
        for (int j = 0; j < oldSideLength; j++) {
            for (int i = 0; i < oldSideLength; i++) {
                output(depth)(i + zeroPadWidth, j + zeroPadWidth) = input(depth)(i, j);
            }
        }
    }
}



void Conv2DLayer::setWeights(const Layer::FourDMatrix &weights, const Layer::Vector &bias) {
    this->weights = weights;
    this->bias = bias;
}

/**
* Project Entwurf_PSE_KNN
* @author Friedemann Claus
*/


#include "Conv2DLayer.h"

/**
 * Constructor
 * @param stride The stride of the Conv-Layer
 * @param ZeroPadding Whether Zero-Padding shall be used
 * @param weights The weights of the Conv-Layer
 * @param bias The bias of the Conv-Layer
 */
Conv2DLayer::Conv2DLayer(int stride, bool ZeroPadding, FourDMatrix& weights, Vector& bias) :
        STRIDE(stride),
        ZERO_PADDING(ZeroPadding),
        weights(weights),
        bias(bias)
{}

/**
 * The forward-propagation-function
 * @param input The 3D-Input-Matrix
 * @param output The 3D-Output-Matrix
 */
void Conv2DLayer::forward(const ThreeDMatrix &input, ThreeDMatrix &output) {
    ThreeDMatrix paddedInput;
    if (ZERO_PADDING == true) {zeroPad(input,paddedInput);}

    // Calculate some Parameters
    int kernels = weights.rows();
    int kernelSize = weights(0, 0).cols(); //rows() would work too, kernels are a square.
    int paddedInputSize = paddedInput(0).cols();
    int inputDepth = input.rows(); //doesn't change with padding

    int lastTopLeftPosition = paddedInputSize - kernelSize; //last Position of Top Left Pixel of kernel.

    //resize output 3DMatrix
    output.resize(kernels);
    for (int i = 0; i < kernels; ++i) {
        output.resize(kernelSize, kernelSize);
    }

    //Needed for iteration:
    float kernelResult;

    //apply filters
    for (int kernel = 0; kernel < kernels; ++kernel) { //for every kernel
        for (int row = 0; row < lastTopLeftPosition; row += STRIDE) {
            for (int col = 0; col < lastTopLeftPosition; col += STRIDE) { //slide over 2DPosition of kernel
                kernelResult = 0;

                for (int depth = 0; depth < inputDepth; ++depth) {
                    //In Eigen, iterating firstly over the columns and secondly over the rows is more efficient.
                    for (int j = 0; j < kernelSize; ++j) {
                        for (int i = 0; i < kernelSize; ++i) {
                            kernelResult += weights(kernel, depth)(i, j) * paddedInput(depth)(row + i, col + j);
                        }
                    }
                }
                output(kernel)(row, col) = kernelResult;
            }
        }
    }
}


/**
 * The zero-padding-function
 * @param input The 3D-Input-Matrix to be padded
 * @param output The 3D-Output-Matrix
 */
void Conv2DLayer::zeroPad(const Layer::ThreeDMatrix &input, Layer::ThreeDMatrix &output) {
    int zeroPadWidth = weights(0,0).cols() / 2; //div
    int sideLength = input(0).cols() + 2 * zeroPadWidth;
    output.resize(input.rows());


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


/**
 * A setter-method for the weights
 * @param weights the new weights of the Conv-Layer
 * @param bias the new bias of the Conv-Layer
 */
void Conv2DLayer::setWeights(const Layer::FourDMatrix &weights, const Layer::Vector &bias) {
    this->weights = weights;
    this->bias = bias;
}

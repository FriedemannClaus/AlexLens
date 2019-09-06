//
// Created by viet on 01.09.19.
//
#ifndef SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H
#define SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H

#include <string>
#include <CL/cl.h>
#include <iostream>
#include <fstream>
#include <cstdlib>

using std::cerr;
using std::endl;
using std::ofstream;
using namespace std;

/**
 * Interface class for communication with the GPU device.
 * Performs matrix multiplication on the GPU device
 */
class GPUSGeMM {
private:
    const unsigned int WA; ///Width of the left input matrix
    const unsigned int HA; ///Height of the left input matrix
    const unsigned int WB; ///Width of the right input matrix
    const unsigned int HB = WA; ///Height of the right input matrix
    const unsigned int WC = WB; ///Width of the output matrix
    const unsigned int HC = HA; ///Height of the output matrix
public:
    /**
     * GPUSeGMM class constructor
     *
     * @param wA width of the left matrix
     * @param hA height of the left matrix
     * @param wB width of the right matrix
     */
    GPUSGeMM(int wA, int hA, int wB) :
            WA(wA),
            HA(hA),
            WB(wB) {}

    /**
     * Computes the result of the matrix multiplication on the GPU device.
     * We use a kernel implementation from https://github.com/CNugteren/myGEMM/blob/master/src/kernels.cl
     * @param A left matrix
     * @param B right matrix
     * @param C result matrix
     */
    void convolve(float *A, float *B, float *C);
};

#endif //SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H

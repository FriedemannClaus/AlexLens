//
// Created by viet on 01.09.19.
//

#ifndef SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H
#define SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H

#include <string>
//#include <CL/cl.h>
#include <iostream>
#include <array>

using namespace std;


class GPUSGeMM {
private:
    const int WA;
    const int HA;
    const int WB;
    const int HB = WA;
    const int WC = WB;
    const int HC = HA;
    void randomInit(float* data, int size);
public:
    GPUSGeMM(int wA, int hA, int wB):
            WA(wA),
            HA(hA),
            WB(wB)
    {}
    void convolve(float* A, float* B, float* C);
};


#endif //SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H

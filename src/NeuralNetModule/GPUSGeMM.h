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


class GPUSGeMM {
private:
    const unsigned int WA;
    const unsigned int HA;
    const unsigned int WB;
    const unsigned int HB = WA;
    const unsigned int WC = WB;
    const unsigned int HC = HA;
public:
    GPUSGeMM(int wA, int hA, int wB):
            WA(wA),
            HA(hA),
            WB(wB)
    {}
    void convolve(float* A, float* B, float* C);
};


#endif //SRC_GUIMODULE_ALEXLENS_GPUSGEMM_H

//
// Created by viet on 01.09.19.
//

#include "GPUSGeMM.h"
#include <memory>
#define MAX_SOURCE_SIZE (0x10000)//geändert

void GPUSGeMM::convolve(float* A, float* B, float* C) {

    size_t kernelLength;
    // Load the kernel source code into the array source_str
    FILE *fp;
    fp = fopen("../../src/NeuralNetModule/kernel.cl", "r");
    if (!fp) {
        fprintf(stderr, "Failed to load kernel.\n");
        exit(1);
    }

    char *clMatrixMul = new char[MAX_SOURCE_SIZE];
    kernelLength = fread(clMatrixMul, 1, MAX_SOURCE_SIZE, fp);
    fclose(fp);
    if (clMatrixMul == NULL) exit(-1);

    // Configure the OpenCL environment
    cl_platform_id platform =0;
    clGetPlatformIDs(1, &platform, NULL);
    cl_device_id device = 0;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);
    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, NULL);
    cl_command_queue queue = clCreateCommandQueue(context, device, 0, NULL);
    char deviceName[1024];
    clGetDeviceInfo(device, CL_DEVICE_NAME, 1024, deviceName, NULL);
    cl_event event = NULL;

    // Compile the kernel
    cl_program program = clCreateProgramWithSource(context, 1, (const char **) &clMatrixMul, &kernelLength, NULL);
    clBuildProgram(program, 0, NULL, "", NULL, NULL);

    // Check for compilation errors
    size_t logSize;
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, 0, NULL, &logSize);
    char *messages = new char[logSize];
    clGetProgramBuildInfo(program, device, CL_PROGRAM_BUILD_LOG, logSize, messages, NULL);
    messages[logSize] = '\0';
    if (logSize > 10) { printf(">>> Compiler message: %s\n", messages); }
    //free(messages);
    delete[]messages;

    // Prepare OpenCL memory objects
    cl_mem bufA = clCreateBuffer(context, CL_MEM_READ_ONLY, HA * WA * sizeof(float), NULL, NULL);
    cl_mem bufB = clCreateBuffer(context, CL_MEM_READ_ONLY, HB * WB * sizeof(float), NULL, NULL);
    cl_mem bufC = clCreateBuffer(context, CL_MEM_READ_WRITE, HC * WC * sizeof(float), NULL, NULL);

    // Copy matrices to the GPU
    clEnqueueWriteBuffer(queue, bufA, CL_TRUE, 0, HA * WA * sizeof(float), A, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufB, CL_TRUE, 0, HB * WB * sizeof(float), B, 0, NULL, NULL);
    clEnqueueWriteBuffer(queue, bufC, CL_TRUE, 0, HC * WC * sizeof(float), C, 0, NULL, NULL);

    // Configure the myGEMM kernel and set its arguments
    cl_kernel kernel = clCreateKernel(program, "myGEMM1", NULL);
    clSetKernelArg(kernel, 0, sizeof(int), (void *) &HA);
    clSetKernelArg(kernel, 1, sizeof(int), (void *) &WB);
    clSetKernelArg(kernel, 2, sizeof(int), (void *) &WA);
    clSetKernelArg(kernel, 3, sizeof(cl_mem), (void *) &bufA);
    clSetKernelArg(kernel, 4, sizeof(cl_mem), (void *) &bufB);
    clSetKernelArg(kernel, 5, sizeof(cl_mem), (void *) &bufC);

    // Run the myGEMM kernel
    size_t TS = 16;
    const size_t local[2] = {1, 1};
    const size_t global[2] = {HC, WC};
    clEnqueueNDRangeKernel(queue, kernel, 2, NULL, global, local, 0, NULL, &event);

    // Copy the output matrix C back to the CPU memory
    clEnqueueReadBuffer(queue, bufC, CL_TRUE, 0, HC * WC * sizeof(float), C, 0, NULL, NULL);

    delete[]clMatrixMul;

    // Free the OpenCL memory objects
    clReleaseMemObject(bufA);
    clReleaseMemObject(bufB);
    clReleaseMemObject(bufC);

    // Clean-up OpenCL
    clReleaseCommandQueue(queue);
    clReleaseContext(context);
    clReleaseProgram(program);
    clReleaseKernel(kernel);
    clReleaseEvent(event);
    clReleaseDevice(device);
}

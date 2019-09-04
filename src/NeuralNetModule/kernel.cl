// Multiply two matrices A * B = C
// OpenCL Kernel
__kernel void myGEMM1(const int M, const int N, const int K,
                             const __global float* A,
                             const __global float* B,
                             __global float* C) {
            const int globalRow = get_global_id(0);
            const int globalCol = get_global_id(1);
            float acc = 0.0f;
            for (int i=0; i<K; i++) {
                acc += A[i + K*globalRow] * B[globalCol + N*i];
            }
            C[globalCol + N*globalRow] = acc;
        }
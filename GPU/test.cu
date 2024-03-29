#include <iostream>
#include <cuda_runtime.h>

__global__ void kernel() {

    // Perform computation
    printf("Thread (x: %d, y: %d, z: %d) block (x: %d, y: %d, z: %d)\n",
           threadIdx.x, threadIdx.y, threadIdx.z,
           blockIdx.x, blockIdx.y, blockIdx.z);
}

int main() {
    // Define grid and block dimensions
    int channels = 3;
    
    dim3 blockSize(1, 9, channels); // 8 threads per block

    // Launch kernel
    kernel<<<2/*block count*/, blockSize/*thread count*/>>>();

    // Check for errors
    cudaError_t error = cudaGetLastError();
    if (error != cudaSuccess) {
        std::cerr << "CUDA error: " << cudaGetErrorString(error) << std::endl;
        return 1;
    }

    // Wait for kernel to finish
    cudaDeviceSynchronize();

    return 0;
}
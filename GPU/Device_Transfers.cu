#include <stdio.h>
#include <stdlib.h>
#include "cuda.h"
#include "cuda_runtime.h" 

#define ARRAY_SIZE 256
#define NUM_BLOCKS  4
#define THREADS_PER_BLOCK 64
 
__global__ void negate(int *d_a)
{
  int idx = threadIdx.x;
  d_a[idx] = -1 * d_a[idx];
}
 
__global__ void negate_multiblock(int *d_a)
{
  int idx = threadIdx.x + (blockIdx.x * blockDim.x);
  d_a[idx] = -1 * d_a[idx];
}
 
int main(int argc, char *argv[])
{
    int *h_a, *h_out;
    int *d_a;
 
    int i;
    size_t siz_b = ARRAY_SIZE * sizeof(int);
    h_a = (int *) malloc(siz_b);
    h_out = (int *) malloc(siz_b);
 
    cudaMalloc(&d_a,sizeof(siz_b));
 
    for (i = 0; i < ARRAY_SIZE; i++) {
        h_a[i] = i;
        h_out[i] = 0;
    }   
 
    cudaMemcpy(&d_a, &h_a, siz_b, cudaMemcpyHostToDevice);
    dim3 blocksPerGrid(NUM_BLOCKS); 
    dim3 threadsPerBlock(THREADS_PER_BLOCK);
    negate<<<1,256>>>(d_a);
    negate_multiblock<<<blocksPerGrid,threadsPerBlock>>>();
    cudaDeviceSynchronize();
 
    cudaMemcpy(&h_out, &d_a, siz_b, cudaMemcpyDeviceToHost);
 
    printf("Results: ");
    for (i = 0; i < ARRAY_SIZE; i++) {
      printf("%d, ", h_out[i]);
    }
    printf("\n\n");
 
    cudaFree(d_a);
 
    free(h_a);
    free(h_out);
 
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "cuda.h"
#include "cuda_runtime.h" 
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../Include/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Include/stb_image.h"
#include <time.h>

clock_t start, stop;
double cpu_time;

#define BLOCK_SIZE 128

__global__ void applyConvolution(unsigned char* image, unsigned char* output, int width, int height, int channels) {
    const float kernel[9] = {
        1, 0, -1,
        1, 0, -1,
        1, 0, -1
    };

    __shared__ float r = 0.0, g = 0.0, b = 0.0, a = 0.0; // dit moet nog global voor de hele block 

    int blockid = blockIdx.x + blockIdx.y * gridDim.x;

    int x = blockid % width;
    int y = blockid / width;

    int convolutie_kernel_x = (threadIdx.y %3)-1;
    int convolutie_kernel_Y = (threadIdx.y /3)-1;
    int ch = threadIdx.z;

    while (y < height) {
        

        int absolute_x = x + convolutie_kernel_x;
        int absolute_y = y + convolutie_kernel_Y;
                
                switch (ch)
                {
                case 0:
                    r += kernel[threadIdx.y]* image[(absolute_y * width + absolute_x) * channels + ch];
                    break;
                case 1:
                    g += kernel[threadIdx.y]* image[(absolute_y * width + absolute_x) * channels + ch];
                    break;
                case 2:
                    b += kernel[threadIdx.y]* image[(absolute_y * width + absolute_x) * channels + ch];
                    break;
                case 3:
                    a += kernel[threadIdx.y]* image[(absolute_y * width + absolute_x) * channels + ch];
                    break;
                default:
                    break;
                }
            __syncthreads();


        if(threadIdx.y == 0){
            switch (ch)
            {
                case 0:
                    output[(y * width + x) * channels + ch] = (unsigned char)(r > 255 ? 255 : (r < 0 ? 0 : r));
                    break;
                case 1:
                    output[(y * width + x) * channels + ch] = (unsigned char)(g > 255 ? 255 : (g < 0 ? 0 : g));
                    break;
                case 2:
                    output[(y * width + x) * channels + ch] = (unsigned char)(b > 255 ? 255 : (b < 0 ? 0 : b));
                    break;
                case 3:
                    output[(y * width + x) * channels + ch] = (unsigned char)(a > 255 ? 255 : (a < 0 ? 0 : a));
                    break;
                default:
                    break;
            }
        }

        blockid += gridDim.y * gridDim.x;
        x = blockid % width;
        y = blockid / width;
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        exit(1);
    }

    // Define your convolution kernel
   

    unsigned char* outputImg = (unsigned char*)malloc(width * height * channels);

    start =clock();

        unsigned char* d_img;
        cudaMalloc(&d_img, width * height * channels);
        cudaMemcpy(d_img, img, width * height * channels, cudaMemcpyHostToDevice);

        unsigned char* d_outputImg;
        cudaMalloc(&d_outputImg, width * height * channels);

        dim3 blockSize(1,9,channels);
        dim3 gridSize();
    
        applyConvolution<<<1023, 256>>>(d_img, d_outputImg, width, height, channels);
    
    
        cudaDeviceSynchronize();
        cudaMemcpy(outputImg, d_outputImg, width * height * channels, cudaMemcpyDeviceToHost);
    
    stop =clock();
    cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time);

    if (strcmp(argv[2], "noOut") != 0) {
        char OutputPath[100];
        snprintf(OutputPath, sizeof(OutputPath), "%s-output.png", argv[1]);
        stbi_write_png(OutputPath, width, height, channels, outputImg, width * channels);
    }

    stbi_image_free(img);
    free(outputImg);

    cudaFree(d_img);
    cudaFree(d_outputImg);
    return 0;
}
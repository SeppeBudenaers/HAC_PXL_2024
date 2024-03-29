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
//__constant__ float kernel[9];


__global__ void applyConvolution(unsigned char* image, unsigned char* output, int width, int height, int channels) {
    // shared memory broken once accessing shared memory ever varaible will be set to zero ?

    __shared__ float RGBA[9*4];
    
    int blockid = blockIdx.x + blockIdx.y * gridDim.x;
    int out_x = blockid % (width - 2); // Adjust for the convolution window size
    int out_y = blockid / (width - 2); // Adjust for the convolution window size
    // Calculate absolute position in the original image
    int absolute_x = out_x + 1;
    int absolute_y = out_y + 1;
    int ch = threadIdx.z;
    int color_offset = ch * 9;
    int kernel = 0 ;
    switch (threadIdx.y)
    {
    case 0:
    case 3:
    case 6:
        kernel = 1;
        break;
    case 2:
    case 5:
    case 8:
        kernel = -1;
        break;
    
    default:
        break;
    }
    

    while (blockid < width * height) {
        if(absolute_x != 0 && absolute_x <= (width-1) && absolute_y != 0 && absolute_y  < (height-1)){
            __syncthreads();
            int convolutie_kernel_x = (threadIdx.y %3)-1;
            int convolutie_kernel_y = (threadIdx.y /3)-1;
            int thread_pixel_x = absolute_x + convolutie_kernel_x;
            int thread_pixel_y = absolute_y + convolutie_kernel_y;
            

            int calculation = (image[(thread_pixel_y * width + thread_pixel_x) * channels + ch]*kernel);
            //printf("pixel x: %d y: %d with: %d and kernel:%d calculation: %d\n",thread_pixel_x,thread_pixel_y,image[(thread_pixel_y * width + thread_pixel_x) * channels + ch],kernel,calculation);
            printf("calculating x: %d :Y %d  on pixel x: %d y: %d r:%f + calculation: %d \n",absolute_x,absolute_y,thread_pixel_x,thread_pixel_y,RGBA[ch],calculation);
            //printf("r: %f\n",RGBA[threadIdx.y + color_offset] + calculation);
            RGBA[threadIdx.y + color_offset] = RGBA[threadIdx.y + color_offset] + calculation;
            __syncthreads();

            
            if(threadIdx.y == 0){
                int output_RGBA = 0;
                for (size_t i = 0; i < 9; i++)
                {
                  output_RGBA = output_RGBA + RGBA[i+ color_offset];
                }
                //printf("output: %d x: %d y: %d channel %d \n",output_RGBA,out_x,out_y,(((out_y) * (width-2) + (out_x)) * channels + ch));
                output[((out_y) * (width-2) + (out_x)) * channels + ch] = (unsigned char)(output_RGBA > 255 ? 255 : (output_RGBA < 0 ? 0 : output_RGBA));
         
            }
            __syncthreads();
        }
        blockid += gridDim.y * gridDim.x;
        if(threadIdx.y == 0){printf("block id : %d X; %d Y:%d\n",blockid,blockid % (width - 2)),blockid / (width - 2);}
        
        int out_x = blockid % (width - 2); // Adjust for the convolution window size
        int out_y = blockid / (width - 2); // Adjust for the convolution window size
        int absolute_x = out_x + 1;
        int absolute_y = out_y + 1;
        RGBA[threadIdx.y+ color_offset] = 0;
    }
}

int main(int argc, char* argv[]) {
    // if (argc < 2) {
    //     printf("Usage: %s <image_path>\n", argv[0]);
    //     return 1;
    // }

    // int width, height, channels;
    // unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
    // if (img == NULL) {
    //     printf("Error in loading the image\n");
    //     exit(1);
    // }

    // Define 
    unsigned char arr[] = {10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,10,10,10,0,0,0,};
    unsigned char output[16];

    printf("arr:\n");
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            printf("%2d ", arr[i * 6 + j]);
        }
        printf("\n");
    }
    
    // unsigned char* outputImg = (unsigned char*)malloc(width * height * channels);

    start =clock();
    
        unsigned char* d_arr;
        cudaMalloc(&d_arr, 36 * sizeof(float));
        cudaMemcpy(d_arr, arr, 36, cudaMemcpyHostToDevice);
        //unsigned char* d_img;
        // cudaMalloc(&d_img, width * height * channels);
        // cudaMemcpy(d_img, img, width * height * channels, cudaMemcpyHostToDevice);

        unsigned char* d_out;
        cudaMalloc(&d_out, 16* sizeof(float));
        // unsigned char* d_outputImg;
        // cudaMalloc(&d_outputImg, width * height * channels);
        int channels = 1;
        dim3 blockSize(1,9,channels);
        dim3 gridSize(1023,1023);
        
        // applyConvolution<<<gridSize, blockSize>>>(d_img, d_outputImg, width, height, channels);
        applyConvolution<<<gridSize, blockSize>>>(d_arr, d_out, 6, 6, channels);
    
        cudaDeviceSynchronize();
        // cudaMemcpy(outputImg, d_outputImg, width * height * channels, cudaMemcpyDeviceToHost);
        cudaMemcpy(output, d_out, 16, cudaMemcpyDeviceToHost);


    stop =clock();
    cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time);

    printf("Output array 4x4:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%2d ", output[i * 4 + j]);
        }
        printf("\n");
    }
        

    // if (strcmp(argv[2], "noOut") != 0) {
    //     char OutputPath[100];
    //     snprintf(OutputPath, sizeof(OutputPath), "%s-output.png", argv[1]);
    //     printf("path : %s",OutputPath);
    //     stbi_write_png(OutputPath, width, height, channels, outputImg, width * channels);
    // }

    // stbi_image_free(img);
    // free(outputImg);

    cudaFree(d_arr);
    cudaFree(d_out);
    // cudaFree(d_img);
    // cudaFree(d_outputImg);
    return 0;
}
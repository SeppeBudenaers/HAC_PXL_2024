%%writefile test.cu
#include <stdio.h>
#include <stdlib.h>
#include <cuda_runtime.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <math.h>

struct Pixel
{
    unsigned char r, g, b, a;
};

void ImageTransformCpu(unsigned char* imageRGBA, int width, int height, int centerX, int centerY)
{
    int radius = 120; // Radius for the effect
    int blockSize = 15; // Size of each pixelation block
    for (int y = 0; y < height; y += blockSize) {
        for (int x = 0; x < width; x += blockSize) {
            int distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));
            if (distance < radius) {
                // Apply pixelation effect within the radius
                int sumR = 0, sumG = 0, sumB = 0, sumA = 0, count = 0;
                for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                    for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                        Pixel* ptrPixel = (Pixel*)&imageRGBA[yy * width * 4 + xx * 4];
                        sumR += ptrPixel->r;
                        sumG += ptrPixel->g;
                        sumB += ptrPixel->b;
                        sumA += ptrPixel->a;
                        count++;
                    }
                }
                // Calculate the average color
                unsigned char avgR = sumR / count;
                unsigned char avgG = sumG / count;
                unsigned char avgB = sumB / count;
                unsigned char avgA = sumA / count;
                
                // Apply the average color to each pixel in the block
                for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                    for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                        Pixel* ptrPixel = (Pixel*)&imageRGBA[yy * width * 4 + xx * 4];
                        ptrPixel->r = avgR;
                        ptrPixel->g = avgG;
                        ptrPixel->b = avgB;
                        ptrPixel->a = avgA;
                    }
                }
            }
        }
    }
}

__global__ void ImageTransformCuda(unsigned char* imageRGBA, int width, int height, int centerX, int centerY) {
    int radius = 120; // Radius for the effect
    int blockSize = 15; // Size of each pixelation block

    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int stride = blockDim.x * gridDim.x;

    for (int i = idx; i < width * height; i += stride + blockSize) {
        int x = (i % width) - ((i % width) % blockSize);
        int y = (i / width) - ((i / width) % blockSize);

        int distance = sqrtf(powf(x - centerX, 2) + powf(y - centerY, 2));
        if (distance < radius) {
            int sumR = 0, sumG = 0, sumB = 0, sumA = 0, count = 0;

            for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                    Pixel* ptrPixel = (Pixel*)&imageRGBA[yy * width * 4 + xx * 4];
                    sumR += ptrPixel->r;
                    sumG += ptrPixel->g;
                    sumB += ptrPixel->b;
                    sumA += ptrPixel->a;
                    count++;
                }
            }

            unsigned char avgR = sumR / count;
            unsigned char avgG = sumG / count;
            unsigned char avgB = sumB / count;
            unsigned char avgA = sumA / count;

            for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                    Pixel* ptrPixel = (Pixel*)&imageRGBA[yy * width * 4 + xx * 4];
                    ptrPixel->r = avgR;
                    ptrPixel->g = avgG;
                    ptrPixel->b = avgB;
                    ptrPixel->a = avgA;
                }
            }
        }
    }
}

int main(int argc, char** argv)
{
    // Check argument count
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return -1;
    }

    printf("Found arguments\n");

    int centerX = 300;
    int centerY = 250;

    // Load image using stb_image library
    int width, height, channels;
    unsigned char* imageRGBA = stbi_load(argv[1], &width, &height, &channels, 4);
    if (!imageRGBA) {
        printf("Failed to load image\n");
        return -1;
    }

    printf("Loaded image with width: %d, height: %d, channels: %d\n", width, height, channels);
    
    // Allocate memory for CPU and GPU images
    unsigned char* imageRGBA_cpu = (unsigned char*)malloc(width * height * 4);
    unsigned char* imageRGBA_gpu = (unsigned char*)malloc(width * height * 4);
    memcpy(imageRGBA_cpu, imageRGBA, width * height * 4);
    memcpy(imageRGBA_gpu, imageRGBA, width * height * 4);

    // CPU transformation
    clock_t start_cpu = clock();
    ImageTransformCpu(imageRGBA_cpu, width, height, centerX, centerY);
    clock_t end_cpu = clock();
    double cpu_time = ((double)(end_cpu - start_cpu)) / CLOCKS_PER_SEC;
    printf("CPU processing time: %f seconds\n", cpu_time);

    // GPU transformation
    
    unsigned char* d_imageRGBA;
    cudaMalloc((void**)&d_imageRGBA, width * height * sizeof(Pixel));
    cudaMemcpy(d_imageRGBA, imageRGBA_gpu, width * height * sizeof(Pixel), cudaMemcpyHostToDevice);

    int blockSize = 256;
    int numBlocks = (width * height + blockSize - 1) / blockSize;

    clock_t start_gpu = clock();
    ImageTransformCuda<<<numBlocks, blockSize>>>(d_imageRGBA, width, height, centerX, centerY);
    clock_t end_gpu = clock();
    double gpu_time = ((double)(end_gpu - start_gpu)) / CLOCKS_PER_SEC;
    printf("GPU processing time: %f seconds\n", gpu_time);

    cudaDeviceSynchronize();
    cudaMemcpy(imageRGBA_gpu, d_imageRGBA, width * height * sizeof(Pixel), cudaMemcpyDeviceToHost);

    // Save the CPU processed image
    stbi_write_png("output_cpu.png", width, height, 4, imageRGBA_cpu, width * 4);

    // Save the GPU processed image
    stbi_write_png("output_gpu.png", width, height, 4, imageRGBA_gpu, width * 4);

    // Free the allocated memory
    free(imageRGBA_cpu);
    free(imageRGBA_gpu);
    cudaFree(d_imageRGBA);
    stbi_image_free(imageRGBA);

    printf("Images saved as output_cpu.png and output_gpu.png\n");

    return 0;
}
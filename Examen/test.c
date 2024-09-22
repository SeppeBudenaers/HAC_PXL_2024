#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image.h"
#include "stb_image_write.h"
#include <math.h>
#include <time.h>
 
struct Pixel
{
 unsigned char r, g, b, a;
};
 
void ImageTransformCpu(unsigned char* imageRGBA, int width, int height,int centerX, int centerY)
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
 
__global__ void ImageTransformGpu(unsigned char* imageRGBA, int width, int height, int centerX, int centerY)
{
  // TODO CUDA KERNEL schrijven
}
  
int main(int argc, char** argv)
{
    // Check argument count
    if (argc < 2)
    {
        printf("Usage: applicationname <filename>\r\n");
        return -1;
    }
 
    // Open image
    int width, height, componentCount;
    int centerX = 300;
    int centerY = 250; 
 
    printf("Loading png file...\r\n");
    unsigned char* imageData = stbi_load(argv[1], &width, &height, &componentCount, 4);
    if (!imageData)
    {
        printf("Failed to open Image\r\n");
        return -1;
    }
    printf(" DONE \r\n" );
 
    // Validate image sizes
    if (width % 32 || height % 32)
    {
        // NOTE: Leaked memory of "imageData"
        printf("Width and/or Height is not dividable by 32!\r\n");
        return -1;
    }
  
    // Process image on cpu
    printf("Processing image...\r\n");
    ImageTransformCpu(imageData, width, height,centerX,centerY);
    printf(" DONE \r\n");
    const char * fileNameOut = "cpu.png";
    // Write image back to disk
    printf("Writing png to disk...\r\n");
    stbi_write_png(fileNameOut, width, height, 4, imageData, 4 * width);
    printf("DONE\r\n");
    
    // Copy data to the gpu
    // TODO: code aanvullen!
 
    // Free memory
    stbi_image_free(imageData);
}
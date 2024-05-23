#define STBI_X64_TARGET
#define STBI_NO_THREAD_LOCALS
#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Convolutie.h"

clock_t start, stop;
double cpu_time;
int main(int argc, char* argv[]) {
	printf("tiktok\n");
	// Load the image
    int width, height, channels;
    unsigned char* inputImage = (unsigned char*)stbi_load(argv[1], &width, &height, &channels, 0);
    if (inputImage == NULL) {
        printf("Error loading image\n");
        return 1;
    }
    printf("Image loaded: %dx%d, %d channels\n", width, height, channels);
    // Prepare the output image buffer
    int newWidth = width - 2;
    int newHeight = height - 2;
    unsigned char* outputImg = (unsigned char*)malloc(newWidth * newHeight * channels);

    // Start the clock
    clock_t start = clock();
    printf("Start\n");
    // Apply convolution
    applyConvolution(inputImage, outputImg, width, height, channels);
    printf("End\n");
    // Stop the clock
    clock_t stop = clock();
    double cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;

    // Print processing time
    printf("Time taken: %f\n", cpu_time);
    printf("saving image\n");
    // Save the output image
    if (!stbi_write_png("output.png", newWidth, newHeight, channels, outputImg, newWidth * channels)) {
        printf("Error saving image\n");
        return 1;
    }
    printf("Image saved\n");
    // Free memory
    stbi_image_free(inputImage);
    free(outputImg);
    printf("Memory freed\n");
    printf("Done\n");
    return 0;
}

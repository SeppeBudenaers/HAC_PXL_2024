#define STBI_NO_THREAD_LOCALS
#define STBI_NO_SIMD
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Max_Min_Pooling.h"

// Helper function to print image
void print_image(unsigned char* image, int width, int height, int channels) {
    for (int h = 0; h < height; ++h) {
        for (int w = 0; w < width; ++w) {
            for (int c = 0; c < channels; ++c) {
                printf("%3d ", image[h * width * channels + w * channels + c]);
            }
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    // Example image (4x4, 1 channel for simplicity)
    unsigned char image[16] = {
        1, 2, 3, 4,
        5, 6, 7, 8,
        9, 10, 11, 12,
        13, 14, 15, 16
    };
    int width = 4;
    int height = 4;
    int channels = 1;

    // Output arrays for pooling results
    unsigned char min_output[4];
    unsigned char avg_output[4];
    unsigned char max_output[4];

    // Perform pooling
    Min_Pooling(image, min_output, width, height, channels);
    Average_Pooling(image, avg_output, width, height, channels);
    Max_Pooling(image, max_output, width, height, channels);

    // Print results
    printf("Original Image:\n");
    print_image(image, width, height, channels);

    printf("Min Pooling Result:\n");
    print_image(min_output, 2, 2, channels); // Assuming 2x2 pooling

    printf("Average Pooling Result:\n");
    print_image(avg_output, 2, 2, channels); // Assuming 2x2 pooling

    printf("Max Pooling Result:\n");
    print_image(max_output, 2, 2, channels); // Assuming 2x2 pooling

    return 0;
}

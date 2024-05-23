#define STBI_NO_SIMD
#define STBI__X64_TARGET
#define STBI_NO_THREAD_LOCALS
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include "Convolutie.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Usage: %s <image_path>\n", argv[0]);
        return 1;
    }

    int width, height, channels;
    unsigned char* img = stbi_load(argv[1], &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image\n");
        return -1;
    }

    // Convolution
    unsigned char* convOutput = (unsigned char*)malloc(width * height * channels);
    applyConvolution(img, convOutput, width, height, channels);
    stbi_write_png("conv_output.png", width, height, channels, convOutput, width * channels);
    printf("Finished Convolution \n\r");


    // Cleanup
    stbi_image_free(img);
    free(convOutput);

    return 0;
}

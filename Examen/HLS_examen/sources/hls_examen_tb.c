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
#include "hls_examen.h"

int main(int argc, char* argv[]) {

    char test[] = "../puppy640.png";
    int width, height, channels;
    unsigned char* img = stbi_load(test, &width, &height, &channels, 0);
    if (img == NULL) {
        printf("Error in loading the image:debug\n");
        return -1;
    }

    // Convolution
    unsigned char* convOutput = (unsigned char*)malloc(width * height * channels);
    ImageTransform(img, convOutput,300,250);
    stbi_write_png("transform.png", width, height, channels, convOutput, width * channels);
    printf("Finished transform \n\r");


    // Cleanup
    stbi_image_free(img);
    free(convOutput);

    return 0;
}

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

    int8_t Input[36] ={3,0,1,2,7,4,1,5,8,9,3,1,2,7,2,5,1,3,0,1,3,1,7,8,4,2,1,6,2,8,2,4,5,2,3,9};
    int8_t output[4][4] ={
        {-5,-4,0,8},
        {-10,-2,2,3},
        {0,-2,-4,-7},
        {-3,-2,-3,-16}
    };
    int channels = 1;
    int width = 6;
    int height = 6;

    char* outputImg = (char*)malloc(16);

    start =clock();

        applyConvolution(Input, outputImg, width, height, channels);

    stop =clock();
    cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("output\n");
    for(int i = 0; i < 4*4*1; i++){
            printf("%d\n", outputImg[i]);
    }
    printf("Time taken: %f\n", cpu_time);

    free(outputImg);
    return 0;
}

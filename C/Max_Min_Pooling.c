#define STB_IMAGE_IMPLEMENTATION
#include "../Include/stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../Include/stb_image_write.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

clock_t start, stop;
double cpu_time;

void Max_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels) {
    for(int i = 1; i < height; i+=2)
    {
        for(int j = 1; j < width; j+=2)
        {
            for (int c = 0; c < channels; c++)
            {
                unsigned char max_val = 0;
                max_val = image[(i-1) * width * channels + (j-1) * channels + c];

                if (image[(i-1) * width * channels + j * channels + c] > max_val)
                {
                    max_val = image[(i-1) * width * channels + j * channels + c];
                }
                if (image[i * width * channels + (j-1) * channels + c] > max_val)
                {
                    max_val = image[i * width * channels + (j-1) * channels + c];
                }
                if (image[i * width * channels + j * channels + c] > max_val)
                {
                    max_val = image[i * width * channels + j * channels + c];
                }

                output[(i/2) * (width/2) * channels + (j/2) * channels + c] = max_val;
            }
        }      
    }
}

void Min_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels) {
    for(int i = 1; i < height; i+=2)
    {
        for(int j = 1; j < width; j+=2)
        {
            for (int c = 0; c < channels; c++)
            {
                unsigned char min_val = 0;
                min_val = image[(i-1) * width * channels + (j-1) * channels + c];

                if (image[(i-1) * width * channels + j * channels + c] < min_val)
                {
                    min_val = image[(i-1) * width * channels + j * channels + c];
                }
                if (image[i * width * channels + (j-1) * channels + c] < min_val)
                {
                    min_val = image[i * width * channels + (j-1) * channels + c];
                }
                if (image[i * width * channels + j * channels + c] < min_val)
                {
                    min_val = image[i * width * channels + j * channels + c];
                }

                output[(i/2) * (width/2) * channels + (j/2) * channels + c] = min_val;
            }
        }      
    }
}

void Average_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels) {
    for(int i = 1; i < height; i+=2)
    {
        for(int j = 1; j < width; j+=2)
        {
            for (int c = 0; c < channels; c++)
            {
                unsigned int sum = 0;
                sum += image[(i-1) * width * channels + (j-1) * channels + c];
                sum += image[(i-1) * width * channels + j * channels + c];
                sum += image[i * width * channels + (j-1) * channels + c];
                sum += image[i * width * channels + j * channels + c];

                unsigned char average_val = sum / 4;

                output[(i/2) * (width/2) * channels + (j/2) * channels + c] = average_val;
            }
        }      
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

    unsigned char* outputImg = (unsigned char*)malloc((width/2 )* (height/2) * channels);

    start =clock();

    Min_Pooling(img, outputImg, width, height, channels); 

    stop =clock();
    cpu_time = ((double)(stop - start)) / CLOCKS_PER_SEC;
    printf("Time taken: %f\n", cpu_time);

    char OutputPath[100];
    snprintf(OutputPath, sizeof(OutputPath), "%s-output.png", argv[1]);
    stbi_write_png(OutputPath, (width/2), (height/2), channels, outputImg, (width/2) * channels);

    stbi_image_free(img);
    free(outputImg);

    return 0;
}
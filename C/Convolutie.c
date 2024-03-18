#include <stdio.h>

#define IMAGE_WIDTH 6
#define IMAGE_HEIGHT 6

void convolution(int image[IMAGE_HEIGHT][IMAGE_WIDTH], int kernel[3][3], int result[IMAGE_HEIGHT-2][IMAGE_WIDTH-2]) {
    for (int i = 1; i < IMAGE_HEIGHT - 1; i++) {
        for (int j = 1; j < IMAGE_WIDTH - 1; j++) {
            printf("i: %d, j: %d\n", i, j);
            int sum = 0;
            for (int k = -1; k <= 1; k++) {
                for (int l = -1; l <= 1; l++) {
                    sum += image[i + k][j + l] * kernel[k + 1][l + 1];
                }
            }
            result[i-1][j-1] = sum;
        }
    }
    
}

int main() {
    int image[IMAGE_HEIGHT][IMAGE_WIDTH] = {
        {10,10,10,0,0,0},
        {10,10,10,0,0,0},
        {10,10,10,0,0,0},
        {10,10,10,0,0,0},
        {10,10,10,0,0,0},
        {10,10,10,0,0,0}
    };
    
    int kernel[3][3] = {
        {1, 0, -1},
        {1, 0, -1},
        {1, 0, -1}
    };
    
    int result[IMAGE_HEIGHT-2][IMAGE_WIDTH-2];
    
    convolution(image, kernel, result);
    
    printf("Convolution result:\n");
    for (int i = 0; i < IMAGE_HEIGHT-2; i++) {
        for (int j = 0; j < IMAGE_WIDTH-2; j++) {
            printf("%d ", result[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}

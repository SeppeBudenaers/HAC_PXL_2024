#include <math.h>

struct Pixel
{
    unsigned char r, g, b, a;
};

void ImageTransform(unsigned char* imageRGBA, unsigned char* output, int centerX, int centerY){

#pragma HLS INTERFACE m_axi depth=65536 port=imageRGBA offset=slave bundle=input //gmem
#pragma HLS INTERFACE m_axi depth=65536 port=output offset=slave bundle=output //gmem

#pragma HLS INTERFACE s_axilite port=return bundle=control
//#pragma HLS INTERFACE s_axilite port=image bundle=control
//#pragma HLS INTERFACE s_axilite port=output bundle=control

#pragma HLS INTERFACE s_axilite port=centerX bundle=control
#pragma HLS INTERFACE s_axilite port=centerY bundle=control

	int width = 640;
	int height = 640;

    int radius = 120; // Radius for the effect
    int blockSize = 15; // Size of each pixelation block

    for (int y = 0; y < height; y += blockSize) {
        for (int x = 0; x < width; x += blockSize) {
           int distance = sqrt(pow(x - centerX, 2) + pow(y - centerY, 2));

            if (distance < radius) {
                int sumR = 0, sumG = 0, sumB = 0, sumA = 0, count = 0;

                // Calculate sum of RGBA values within the block
                for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                    for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                        int pixelIndex = (yy * width + xx) * 3; // Calculate index in RGBA array
                        sumR += imageRGBA[pixelIndex];
                        sumG += imageRGBA[pixelIndex + 1];
                        sumB += imageRGBA[pixelIndex + 2];
//                        sumA += imageRGBA[pixelIndex + 3];
                        count++;
                    }
                }

                // Calculate the average color
                unsigned char avgR = sumR / count;
                unsigned char avgG = sumG / count;
                unsigned char avgB = sumB / count;
//                unsigned char avgA = sumA / count;
//
//                // Apply the average color to each pixel in the block
                for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                    for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                        int pixelIndex = (yy * width + xx) * 3; // Calculate index in output array
                        output[pixelIndex] = avgR;
                        output[pixelIndex + 1] = avgG;
                        output[pixelIndex + 2] = avgB;
//                        output[pixelIndex + 3] = avgA;
                    }
                }
            } else {
                // Copy original pixel outside the radius
                for (int yy = y; yy < y + blockSize && yy < height; yy++) {
                    for (int xx = x; xx < x + blockSize && xx < width; xx++) {
                        int pixelIndex = (yy * width + xx) * 3; // Calculate index in both input and output arrays
                        output[pixelIndex] = imageRGBA[pixelIndex];
                        output[pixelIndex + 1] = imageRGBA[pixelIndex + 1];
                        output[pixelIndex + 2] = imageRGBA[pixelIndex + 2];
//                        output[pixelIndex + 3] = imageRGBA[pixelIndex + 3];
                    }
                }
            }
        }
    }
}

#include "Convolutie.h"
#include "stdbool.h"
#include <stdint.h>
//#include "hls_stream.h"

void applyConvolution( int image[256*256*4],  int output[254*254*4],int height,int width,int channels) {
	//DMA
	#pragma HLS INTERFACE axis port = image
	#pragma HLS INTERFACE axis port = output

	//AXI bus
	#pragma HLS INTERFACE s_axilite port=width bundle=control
	#pragma HLS INTERFACE s_axilite port=height bundle=control
	#pragma HLS INTERFACE s_axilite port=channels bundle=control

	float kernel[3][3] = {
		        {1, 0, -1},
		        {1, 0, -1},
		        {1, 0, -1}
		    };

int edge = 1; // Since kernel size is 3x3

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sum[3] = {0.0, 0.0, 0.0}; // Sum for each channel
            for (int ky = -edge; ky <= edge; ky++) {
                for (int kx = -edge; kx <= edge; kx++) {
                    int ix = x + kx;
                    int iy = y + ky;
                    if (ix >= 0 && ix < width && iy >= 0 && iy < height) {

                    for (int ch = 0; ch < channels; ch++) {
                    if (ch < 3) { // Apply convolution only to RGB channels
                                sum[ch] += kernel[ky + edge][kx + edge] * image[(iy * width + ix) * channels + ch];
                            }
                        }
                    }
                }
            }
            for (int ch = 0; ch < channels; ch++) {
                if (ch < 3) {
                    int val = (int)sum[ch];
                    output[(y * width + x) * channels + ch] = (unsigned char)(val > 255 ? 255 : (val < 0 ? 0 : val));
                } else {
                    // Preserve the alpha channel if present
                    output[(y * width + x) * channels + ch] = image[(y * width + x) * channels + ch];
                }
            }
        }
    }
}

#include "Convolutie.h"
#include "stdbool.h"
#include <stdint.h>

void applyConvolution( char* image,  char* output) {
	#pragma HLS INTERFACE s_axilite port=return bundle=control
	#pragma HLS INTERFACE s_axilite port=image bundle=control
	#pragma HLS INTERFACE s_axilite port=output bundle=control
	#pragma HLS INTERFACE s_axilite port=width bundle=control
	#pragma HLS INTERFACE s_axilite port=height bundle=control
	#pragma HLS INTERFACE s_axilite port=channels bundle=control

	#pragma HLS INTERFACE m_axi depth=65536 port=image offset=slave bundle=input //gmem
	#pragma HLS INTERFACE m_axi depth=65536 port=output offset=slave bundle=output //gmem

	/*
	#pragma HLS INTERFACE ap_ctrl_none port = return
	#pragma HLS INTERFACE ap_none port = image
	#pragma HLS INTERFACE ap_none port = output
	#pragma HLS INTERFACE ap_none port = width
	#pragma HLS INTERFACE ap_none port = height
	#pragma HLS INTERFACE ap_none port = channels
	#pragma HLS INTERFACE ap_none port = kernel
	 */

	float kernel[3][3] = {
	        {1, 0, -1},
	        {1, 0, -1},
	        {1, 0, -1}
	    };
	    int width = 6;
	    int height = 6;
	    int edge = 1; // Since kernel size is 3x3

	    for (int y = edge; y < height - edge; y++) {
	        for (int x = edge; x < width - edge; x++) {
	            float sum = 0.0; // Single sum for single channel
	            for (int ky = -edge; ky <= edge; ky++) {
	                for (int kx = -edge; kx <= edge; kx++) {
	                    int ix = x + kx;
	                    int iy = y + ky;
	                    sum += kernel[ky + edge][kx + edge] * image[iy * width + ix];
	                }
	            }
	            // Convert sum to int8_t and store in the output array
	            int val = (int)sum;
	            output[(y - edge) * (width - 2 * edge) + (x - edge)] = (int8_t)(val > 127 ? 127 : (val < -128 ? -128 : val));
	        }
	    }
	}

#ifndef MAX_MIN_POOLING_H
#define MAX_MIN_POOLING_H


void Max_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels);
void Min_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels);
void Average_Pooling(unsigned char* image, unsigned char* output, int width, int height, int channels);
#endif
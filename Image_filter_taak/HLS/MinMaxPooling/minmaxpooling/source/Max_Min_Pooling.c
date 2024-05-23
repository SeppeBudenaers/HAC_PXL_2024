




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


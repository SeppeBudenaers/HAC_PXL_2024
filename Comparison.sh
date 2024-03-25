#!/bin/bash

# Get the image location from the first argument
imageLocation=$1

# Compile and run the GPU code and measure the time taken
nvcc ./GPU/Convolutie.cu -o ./main.exe && {
    clear
    HACtime=$(./main.exe "$imageLocation" | grep "Time taken:")
}

# Compile and run the CPU code and measure the time taken
gcc ./C/Convolutie.c -o ./main.exe && {
    clear
    CPUtime=$(./main.exe "$imageLocation" | grep "Time taken:")
}

clear
echo "hac $HACtime"
echo "cpu $CPUtime"

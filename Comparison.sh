#!/bin/bash

# Get the image location from the first argument
imageLocation=$1

# Check if the second argument is "gpu"
if [ "$2" == "gpu" ]; then
    # Compile and run the GPU code and measure the time taken
    nvcc ./GPU/Convolutie.cu -o ./main.exe && {
        clear
        HACtime=$(./main.exe "$imageLocation" | grep "Time taken:")
    }
elif [ "$2" == "cpu" ]; then
    # Compile and run the CPU code and measure the time taken
    gcc ./C/Convolutie.c -o ./main.exe && {
        clear
        CPUtime=$(./main.exe "$imageLocation" | grep "Time taken:")
    }
else
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
fi

clear
if [ "$2" == "cpu" ]; then
    echo "cpu $CPUtime"
elif [ "$2" == "gpu" ]; then
    echo "gpu $HACtime"
else
    echo "gpu $HACtime"
    echo "cpu $CPUtime"
fi

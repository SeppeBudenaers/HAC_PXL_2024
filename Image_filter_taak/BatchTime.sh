#!/bin/bash

# Get the image location from the first argument
imageLocation="./Images/"

# Compile the GPU code
nvcc ./GPU/Convolutie.cu -o ./gpu.exe

# Compile the CPU code
gcc ./C/Convolutie.c -o ./cpu.exe



# Create the CSV file and write the header
echo "Image Name; CPU Time; GPU Time" > comparison.csv

# Loop through all the images in the directory
for file in "$imageLocation"*; do
    # Check if the image name does not end with "-output.png"
    if [[ ! "$file" == *"-output.png" ]]; then
        # Run the GPU code and measure the time taken
        GPUtime=$(./gpu.exe "$imageLocation$file" "noOut" | grep "Time taken:")

        # Run the CPU code and measure the time taken
        CPUtime=$(./cpu.exe "$imageLocation$file" "noOut" | grep "Time taken:")

        # Remove dot and replace with comma in GPUtime
        GPUtime=${GPUtime//./,}

        # Remove dot and replace with comma in CPUtime
        CPUtime=${CPUtime//./,}

        # Write the image name and times to the CSV file
        echo "$(basename "$file"); ${CPUtime:12:5}; ${GPUtime:12:5}" >> comparison.csv
    fi
done

echo "Done! Check comparison.csv for the results"


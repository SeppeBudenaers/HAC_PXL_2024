@echo off
cls

REM Get the image location from the first argument
set imageLocation=./Images/

REM Compile the GPU code
nvcc .\GPU\Convolutie.cu -o ./gpu.exe

REM Compile the CPU code
gcc .\C\Convolutie.c -o ./cpu.exe

REM Enable delayed expansion
setlocal EnableDelayedExpansion

REM Create the CSV file and write the header
echo Image Name; CPU Time; GPU Time > comparison.csv

REM Loop through all the images in the directory
for %%F in (%imageLocation%*) do (
    REM Check if the image name does not end with "-output.png"
    echo %%~nxF | findstr /I /C:"-output.png" > nul
    if errorlevel 1 (
        REM Run the GPU code and measure the time taken
        for /f "tokens=*" %%i in ('.\gpu.exe !imageLocation!%%F "noOut" ^| findstr "Time taken:"') do set GPUtime=%%i
        REM Remove dot and replace with comma in GPUtime
        set GPUtime=!GPUtime:.=,!
        REM echo !imageLocation!%%F !GPUtime!
        REM Run the CPU code and measure the time taken
        for /f "tokens=*" %%i in ('.\cpu.exe !imageLocation!%%F "noOut" ^| findstr "Time taken:"') do set CPUtime=%%i
        REM Remove dot and replace with comma in CPUtime
        set CPUtime=!CPUtime:.=,!
        REM echo !imageLocation!%%F !CPUtime!
        REM Write the image name and times to the CSV file
        
        echo %%~nxF; !CPUtime:~12,5!; !GPUtime:~12,5! >> comparison.csv
    )
)
echo Done! check comparison.csv for the results
REM End delayed expansion
endlocal

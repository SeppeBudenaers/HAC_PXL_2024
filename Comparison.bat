@echo off
cls


REM Get the image location from the first argument
set imageLocation=%1

REM Compile and run the CPU and GPU code and measure the time taken
nvcc .\GPU\Convolutie.cu -o ./main.exe && (
    cls
    for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set HACtime=%%i
)

gcc .\C\Convolutie.c -o ./main.exe && (
    cls
    for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set CPUtime=%%i
)

cls
echo hac %HACtime%
echo cpu %CPUtime%

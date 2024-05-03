@echo off
cls

REM Get the image location from the first argument
set imageLocation=%1

REM Check if the second argument is "gpu"
if "%2"=="gpu" (
    REM Compile and run the GPU code and measure the time taken
    nvcc .\GPU\Convolutie.cu -o ./main.exe && (
        cls
        for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set HACtime=%%i
    )
) else if "%2"=="cpu" (
    REM Compile and run the CPU code and measure the time taken
    gcc .\C\Convolutie.c -o ./main.exe && (
        cls
        for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set HACtime=%%i
    )
) else (
    REM Compile and run the GPU code and measure the time taken
    nvcc .\GPU\Convolutie.cu -o ./main.exe && (
        cls
        for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set HACtime=%%i
    )
    REM Compile and run the CPU code and measure the time taken
    gcc .\C\Convolutie.c -o ./main.exe && (
        cls
        for /f "tokens=*" %%i in ('.\main.exe %imageLocation% ^| findstr "Time taken:"') do set CPUtime=%%i
    )
)

cls
if "%2"=="cpu" (
    echo cpu %CPUtime%
) else if "%2"=="gpu" (
    echo gpu %HACtime%
) else (
    echo gpu %HACtime%
    echo cpu %CPUtime%
)

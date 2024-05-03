set imageLocation=%1
nvcc .\GPU\test.cu -o .\test
.\test.exe %imageLocation% out
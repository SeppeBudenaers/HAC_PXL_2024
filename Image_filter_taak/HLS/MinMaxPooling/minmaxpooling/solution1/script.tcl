############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project minmaxpooling
add_files minmaxpooling/source/Max_Min_Pooling.c
add_files minmaxpooling/source/Max_Min_Pooling.h
add_files minmaxpooling/source/stb_image.h
add_files minmaxpooling/source/stb_image_write.h
add_files -tb minmaxpooling/source/MinMax_tb.c
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 8 -name default
#source "./minmaxpooling/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

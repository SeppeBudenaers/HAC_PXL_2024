############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project HLS_examen
set_top ImageTransform
add_files HLS_examen/sources/hls_examen.c
add_files HLS_examen/sources/hls_examen.h
add_files HLS_examen/sources/stb_image.h
add_files HLS_examen/sources/stb_image_write.h
add_files -tb HLS_examen/sources/hls_examen_tb.c
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 8 -name default
#source "./HLS_examen/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

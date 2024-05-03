############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project Labo1_Oef3
set_top CombLogic
add_files Labo1_Oef3/source/hls_custom_ex3.c
add_files Labo1_Oef3/source/hls_custom_ex3.h
add_files -tb Labo1_Oef3/source/hls_custom_ex3_tb.c
open_solution "solution1" -flow_target vivado
set_part {xc7z010iclg225-1L}
create_clock -period 10 -name default
#source "./Labo1_Oef3/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

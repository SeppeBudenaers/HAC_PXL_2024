############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project Labo1_Oef2
set_top comb_oef2
add_files Labo1_Oef2/source/hls_Custom_Gate.c
add_files Labo1_Oef2/source/hls_Custom_Gate.h
add_files -tb Labo1_Oef2/source/hls_Custom_Gate_tb.c
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 8 -name default
#source "./Labo1_Oef2/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

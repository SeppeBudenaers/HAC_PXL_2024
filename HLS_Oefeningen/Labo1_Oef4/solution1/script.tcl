############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project Labo1_Oef4
set_top Oef4
add_files Labo1_Oef4/source/Dobblesteen.c
add_files Labo1_Oef4/source/Dobblesteen.h
add_files -tb Labo1_Oef4/source/Dobblesteen_TB.c
open_solution "solution1" -flow_target vivado
set_part {xc7z020clg400-1}
create_clock -period 8 -name default
#source "./Labo1_Oef4/solution1/directives.tcl"
csim_design
csynth_design
cosim_design
export_design -format ip_catalog

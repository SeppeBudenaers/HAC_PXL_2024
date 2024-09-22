############################################################
## This file is generated automatically by Vitis HLS.
## Please DO NOT edit it.
## Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
## Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
############################################################
open_project Convolutie
set_top Convolutie
add_files Convolutie/source/Convolutie.c
add_files Convolutie/source/Convolutie.h
add_files Convolutie/source/stb_image.h
add_files Convolutie/source/stb_image_write.h
add_files -tb Convolutie/source/Convolutie.h -cflags "-Wno-unknown-pragmas"
add_files -tb Convolutie/source/Convolutie_TB.c -cflags "-Wno-unknown-pragmas"
add_files -tb Convolutie/source/input.png -cflags "-Wno-unknown-pragmas"
add_files -tb Convolutie/source/stb_image.h -cflags "-Wno-unknown-pragmas"
add_files -tb Convolutie/source/stb_image_write.h -cflags "-Wno-unknown-pragmas"
open_solution "solution1" -flow_target vivado
set_part {xc7z020-clg400-1}
create_clock -period 8 -name default
#source "./Convolutie/solution1/directives.tcl"
csim_design -argv {input.png}
csynth_design
cosim_design
export_design -format ip_catalog

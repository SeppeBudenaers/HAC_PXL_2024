vlib modelsim_lib/work
vlib modelsim_lib/msim

vlib modelsim_lib/msim/xilinx_vip
vlib modelsim_lib/msim/xpm
vlib modelsim_lib/msim/xbip_utils_v3_0_11
vlib modelsim_lib/msim/axi_utils_v2_0_7
vlib modelsim_lib/msim/xbip_pipe_v3_0_7
vlib modelsim_lib/msim/xbip_dsp48_wrapper_v3_0_5
vlib modelsim_lib/msim/xbip_dsp48_addsub_v3_0_7
vlib modelsim_lib/msim/xbip_dsp48_multadd_v3_0_7
vlib modelsim_lib/msim/xbip_bram18k_v3_0_7
vlib modelsim_lib/msim/mult_gen_v12_0_19
vlib modelsim_lib/msim/floating_point_v7_1_16
vlib modelsim_lib/msim/xil_defaultlib
vlib modelsim_lib/msim/axi_infrastructure_v1_1_0
vlib modelsim_lib/msim/axi_vip_v1_1_15
vlib modelsim_lib/msim/processing_system7_vip_v1_0_17
vlib modelsim_lib/msim/generic_baseblocks_v2_1_1
vlib modelsim_lib/msim/axi_register_slice_v2_1_29
vlib modelsim_lib/msim/fifo_generator_v13_2_9
vlib modelsim_lib/msim/axi_data_fifo_v2_1_28
vlib modelsim_lib/msim/axi_crossbar_v2_1_30
vlib modelsim_lib/msim/lib_cdc_v1_0_2
vlib modelsim_lib/msim/proc_sys_reset_v5_0_14
vlib modelsim_lib/msim/xlconstant_v1_1_8
vlib modelsim_lib/msim/smartconnect_v1_0
vlib modelsim_lib/msim/axi_protocol_converter_v2_1_29

vmap xilinx_vip modelsim_lib/msim/xilinx_vip
vmap xpm modelsim_lib/msim/xpm
vmap xbip_utils_v3_0_11 modelsim_lib/msim/xbip_utils_v3_0_11
vmap axi_utils_v2_0_7 modelsim_lib/msim/axi_utils_v2_0_7
vmap xbip_pipe_v3_0_7 modelsim_lib/msim/xbip_pipe_v3_0_7
vmap xbip_dsp48_wrapper_v3_0_5 modelsim_lib/msim/xbip_dsp48_wrapper_v3_0_5
vmap xbip_dsp48_addsub_v3_0_7 modelsim_lib/msim/xbip_dsp48_addsub_v3_0_7
vmap xbip_dsp48_multadd_v3_0_7 modelsim_lib/msim/xbip_dsp48_multadd_v3_0_7
vmap xbip_bram18k_v3_0_7 modelsim_lib/msim/xbip_bram18k_v3_0_7
vmap mult_gen_v12_0_19 modelsim_lib/msim/mult_gen_v12_0_19
vmap floating_point_v7_1_16 modelsim_lib/msim/floating_point_v7_1_16
vmap xil_defaultlib modelsim_lib/msim/xil_defaultlib
vmap axi_infrastructure_v1_1_0 modelsim_lib/msim/axi_infrastructure_v1_1_0
vmap axi_vip_v1_1_15 modelsim_lib/msim/axi_vip_v1_1_15
vmap processing_system7_vip_v1_0_17 modelsim_lib/msim/processing_system7_vip_v1_0_17
vmap generic_baseblocks_v2_1_1 modelsim_lib/msim/generic_baseblocks_v2_1_1
vmap axi_register_slice_v2_1_29 modelsim_lib/msim/axi_register_slice_v2_1_29
vmap fifo_generator_v13_2_9 modelsim_lib/msim/fifo_generator_v13_2_9
vmap axi_data_fifo_v2_1_28 modelsim_lib/msim/axi_data_fifo_v2_1_28
vmap axi_crossbar_v2_1_30 modelsim_lib/msim/axi_crossbar_v2_1_30
vmap lib_cdc_v1_0_2 modelsim_lib/msim/lib_cdc_v1_0_2
vmap proc_sys_reset_v5_0_14 modelsim_lib/msim/proc_sys_reset_v5_0_14
vmap xlconstant_v1_1_8 modelsim_lib/msim/xlconstant_v1_1_8
vmap smartconnect_v1_0 modelsim_lib/msim/smartconnect_v1_0
vmap axi_protocol_converter_v2_1_29 modelsim_lib/msim/axi_protocol_converter_v2_1_29

vlog -work xilinx_vip  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_axi4streampc.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_axi4pc.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/xil_common_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_pkg.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi4stream_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/axi_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/clk_vip_if.sv" \
"C:/Xilinx/Vivado/2023.2/data/xilinx_vip/hdl/rst_vip_if.sv" \

vlog -work xpm  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_cdc/hdl/xpm_cdc.sv" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_fifo/hdl/xpm_fifo.sv" \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_memory/hdl/xpm_memory.sv" \

vcom -work xpm  -93  \
"C:/Xilinx/Vivado/2023.2/data/ip/xpm/xpm_VCOMP.vhd" \

vcom -work xbip_utils_v3_0_11  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/9836/hdl/xbip_utils_v3_0_vh_rfs.vhd" \

vcom -work axi_utils_v2_0_7  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/e392/hdl/axi_utils_v2_0_vh_rfs.vhd" \

vcom -work xbip_pipe_v3_0_7  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/c4f2/hdl/xbip_pipe_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_wrapper_v3_0_5  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/e5f6/hdl/xbip_dsp48_wrapper_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_addsub_v3_0_7  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/9cc0/hdl/xbip_dsp48_addsub_v3_0_vh_rfs.vhd" \

vcom -work xbip_dsp48_multadd_v3_0_7  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/0fb3/hdl/xbip_dsp48_multadd_v3_0_vh_rfs.vhd" \

vcom -work xbip_bram18k_v3_0_7  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/7a2e/hdl/xbip_bram18k_v3_0_vh_rfs.vhd" \

vcom -work mult_gen_v12_0_19  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/e1b5/hdl/mult_gen_v12_0_vh_rfs.vhd" \

vcom -work floating_point_v7_1_16  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/0994/hdl/floating_point_v7_1_rfs.vhd" \

vlog -work floating_point_v7_1_16  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/0994/hdl/floating_point_v7_1_rfs.v" \

vcom -work xil_defaultlib  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_applyConvolution_Pipeline_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_34_5.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_42_6.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_control_s_axi.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_conv_s_axi.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_fadd_32ns_32ns_32_8_full_dsp_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_flow_control_loop_pipe_sequential_init.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_fmul_32ns_32ns_32_4_max_dsp_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_input_r_m_axi.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_kernel_ROM_AUTO_1R.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_2ns_64s_64_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_31ns_32ns_63_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_31ns_64s_64_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_32ns_32ns_64_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_32s_32s_32_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mul_34s_32ns_64_3_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_mux_3_2_32_1_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_output_r_m_axi.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution_sitofp_32ns_32_7_no_dsp_1.vhd" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/vhdl/applyConvolution.vhd" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/ip/applyConvolution_fadd_32ns_32ns_32_8_full_dsp_1_ip.v" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/ip/applyConvolution_fmul_32ns_32ns_32_4_max_dsp_1_ip.v" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/dacd/hdl/ip/applyConvolution_sitofp_32ns_32_7_no_dsp_1_ip.v" \
"../../../bd/design_1/ip/design_1_applyConvolution_0_1/sim/design_1_applyConvolution_0_1.v" \

vlog -work axi_infrastructure_v1_1_0  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl/axi_infrastructure_v1_1_vl_rfs.v" \

vlog -work axi_vip_v1_1_15  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/5753/hdl/axi_vip_v1_1_vl_rfs.sv" \

vlog -work processing_system7_vip_v1_0_17  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl/processing_system7_vip_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_processing_system7_0_0/sim/design_1_processing_system7_0_0.v" \

vlog -work generic_baseblocks_v2_1_1  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/10ab/hdl/generic_baseblocks_v2_1_vl_rfs.v" \

vlog -work axi_register_slice_v2_1_29  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ff9f/hdl/axi_register_slice_v2_1_vl_rfs.v" \

vlog -work fifo_generator_v13_2_9  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ac72/simulation/fifo_generator_vlog_beh.v" \

vcom -work fifo_generator_v13_2_9  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ac72/hdl/fifo_generator_v13_2_rfs.vhd" \

vlog -work fifo_generator_v13_2_9  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ac72/hdl/fifo_generator_v13_2_rfs.v" \

vlog -work axi_data_fifo_v2_1_28  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/279e/hdl/axi_data_fifo_v2_1_vl_rfs.v" \

vlog -work axi_crossbar_v2_1_30  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/fb47/hdl/axi_crossbar_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_xbar_0/sim/design_1_xbar_0.v" \

vcom -work lib_cdc_v1_0_2  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ef1e/hdl/lib_cdc_v1_0_rfs.vhd" \

vcom -work proc_sys_reset_v5_0_14  -93  \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/408c/hdl/proc_sys_reset_v5_0_vh_rfs.vhd" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/ip/design_1_rst_ps7_0_100M_0/sim/design_1_rst_ps7_0_100M_0.vhd" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/sim/bd_48ac.v" \

vlog -work xlconstant_v1_1_8  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/d390/hdl/xlconstant_v1_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_0/sim/bd_48ac_one_0.v" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_1/sim/bd_48ac_psr_aclk_0.vhd" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/sc_util_v1_0_vl_rfs.sv" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/bd53/hdl/sc_switchboard_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_2/sim/bd_48ac_arsw_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_3/sim/bd_48ac_rsw_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_4/sim/bd_48ac_awsw_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_5/sim/bd_48ac_wsw_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_6/sim/bd_48ac_bsw_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/c6b2/hdl/sc_mmu_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_7/sim/bd_48ac_s00mmu_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/abb8/hdl/sc_transaction_regulator_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_8/sim/bd_48ac_s00tr_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/7827/hdl/sc_si_converter_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_9/sim/bd_48ac_s00sic_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/79ce/hdl/sc_axi2sc_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_10/sim/bd_48ac_s00a2s_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/sc_node_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_11/sim/bd_48ac_sarn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_12/sim/bd_48ac_srn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_13/sim/bd_48ac_s01mmu_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_14/sim/bd_48ac_s01tr_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_15/sim/bd_48ac_s01sic_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_16/sim/bd_48ac_s01a2s_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_17/sim/bd_48ac_sawn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_18/sim/bd_48ac_swn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_19/sim/bd_48ac_sbn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/ebf7/hdl/sc_sc2axi_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_20/sim/bd_48ac_m00s2a_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_21/sim/bd_48ac_m00arn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_22/sim/bd_48ac_m00rn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_23/sim/bd_48ac_m00awn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_24/sim/bd_48ac_m00wn_0.sv" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_25/sim/bd_48ac_m00bn_0.sv" \

vlog -work smartconnect_v1_0  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/6eea/hdl/sc_exit_v1_0_vl_rfs.sv" \

vlog -work xil_defaultlib  -incr -mfcu  -sv -L axi_vip_v1_1_15 -L processing_system7_vip_v1_0_17 -L smartconnect_v1_0 -L xilinx_vip "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/bd_0/ip/ip_26/sim/bd_48ac_m00e_0.sv" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_smartconnect_0_0/sim/design_1_smartconnect_0_0.v" \

vlog -work axi_protocol_converter_v2_1_29  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../../project_1.gen/sources_1/bd/design_1/ipshared/a63f/hdl/axi_protocol_converter_v2_1_vl_rfs.v" \

vlog -work xil_defaultlib  -incr -mfcu  "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/ec67/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/6b2b/hdl" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/f0b6/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ipshared/35de/hdl/verilog" "+incdir+../../../../project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/drivers/applyConvolution_v1_0/src" "+incdir+C:/Xilinx/Vivado/2023.2/data/xilinx_vip/include" \
"../../../bd/design_1/ip/design_1_auto_pc_0/sim/design_1_auto_pc_0.v" \

vcom -work xil_defaultlib  -93  \
"../../../bd/design_1/sim/design_1.vhd" \

vlog -work xil_defaultlib \
"glbl.v"


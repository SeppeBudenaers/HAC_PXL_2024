set SynModuleInfo {
  {SRCNAME applyConvolution_Pipeline_1 MODELNAME applyConvolution_Pipeline_1 RTLNAME applyConvolution_applyConvolution_Pipeline_1
    SUBMODULES {
      {MODELNAME applyConvolution_flow_control_loop_pipe_sequential_init RTLNAME applyConvolution_flow_control_loop_pipe_sequential_init BINDTYPE interface TYPE internal_upc_flow_control INSTNAME applyConvolution_flow_control_loop_pipe_sequential_init_U}
    }
  }
  {SRCNAME applyConvolution_Pipeline_VITIS_LOOP_34_5 MODELNAME applyConvolution_Pipeline_VITIS_LOOP_34_5 RTLNAME applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_34_5
    SUBMODULES {
      {MODELNAME applyConvolution_fadd_32ns_32ns_32_8_full_dsp_1 RTLNAME applyConvolution_fadd_32ns_32ns_32_8_full_dsp_1 BINDTYPE op TYPE fadd IMPL fulldsp LATENCY 7 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_fmul_32ns_32ns_32_4_max_dsp_1 RTLNAME applyConvolution_fmul_32ns_32ns_32_4_max_dsp_1 BINDTYPE op TYPE fmul IMPL maxdsp LATENCY 3 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_sitofp_32ns_32_7_no_dsp_1 RTLNAME applyConvolution_sitofp_32ns_32_7_no_dsp_1 BINDTYPE op TYPE sitofp IMPL auto LATENCY 6 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mux_3_2_32_1_1 RTLNAME applyConvolution_mux_3_2_32_1_1 BINDTYPE op TYPE mux IMPL auto LATENCY 0 ALLOW_PRAGMA 1}
    }
  }
  {SRCNAME applyConvolution_Pipeline_VITIS_LOOP_42_6 MODELNAME applyConvolution_Pipeline_VITIS_LOOP_42_6 RTLNAME applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_42_6}
  {SRCNAME applyConvolution MODELNAME applyConvolution RTLNAME applyConvolution IS_TOP 1
    SUBMODULES {
      {MODELNAME applyConvolution_mul_31ns_32ns_63_3_1 RTLNAME applyConvolution_mul_31ns_32ns_63_3_1 BINDTYPE op TYPE mul IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mul_32ns_32ns_64_3_1 RTLNAME applyConvolution_mul_32ns_32ns_64_3_1 BINDTYPE op TYPE mul IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mul_32s_32s_32_3_1 RTLNAME applyConvolution_mul_32s_32s_32_3_1 BINDTYPE op TYPE mul IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mul_34s_32ns_64_3_1 RTLNAME applyConvolution_mul_34s_32ns_64_3_1 BINDTYPE op TYPE mul IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mul_31ns_64s_64_3_1 RTLNAME applyConvolution_mul_31ns_64s_64_3_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_mul_2ns_64s_64_3_1 RTLNAME applyConvolution_mul_2ns_64s_64_3_1 BINDTYPE op TYPE mul IMPL dsp LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_kernel_ROM_AUTO_1R RTLNAME applyConvolution_kernel_ROM_AUTO_1R BINDTYPE storage TYPE rom IMPL auto LATENCY 2 ALLOW_PRAGMA 1}
      {MODELNAME applyConvolution_input_r_m_axi RTLNAME applyConvolution_input_r_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME applyConvolution_output_r_m_axi RTLNAME applyConvolution_output_r_m_axi BINDTYPE interface TYPE adapter IMPL m_axi}
      {MODELNAME applyConvolution_control_s_axi RTLNAME applyConvolution_control_s_axi BINDTYPE interface TYPE interface_s_axilite}
      {MODELNAME applyConvolution_conv_s_axi RTLNAME applyConvolution_conv_s_axi BINDTYPE interface TYPE interface_s_axilite}
    }
  }
}
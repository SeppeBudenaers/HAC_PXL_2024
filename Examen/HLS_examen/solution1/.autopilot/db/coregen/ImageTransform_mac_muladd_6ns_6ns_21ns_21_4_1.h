// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1__HH__
#define __ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1__HH__
#include "ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1.h"

template<
    int ID,
    int NUM_STAGE,
    int din0_WIDTH,
    int din1_WIDTH,
    int din2_WIDTH,
    int dout_WIDTH>
SC_MODULE(ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1) {
    sc_core::sc_in_clk clk;
    sc_core::sc_in<sc_dt::sc_logic> reset;
    sc_core::sc_in<sc_dt::sc_logic> ce;
    sc_core::sc_in< sc_dt::sc_lv<din0_WIDTH> >   din0;
    sc_core::sc_in< sc_dt::sc_lv<din1_WIDTH> >   din1;
    sc_core::sc_in< sc_dt::sc_lv<din2_WIDTH> >   din2;
    sc_core::sc_out< sc_dt::sc_lv<dout_WIDTH> >   dout;



    ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1 ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U;

    SC_CTOR(ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1):  ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U ("ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U") {
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.clk(clk);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.rst(reset);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.ce(ce);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.in0(din0);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.in1(din1);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.in2(din2);
        ImageTransform_mac_muladd_6ns_6ns_21ns_21_4_1_DSP48_1_U.dout(dout);

    }

};

#endif //

// ==============================================================
// Generated by Vitis HLS v2023.2
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// ==============================================================

`timescale 1 ns / 1 ps 

module applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_33_5 (
        ap_clk,
        ap_rst,
        ap_start,
        ap_done,
        ap_idle,
        ap_ready,
        sum_2_5,
        sum_1_5,
        sum_0_5,
        channels,
        image_r_TDATA,
        image_r_TVALID,
        image_r_TREADY,
        kernel_load,
        sum_2_6_out,
        sum_2_6_out_ap_vld,
        sum_1_6_out,
        sum_1_6_out_ap_vld,
        sum_0_6_out,
        sum_0_6_out_ap_vld
);

parameter    ap_ST_fsm_pp0_stage0 = 9'd1;
parameter    ap_ST_fsm_pp0_stage1 = 9'd2;
parameter    ap_ST_fsm_pp0_stage2 = 9'd4;
parameter    ap_ST_fsm_pp0_stage3 = 9'd8;
parameter    ap_ST_fsm_pp0_stage4 = 9'd16;
parameter    ap_ST_fsm_pp0_stage5 = 9'd32;
parameter    ap_ST_fsm_pp0_stage6 = 9'd64;
parameter    ap_ST_fsm_pp0_stage7 = 9'd128;
parameter    ap_ST_fsm_pp0_stage8 = 9'd256;

input   ap_clk;
input   ap_rst;
input   ap_start;
output   ap_done;
output   ap_idle;
output   ap_ready;
input  [31:0] sum_2_5;
input  [31:0] sum_1_5;
input  [31:0] sum_0_5;
input  [31:0] channels;
input  [7:0] image_r_TDATA;
input   image_r_TVALID;
output   image_r_TREADY;
input  [31:0] kernel_load;
output  [31:0] sum_2_6_out;
output   sum_2_6_out_ap_vld;
output  [31:0] sum_1_6_out;
output   sum_1_6_out_ap_vld;
output  [31:0] sum_0_6_out;
output   sum_0_6_out_ap_vld;

reg ap_idle;
reg image_r_TREADY;
reg sum_2_6_out_ap_vld;
reg sum_1_6_out_ap_vld;
reg sum_0_6_out_ap_vld;

(* fsm_encoding = "none" *) reg   [8:0] ap_CS_fsm;
wire    ap_CS_fsm_pp0_stage0;
reg    ap_enable_reg_pp0_iter0;
reg    ap_enable_reg_pp0_iter1;
reg    ap_enable_reg_pp0_iter2;
reg    ap_idle_pp0;
wire    ap_CS_fsm_pp0_stage8;
wire    ap_block_pp0_stage8_subdone;
reg   [0:0] icmp_ln33_reg_321;
reg    ap_condition_exit_pp0_iter0_stage8;
wire    ap_loop_exit_ready;
reg    ap_ready_int;
reg    image_r_TDATA_blk_n;
wire    ap_CS_fsm_pp0_stage1;
wire    ap_block_pp0_stage1;
reg   [0:0] icmp_ln34_reg_325;
wire    ap_block_pp0_stage0_11001;
reg   [30:0] ch_reg_315;
wire   [0:0] icmp_ln33_fu_169_p2;
reg   [0:0] icmp_ln33_reg_321_pp0_iter1_reg;
wire   [0:0] icmp_ln34_fu_175_p2;
reg   [0:0] icmp_ln34_reg_325_pp0_iter1_reg;
reg   [0:0] icmp_ln34_reg_325_pp0_iter2_reg;
reg   [7:0] image_r_read_reg_329;
reg    ap_predicate_op48_read_state2;
reg    ap_block_state2_pp0_stage1_iter0;
reg    ap_block_pp0_stage1_11001;
wire    ap_CS_fsm_pp0_stage2;
wire    ap_block_pp0_stage2_11001;
wire   [31:0] grp_fu_139_p1;
reg   [31:0] conv_reg_339;
wire    ap_block_pp0_stage8_11001;
wire   [1:0] trunc_ln35_fu_190_p1;
reg   [1:0] trunc_ln35_reg_344;
reg   [1:0] trunc_ln35_reg_344_pp0_iter1_reg;
reg   [31:0] sum_0_6_load_1_reg_351;
wire    ap_CS_fsm_pp0_stage3;
wire    ap_block_pp0_stage3_11001;
reg   [31:0] sum_1_6_load_1_reg_356;
reg   [31:0] sum_2_6_load_1_reg_361;
wire   [31:0] grp_fu_135_p2;
reg   [31:0] mul_reg_366;
wire   [31:0] tmp_2_fu_207_p5;
reg   [31:0] tmp_2_reg_371;
wire   [31:0] grp_fu_131_p2;
reg   [31:0] sum_2_4_reg_376;
reg    ap_enable_reg_pp0_iter0_reg;
wire    ap_block_pp0_stage3_subdone;
reg   [30:0] ch_1_fu_58;
wire   [30:0] add_ln33_fu_185_p2;
wire    ap_loop_init;
reg   [30:0] ap_sig_allocacmp_ch;
wire    ap_block_pp0_stage0;
reg   [31:0] sum_0_6_fu_62;
wire   [31:0] sum_2_3_fu_246_p3;
reg   [31:0] ap_sig_allocacmp_sum_0_6_load_1;
wire    ap_block_pp0_stage3;
reg   [31:0] sum_1_6_fu_66;
wire   [31:0] sum_2_2_fu_240_p3;
reg   [31:0] ap_sig_allocacmp_sum_1_6_load_1;
reg   [31:0] sum_2_6_fu_70;
wire   [31:0] sum_2_fu_234_p3;
reg   [31:0] ap_sig_allocacmp_sum_2_6_load_1;
wire    ap_block_pp0_stage3_01001;
wire    ap_CS_fsm_pp0_stage4;
wire    ap_block_pp0_stage4;
wire   [31:0] grp_fu_139_p0;
wire    ap_block_pp0_stage2;
wire   [31:0] zext_ln33_fu_165_p1;
wire    ap_block_pp0_stage8;
wire   [0:0] icmp_ln35_fu_218_p2;
wire   [0:0] icmp_ln35_1_fu_223_p2;
wire   [0:0] or_ln35_fu_228_p2;
reg    grp_fu_131_ce;
wire    ap_block_pp0_stage4_11001;
wire    ap_block_pp0_stage5_11001;
wire    ap_CS_fsm_pp0_stage5;
wire    ap_block_pp0_stage6_11001;
wire    ap_CS_fsm_pp0_stage6;
wire    ap_block_pp0_stage7_11001;
wire    ap_CS_fsm_pp0_stage7;
reg    grp_fu_135_ce;
reg    grp_fu_139_ce;
reg    ap_done_reg;
wire    ap_continue_int;
reg    ap_done_int;
reg    ap_loop_exit_ready_pp0_iter1_reg;
reg    ap_condition_exit_pp0_iter1_stage3;
reg    ap_idle_pp0_0to0;
reg   [8:0] ap_NS_fsm;
wire    ap_block_pp0_stage0_subdone;
reg    ap_idle_pp0_1to2;
reg    ap_done_pending_pp0;
reg    ap_block_pp0_stage1_subdone;
wire    ap_block_pp0_stage2_subdone;
wire    ap_block_pp0_stage4_subdone;
wire    ap_block_pp0_stage5_subdone;
wire    ap_block_pp0_stage6_subdone;
wire    ap_block_pp0_stage7_subdone;
wire    ap_enable_pp0;
wire    ap_start_int;
wire    ap_ce_reg;

// power-on initialization
initial begin
#0 ap_CS_fsm = 9'd1;
#0 ap_enable_reg_pp0_iter1 = 1'b0;
#0 ap_enable_reg_pp0_iter2 = 1'b0;
#0 ap_enable_reg_pp0_iter0_reg = 1'b0;
#0 ch_1_fu_58 = 31'd0;
#0 sum_0_6_fu_62 = 32'd0;
#0 sum_1_6_fu_66 = 32'd0;
#0 sum_2_6_fu_70 = 32'd0;
#0 ap_done_reg = 1'b0;
end

applyConvolution_fadd_32ns_32ns_32_8_full_dsp_1 #(
    .ID( 1 ),
    .NUM_STAGE( 8 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .dout_WIDTH( 32 ))
fadd_32ns_32ns_32_8_full_dsp_1_U7(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(tmp_2_reg_371),
    .din1(mul_reg_366),
    .ce(grp_fu_131_ce),
    .dout(grp_fu_131_p2)
);

applyConvolution_fmul_32ns_32ns_32_4_max_dsp_1 #(
    .ID( 1 ),
    .NUM_STAGE( 4 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .dout_WIDTH( 32 ))
fmul_32ns_32ns_32_4_max_dsp_1_U8(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(kernel_load),
    .din1(conv_reg_339),
    .ce(grp_fu_135_ce),
    .dout(grp_fu_135_p2)
);

applyConvolution_sitofp_32ns_32_7_no_dsp_1 #(
    .ID( 1 ),
    .NUM_STAGE( 7 ),
    .din0_WIDTH( 32 ),
    .dout_WIDTH( 32 ))
sitofp_32ns_32_7_no_dsp_1_U9(
    .clk(ap_clk),
    .reset(ap_rst),
    .din0(grp_fu_139_p0),
    .ce(grp_fu_139_ce),
    .dout(grp_fu_139_p1)
);

applyConvolution_mux_3_2_32_1_1 #(
    .ID( 1 ),
    .NUM_STAGE( 1 ),
    .din0_WIDTH( 32 ),
    .din1_WIDTH( 32 ),
    .din2_WIDTH( 32 ),
    .din3_WIDTH( 2 ),
    .dout_WIDTH( 32 ))
mux_3_2_32_1_1_U10(
    .din0(ap_sig_allocacmp_sum_0_6_load_1),
    .din1(ap_sig_allocacmp_sum_1_6_load_1),
    .din2(ap_sig_allocacmp_sum_2_6_load_1),
    .din3(trunc_ln35_reg_344),
    .dout(tmp_2_fu_207_p5)
);

applyConvolution_flow_control_loop_pipe_sequential_init flow_control_loop_pipe_sequential_init_U(
    .ap_clk(ap_clk),
    .ap_rst(ap_rst),
    .ap_start(ap_start),
    .ap_ready(ap_ready),
    .ap_done(ap_done),
    .ap_start_int(ap_start_int),
    .ap_loop_init(ap_loop_init),
    .ap_ready_int(ap_ready_int),
    .ap_loop_exit_ready(ap_condition_exit_pp0_iter0_stage8),
    .ap_loop_exit_done(ap_done_int),
    .ap_continue_int(ap_continue_int),
    .ap_done_int(ap_done_int)
);

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
    end else begin
        ap_CS_fsm <= ap_NS_fsm;
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_done_reg <= 1'b0;
    end else begin
        if ((ap_continue_int == 1'b1)) begin
            ap_done_reg <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage3_subdone) & (ap_loop_exit_ready_pp0_iter1_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
            ap_done_reg <= 1'b1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter0_reg <= 1'b0;
    end else begin
        if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
            ap_enable_reg_pp0_iter0_reg <= ap_start_int;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter1 <= 1'b0;
    end else begin
        if ((1'b1 == ap_condition_exit_pp0_iter0_stage8)) begin
            ap_enable_reg_pp0_iter1 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage8_subdone) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
            ap_enable_reg_pp0_iter1 <= ap_enable_reg_pp0_iter0;
        end
    end
end

always @ (posedge ap_clk) begin
    if (ap_rst == 1'b1) begin
        ap_enable_reg_pp0_iter2 <= 1'b0;
    end else begin
        if (((1'b0 == ap_block_pp0_stage3_subdone) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
            ap_enable_reg_pp0_iter2 <= 1'b0;
        end else if (((1'b0 == ap_block_pp0_stage8_subdone) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
            ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
        end
    end
end

always @ (posedge ap_clk) begin
    if (((ap_idle_pp0_0to0 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter1_stage3))) begin
        ap_loop_exit_ready_pp0_iter1_reg <= 1'b0;
    end else if (((1'b0 == ap_block_pp0_stage8_11001) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
        ap_loop_exit_ready_pp0_iter1_reg <= ap_loop_exit_ready;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ch_1_fu_58 <= 31'd0;
    end else if (((icmp_ln33_reg_321 == 1'd1) & (1'b0 == ap_block_pp0_stage8_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
        ch_1_fu_58 <= add_ln33_fu_185_p2;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        sum_0_6_fu_62 <= sum_0_5;
    end else if (((1'b0 == ap_block_pp0_stage3_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        sum_0_6_fu_62 <= sum_2_3_fu_246_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        sum_1_6_fu_66 <= sum_1_5;
    end else if (((1'b0 == ap_block_pp0_stage3_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        sum_1_6_fu_66 <= sum_2_2_fu_240_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        sum_2_6_fu_70 <= sum_2_5;
    end else if (((1'b0 == ap_block_pp0_stage3_11001) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        sum_2_6_fu_70 <= sum_2_fu_234_p3;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ch_reg_315 <= ap_sig_allocacmp_ch;
        icmp_ln33_reg_321 <= icmp_ln33_fu_169_p2;
        icmp_ln33_reg_321_pp0_iter1_reg <= icmp_ln33_reg_321;
        icmp_ln34_reg_325 <= icmp_ln34_fu_175_p2;
        icmp_ln34_reg_325_pp0_iter1_reg <= icmp_ln34_reg_325;
        icmp_ln34_reg_325_pp0_iter2_reg <= icmp_ln34_reg_325_pp0_iter1_reg;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage8_11001) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
        conv_reg_339 <= grp_fu_139_p1;
        trunc_ln35_reg_344 <= trunc_ln35_fu_190_p1;
        trunc_ln35_reg_344_pp0_iter1_reg <= trunc_ln35_reg_344;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        image_r_read_reg_329 <= image_r_TDATA;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
        mul_reg_366 <= grp_fu_135_p2;
        sum_0_6_load_1_reg_351 <= ap_sig_allocacmp_sum_0_6_load_1;
        sum_1_6_load_1_reg_356 <= ap_sig_allocacmp_sum_1_6_load_1;
        sum_2_6_load_1_reg_361 <= ap_sig_allocacmp_sum_2_6_load_1;
        tmp_2_reg_371 <= tmp_2_fu_207_p5;
    end
end

always @ (posedge ap_clk) begin
    if (((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2))) begin
        sum_2_4_reg_376 <= grp_fu_131_p2;
    end
end

always @ (*) begin
    if (((icmp_ln33_reg_321 == 1'd0) & (1'b0 == ap_block_pp0_stage8_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
        ap_condition_exit_pp0_iter0_stage8 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter0_stage8 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_subdone) & (ap_enable_reg_pp0_iter1 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln33_reg_321_pp0_iter1_reg == 1'd0))) begin
        ap_condition_exit_pp0_iter1_stage3 = 1'b1;
    end else begin
        ap_condition_exit_pp0_iter1_stage3 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_subdone) & (ap_loop_exit_ready_pp0_iter1_reg == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3))) begin
        ap_done_int = 1'b1;
    end else begin
        ap_done_int = ap_done_reg;
    end
end

always @ (*) begin
    if (~((ap_loop_exit_ready == 1'b0) & (ap_loop_exit_ready_pp0_iter1_reg == 1'b0))) begin
        ap_done_pending_pp0 = 1'b1;
    end else begin
        ap_done_pending_pp0 = 1'b0;
    end
end

always @ (*) begin
    if ((1'b1 == ap_CS_fsm_pp0_stage0)) begin
        ap_enable_reg_pp0_iter0 = ap_start_int;
    end else begin
        ap_enable_reg_pp0_iter0 = ap_enable_reg_pp0_iter0_reg;
    end
end

always @ (*) begin
    if (((ap_start_int == 1'b0) & (ap_idle_pp0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage0))) begin
        ap_idle = 1'b1;
    end else begin
        ap_idle = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0) & (ap_enable_reg_pp0_iter0 == 1'b0))) begin
        ap_idle_pp0 = 1'b1;
    end else begin
        ap_idle_pp0 = 1'b0;
    end
end

always @ (*) begin
    if ((ap_enable_reg_pp0_iter0 == 1'b0)) begin
        ap_idle_pp0_0to0 = 1'b1;
    end else begin
        ap_idle_pp0_0to0 = 1'b0;
    end
end

always @ (*) begin
    if (((ap_enable_reg_pp0_iter2 == 1'b0) & (ap_enable_reg_pp0_iter1 == 1'b0))) begin
        ap_idle_pp0_1to2 = 1'b1;
    end else begin
        ap_idle_pp0_1to2 = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage8_subdone) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage8))) begin
        ap_ready_int = 1'b1;
    end else begin
        ap_ready_int = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage0) & (1'b1 == ap_CS_fsm_pp0_stage0) & (ap_loop_init == 1'b1))) begin
        ap_sig_allocacmp_ch = 31'd0;
    end else begin
        ap_sig_allocacmp_ch = ch_1_fu_58;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        ap_sig_allocacmp_sum_0_6_load_1 = sum_2_3_fu_246_p3;
    end else begin
        ap_sig_allocacmp_sum_0_6_load_1 = sum_0_6_fu_62;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        ap_sig_allocacmp_sum_1_6_load_1 = sum_2_2_fu_240_p3;
    end else begin
        ap_sig_allocacmp_sum_1_6_load_1 = sum_1_6_fu_66;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3) & (ap_enable_reg_pp0_iter2 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln34_reg_325_pp0_iter2_reg == 1'd1))) begin
        ap_sig_allocacmp_sum_2_6_load_1 = sum_2_fu_234_p3;
    end else begin
        ap_sig_allocacmp_sum_2_6_load_1 = sum_2_6_fu_70;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7)) | ((1'b0 == ap_block_pp0_stage6_11001) & (1'b1 == ap_CS_fsm_pp0_stage6)) | ((1'b0 == ap_block_pp0_stage5_11001) & (1'b1 == ap_CS_fsm_pp0_stage5)) | ((1'b0 == ap_block_pp0_stage4_11001) & (1'b1 == ap_CS_fsm_pp0_stage4)) | ((1'b0 == ap_block_pp0_stage8_11001) & (1'b1 == ap_CS_fsm_pp0_stage8)) | ((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        grp_fu_131_ce = 1'b1;
    end else begin
        grp_fu_131_ce = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage0_11001) & (1'b1 == ap_CS_fsm_pp0_stage0)) | ((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3)) | ((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2)) | ((1'b0 == ap_block_pp0_stage1_11001) & (1'b1 == ap_CS_fsm_pp0_stage1)))) begin
        grp_fu_135_ce = 1'b1;
    end else begin
        grp_fu_135_ce = 1'b0;
    end
end

always @ (*) begin
    if ((((1'b0 == ap_block_pp0_stage7_11001) & (1'b1 == ap_CS_fsm_pp0_stage7)) | ((1'b0 == ap_block_pp0_stage6_11001) & (1'b1 == ap_CS_fsm_pp0_stage6)) | ((1'b0 == ap_block_pp0_stage5_11001) & (1'b1 == ap_CS_fsm_pp0_stage5)) | ((1'b0 == ap_block_pp0_stage4_11001) & (1'b1 == ap_CS_fsm_pp0_stage4)) | ((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3)) | ((1'b0 == ap_block_pp0_stage8_11001) & (1'b1 == ap_CS_fsm_pp0_stage8)) | ((1'b0 == ap_block_pp0_stage2_11001) & (1'b1 == ap_CS_fsm_pp0_stage2)))) begin
        grp_fu_139_ce = 1'b1;
    end else begin
        grp_fu_139_ce = 1'b0;
    end
end

always @ (*) begin
    if (((icmp_ln34_reg_325 == 1'd1) & (icmp_ln33_reg_321 == 1'd1) & (1'b0 == ap_block_pp0_stage1) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1))) begin
        image_r_TDATA_blk_n = image_r_TVALID;
    end else begin
        image_r_TDATA_blk_n = 1'b1;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage1_11001) & (ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_CS_fsm_pp0_stage1) & (ap_predicate_op48_read_state2 == 1'b1))) begin
        image_r_TREADY = 1'b1;
    end else begin
        image_r_TREADY = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln33_reg_321_pp0_iter1_reg == 1'd0))) begin
        sum_0_6_out_ap_vld = 1'b1;
    end else begin
        sum_0_6_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln33_reg_321_pp0_iter1_reg == 1'd0))) begin
        sum_1_6_out_ap_vld = 1'b1;
    end else begin
        sum_1_6_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    if (((1'b0 == ap_block_pp0_stage3_11001) & (1'b1 == ap_CS_fsm_pp0_stage3) & (icmp_ln33_reg_321_pp0_iter1_reg == 1'd0))) begin
        sum_2_6_out_ap_vld = 1'b1;
    end else begin
        sum_2_6_out_ap_vld = 1'b0;
    end
end

always @ (*) begin
    case (ap_CS_fsm)
        ap_ST_fsm_pp0_stage0 : begin
            if ((~((ap_start_int == 1'b0) & (ap_done_pending_pp0 == 1'b0) & (ap_idle_pp0_1to2 == 1'b1)) & (1'b0 == ap_block_pp0_stage0_subdone))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end
        end
        ap_ST_fsm_pp0_stage1 : begin
            if ((1'b0 == ap_block_pp0_stage1_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage2;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage1;
            end
        end
        ap_ST_fsm_pp0_stage2 : begin
            if ((1'b0 == ap_block_pp0_stage2_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage3;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage2;
            end
        end
        ap_ST_fsm_pp0_stage3 : begin
            if (((ap_idle_pp0_0to0 == 1'b1) & (1'b1 == ap_condition_exit_pp0_iter1_stage3))) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else if ((1'b0 == ap_block_pp0_stage3_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage4;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage3;
            end
        end
        ap_ST_fsm_pp0_stage4 : begin
            if ((1'b0 == ap_block_pp0_stage4_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage5;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage4;
            end
        end
        ap_ST_fsm_pp0_stage5 : begin
            if ((1'b0 == ap_block_pp0_stage5_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage6;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage5;
            end
        end
        ap_ST_fsm_pp0_stage6 : begin
            if ((1'b0 == ap_block_pp0_stage6_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage7;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage6;
            end
        end
        ap_ST_fsm_pp0_stage7 : begin
            if ((1'b0 == ap_block_pp0_stage7_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage8;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage7;
            end
        end
        ap_ST_fsm_pp0_stage8 : begin
            if ((1'b0 == ap_block_pp0_stage8_subdone)) begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage0;
            end else begin
                ap_NS_fsm = ap_ST_fsm_pp0_stage8;
            end
        end
        default : begin
            ap_NS_fsm = 'bx;
        end
    endcase
end

assign add_ln33_fu_185_p2 = (ch_reg_315 + 31'd1);

assign ap_CS_fsm_pp0_stage0 = ap_CS_fsm[32'd0];

assign ap_CS_fsm_pp0_stage1 = ap_CS_fsm[32'd1];

assign ap_CS_fsm_pp0_stage2 = ap_CS_fsm[32'd2];

assign ap_CS_fsm_pp0_stage3 = ap_CS_fsm[32'd3];

assign ap_CS_fsm_pp0_stage4 = ap_CS_fsm[32'd4];

assign ap_CS_fsm_pp0_stage5 = ap_CS_fsm[32'd5];

assign ap_CS_fsm_pp0_stage6 = ap_CS_fsm[32'd6];

assign ap_CS_fsm_pp0_stage7 = ap_CS_fsm[32'd7];

assign ap_CS_fsm_pp0_stage8 = ap_CS_fsm[32'd8];

assign ap_block_pp0_stage0 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage0_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage1 = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_pp0_stage1_11001 = ((ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_block_state2_pp0_stage1_iter0));
end

always @ (*) begin
    ap_block_pp0_stage1_subdone = ((ap_enable_reg_pp0_iter0 == 1'b1) & (1'b1 == ap_block_state2_pp0_stage1_iter0));
end

assign ap_block_pp0_stage2 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage2_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_01001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage3_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage4_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage5_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage5_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage6_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage6_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage7_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage7_subdone = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage8 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage8_11001 = ~(1'b1 == 1'b1);

assign ap_block_pp0_stage8_subdone = ~(1'b1 == 1'b1);

always @ (*) begin
    ap_block_state2_pp0_stage1_iter0 = ((image_r_TVALID == 1'b0) & (ap_predicate_op48_read_state2 == 1'b1));
end

assign ap_enable_pp0 = (ap_idle_pp0 ^ 1'b1);

assign ap_loop_exit_ready = ap_condition_exit_pp0_iter0_stage8;

always @ (*) begin
    ap_predicate_op48_read_state2 = ((icmp_ln34_reg_325 == 1'd1) & (icmp_ln33_reg_321 == 1'd1));
end

assign grp_fu_139_p0 = image_r_read_reg_329;

assign icmp_ln33_fu_169_p2 = (($signed(zext_ln33_fu_165_p1) < $signed(channels)) ? 1'b1 : 1'b0);

assign icmp_ln34_fu_175_p2 = ((ap_sig_allocacmp_ch < 31'd3) ? 1'b1 : 1'b0);

assign icmp_ln35_1_fu_223_p2 = ((trunc_ln35_reg_344_pp0_iter1_reg == 2'd1) ? 1'b1 : 1'b0);

assign icmp_ln35_fu_218_p2 = ((trunc_ln35_reg_344_pp0_iter1_reg == 2'd0) ? 1'b1 : 1'b0);

assign or_ln35_fu_228_p2 = (icmp_ln35_fu_218_p2 | icmp_ln35_1_fu_223_p2);

assign sum_0_6_out = sum_0_6_fu_62;

assign sum_1_6_out = sum_1_6_fu_66;

assign sum_2_2_fu_240_p3 = ((icmp_ln35_1_fu_223_p2[0:0] == 1'b1) ? sum_2_4_reg_376 : sum_1_6_load_1_reg_356);

assign sum_2_3_fu_246_p3 = ((icmp_ln35_fu_218_p2[0:0] == 1'b1) ? sum_2_4_reg_376 : sum_0_6_load_1_reg_351);

assign sum_2_6_out = sum_2_6_fu_70;

assign sum_2_fu_234_p3 = ((or_ln35_fu_228_p2[0:0] == 1'b1) ? sum_2_6_load_1_reg_361 : sum_2_4_reg_376);

assign trunc_ln35_fu_190_p1 = ch_reg_315[1:0];

assign zext_ln33_fu_165_p1 = ap_sig_allocacmp_ch;

endmodule //applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_33_5

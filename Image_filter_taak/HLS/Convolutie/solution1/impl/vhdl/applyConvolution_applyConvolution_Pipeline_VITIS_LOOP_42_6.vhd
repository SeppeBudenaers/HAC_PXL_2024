-- ==============================================================
-- Generated by Vitis HLS v2023.2
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- ==============================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_42_6 is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    m_axi_input_r_AWVALID : OUT STD_LOGIC;
    m_axi_input_r_AWREADY : IN STD_LOGIC;
    m_axi_input_r_AWADDR : OUT STD_LOGIC_VECTOR (63 downto 0);
    m_axi_input_r_AWID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_AWLEN : OUT STD_LOGIC_VECTOR (31 downto 0);
    m_axi_input_r_AWSIZE : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_input_r_AWBURST : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_AWLOCK : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_AWCACHE : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_AWPROT : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_input_r_AWQOS : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_AWREGION : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_AWUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_WVALID : OUT STD_LOGIC;
    m_axi_input_r_WREADY : IN STD_LOGIC;
    m_axi_input_r_WDATA : OUT STD_LOGIC_VECTOR (7 downto 0);
    m_axi_input_r_WSTRB : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_WLAST : OUT STD_LOGIC;
    m_axi_input_r_WID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_WUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_ARVALID : OUT STD_LOGIC;
    m_axi_input_r_ARREADY : IN STD_LOGIC;
    m_axi_input_r_ARADDR : OUT STD_LOGIC_VECTOR (63 downto 0);
    m_axi_input_r_ARID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_ARLEN : OUT STD_LOGIC_VECTOR (31 downto 0);
    m_axi_input_r_ARSIZE : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_input_r_ARBURST : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_ARLOCK : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_ARCACHE : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_ARPROT : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_input_r_ARQOS : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_ARREGION : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_input_r_ARUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_RVALID : IN STD_LOGIC;
    m_axi_input_r_RREADY : OUT STD_LOGIC;
    m_axi_input_r_RDATA : IN STD_LOGIC_VECTOR (7 downto 0);
    m_axi_input_r_RLAST : IN STD_LOGIC;
    m_axi_input_r_RID : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_RFIFONUM : IN STD_LOGIC_VECTOR (10 downto 0);
    m_axi_input_r_RUSER : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_RRESP : IN STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_BVALID : IN STD_LOGIC;
    m_axi_input_r_BREADY : OUT STD_LOGIC;
    m_axi_input_r_BRESP : IN STD_LOGIC_VECTOR (1 downto 0);
    m_axi_input_r_BID : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_input_r_BUSER : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_AWVALID : OUT STD_LOGIC;
    m_axi_output_r_AWREADY : IN STD_LOGIC;
    m_axi_output_r_AWADDR : OUT STD_LOGIC_VECTOR (63 downto 0);
    m_axi_output_r_AWID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_AWLEN : OUT STD_LOGIC_VECTOR (31 downto 0);
    m_axi_output_r_AWSIZE : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_output_r_AWBURST : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_AWLOCK : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_AWCACHE : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_AWPROT : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_output_r_AWQOS : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_AWREGION : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_AWUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_WVALID : OUT STD_LOGIC;
    m_axi_output_r_WREADY : IN STD_LOGIC;
    m_axi_output_r_WDATA : OUT STD_LOGIC_VECTOR (7 downto 0);
    m_axi_output_r_WSTRB : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_WLAST : OUT STD_LOGIC;
    m_axi_output_r_WID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_WUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_ARVALID : OUT STD_LOGIC;
    m_axi_output_r_ARREADY : IN STD_LOGIC;
    m_axi_output_r_ARADDR : OUT STD_LOGIC_VECTOR (63 downto 0);
    m_axi_output_r_ARID : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_ARLEN : OUT STD_LOGIC_VECTOR (31 downto 0);
    m_axi_output_r_ARSIZE : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_output_r_ARBURST : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_ARLOCK : OUT STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_ARCACHE : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_ARPROT : OUT STD_LOGIC_VECTOR (2 downto 0);
    m_axi_output_r_ARQOS : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_ARREGION : OUT STD_LOGIC_VECTOR (3 downto 0);
    m_axi_output_r_ARUSER : OUT STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_RVALID : IN STD_LOGIC;
    m_axi_output_r_RREADY : OUT STD_LOGIC;
    m_axi_output_r_RDATA : IN STD_LOGIC_VECTOR (7 downto 0);
    m_axi_output_r_RLAST : IN STD_LOGIC;
    m_axi_output_r_RID : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_RFIFONUM : IN STD_LOGIC_VECTOR (10 downto 0);
    m_axi_output_r_RUSER : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_RRESP : IN STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_BVALID : IN STD_LOGIC;
    m_axi_output_r_BREADY : OUT STD_LOGIC;
    m_axi_output_r_BRESP : IN STD_LOGIC_VECTOR (1 downto 0);
    m_axi_output_r_BID : IN STD_LOGIC_VECTOR (0 downto 0);
    m_axi_output_r_BUSER : IN STD_LOGIC_VECTOR (0 downto 0);
    channels : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_0_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_1_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_2_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    output_r_offset : IN STD_LOGIC_VECTOR (63 downto 0);
    add_ln26_1 : IN STD_LOGIC_VECTOR (63 downto 0) );
end;


architecture behav of applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_42_6 is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv64_0 : STD_LOGIC_VECTOR (63 downto 0) := "0000000000000000000000000000000000000000000000000000000000000000";
    constant ap_const_lv3_0 : STD_LOGIC_VECTOR (2 downto 0) := "000";
    constant ap_const_lv2_0 : STD_LOGIC_VECTOR (1 downto 0) := "00";
    constant ap_const_lv4_0 : STD_LOGIC_VECTOR (3 downto 0) := "0000";
    constant ap_const_lv8_0 : STD_LOGIC_VECTOR (7 downto 0) := "00000000";
    constant ap_const_lv31_0 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000000";
    constant ap_const_lv31_1 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000001";
    constant ap_const_lv31_3 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000011";
    constant ap_const_lv32_1F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011111";
    constant ap_const_lv32_17 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000010111";
    constant ap_const_lv32_1E : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011110";
    constant ap_const_lv9_181 : STD_LOGIC_VECTOR (8 downto 0) := "110000001";
    constant ap_const_lv32_8 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001000";
    constant ap_const_lv8_7F : STD_LOGIC_VECTOR (7 downto 0) := "01111111";
    constant ap_const_lv24_0 : STD_LOGIC_VECTOR (23 downto 0) := "000000000000000000000000";
    constant ap_const_lv8_FF : STD_LOGIC_VECTOR (7 downto 0) := "11111111";
    constant ap_const_lv32_18 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011000";
    constant ap_const_lv32_37 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000110111";

attribute shreg_extract : string;
    signal ap_CS_fsm : STD_LOGIC_VECTOR (0 downto 0) := "1";
    attribute fsm_encoding : string;
    attribute fsm_encoding of ap_CS_fsm : signal is "none";
    signal ap_CS_fsm_pp0_stage0 : STD_LOGIC;
    attribute fsm_encoding of ap_CS_fsm_pp0_stage0 : signal is "none";
    signal ap_enable_reg_pp0_iter0 : STD_LOGIC;
    signal ap_enable_reg_pp0_iter1 : STD_LOGIC := '0';
    signal ap_enable_reg_pp0_iter2 : STD_LOGIC := '0';
    signal ap_enable_reg_pp0_iter3 : STD_LOGIC := '0';
    signal ap_enable_reg_pp0_iter4 : STD_LOGIC := '0';
    signal ap_idle_pp0 : STD_LOGIC;
    signal icmp_ln42_reg_413 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln42_reg_413_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln43_reg_427 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln43_reg_427_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_predicate_op45_read_state2 : BOOLEAN;
    signal ap_block_state2_pp0_stage0_iter2 : BOOLEAN;
    signal ap_block_pp0_stage0_subdone : BOOLEAN;
    signal icmp_ln42_fu_177_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_condition_exit_pp0_iter0_stage0 : STD_LOGIC;
    signal ap_loop_exit_ready : STD_LOGIC;
    signal ap_ready_int : STD_LOGIC;
    signal output_r_blk_n_W : STD_LOGIC;
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal input_r_blk_n_R : STD_LOGIC;
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal icmp_ln42_reg_413_pp0_iter2_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln43_fu_201_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln43_reg_427_pp0_iter2_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal xs_sign_reg_431 : STD_LOGIC_VECTOR (0 downto 0);
    signal xs_sign_reg_431_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln342_fu_245_p1 : STD_LOGIC_VECTOR (22 downto 0);
    signal trunc_ln342_reg_436 : STD_LOGIC_VECTOR (22 downto 0);
    signal tmp_fu_259_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_reg_441 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln18_fu_277_p3 : STD_LOGIC_VECTOR (8 downto 0);
    signal select_ln18_reg_446 : STD_LOGIC_VECTOR (8 downto 0);
    signal input_r_addr_read_reg_451 : STD_LOGIC_VECTOR (7 downto 0);
    signal result_fu_295_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal result_reg_456 : STD_LOGIC_VECTOR (31 downto 0);
    signal icmp_ln45_fu_311_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln45_reg_462 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln45_fu_339_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal val_1_fu_399_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal val_1_reg_473 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_phi_reg_pp0_iter0_storereflowmerge_reg_155 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_phi_reg_pp0_iter1_storereflowmerge_reg_155 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_phi_reg_pp0_iter2_storereflowmerge_reg_155 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_phi_reg_pp0_iter3_storereflowmerge_reg_155 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_phi_reg_pp0_iter4_storereflowmerge_reg_155 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal ch_fu_102 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000000";
    signal add_ln42_fu_183_p2 : STD_LOGIC_VECTOR (30 downto 0);
    signal ap_loop_init : STD_LOGIC;
    signal ap_sig_allocacmp_ch_1 : STD_LOGIC_VECTOR (30 downto 0);
    signal zext_ln42_fu_173_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal dc_fu_211_p4 : STD_LOGIC_VECTOR (1 downto 0);
    signal dc_fu_211_p5 : STD_LOGIC_VECTOR (31 downto 0);
    signal data_fu_223_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xs_exp_fu_235_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal zext_ln317_fu_249_p1 : STD_LOGIC_VECTOR (8 downto 0);
    signal add_ln317_fu_253_p2 : STD_LOGIC_VECTOR (8 downto 0);
    signal sub_ln18_fu_267_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal sext_ln18_fu_273_p1 : STD_LOGIC_VECTOR (8 downto 0);
    signal result_2_fu_290_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_1_fu_301_p4 : STD_LOGIC_VECTOR (23 downto 0);
    signal tmp_2_fu_317_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln45_fu_334_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln45_1_fu_327_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal trunc_ln45_fu_324_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal mantissa_fu_347_p4 : STD_LOGIC_VECTOR (24 downto 0);
    signal sext_ln18_1_fu_360_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln15_fu_356_p1 : STD_LOGIC_VECTOR (78 downto 0);
    signal zext_ln18_fu_363_p1 : STD_LOGIC_VECTOR (78 downto 0);
    signal lshr_ln18_fu_367_p2 : STD_LOGIC_VECTOR (78 downto 0);
    signal shl_ln18_fu_373_p2 : STD_LOGIC_VECTOR (78 downto 0);
    signal tmp_4_fu_379_p4 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_5_fu_389_p4 : STD_LOGIC_VECTOR (31 downto 0);
    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_continue_int : STD_LOGIC;
    signal ap_done_int : STD_LOGIC;
    signal ap_loop_exit_ready_pp0_iter1_reg : STD_LOGIC;
    signal ap_loop_exit_ready_pp0_iter2_reg : STD_LOGIC;
    signal ap_loop_exit_ready_pp0_iter3_reg : STD_LOGIC;
    signal ap_NS_fsm : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_enable_pp0 : STD_LOGIC;
    signal ap_start_int : STD_LOGIC;
    signal ap_ce_reg : STD_LOGIC;

    component applyConvolution_mux_3_2_32_1_1 IS
    generic (
        ID : INTEGER;
        NUM_STAGE : INTEGER;
        din0_WIDTH : INTEGER;
        din1_WIDTH : INTEGER;
        din2_WIDTH : INTEGER;
        din3_WIDTH : INTEGER;
        dout_WIDTH : INTEGER );
    port (
        din0 : IN STD_LOGIC_VECTOR (31 downto 0);
        din1 : IN STD_LOGIC_VECTOR (31 downto 0);
        din2 : IN STD_LOGIC_VECTOR (31 downto 0);
        din3 : IN STD_LOGIC_VECTOR (1 downto 0);
        dout : OUT STD_LOGIC_VECTOR (31 downto 0) );
    end component;


    component applyConvolution_flow_control_loop_pipe_sequential_init IS
    port (
        ap_clk : IN STD_LOGIC;
        ap_rst : IN STD_LOGIC;
        ap_start : IN STD_LOGIC;
        ap_ready : OUT STD_LOGIC;
        ap_done : OUT STD_LOGIC;
        ap_start_int : OUT STD_LOGIC;
        ap_loop_init : OUT STD_LOGIC;
        ap_ready_int : IN STD_LOGIC;
        ap_loop_exit_ready : IN STD_LOGIC;
        ap_loop_exit_done : IN STD_LOGIC;
        ap_continue_int : OUT STD_LOGIC;
        ap_done_int : IN STD_LOGIC );
    end component;



begin
    mux_3_2_32_1_1_U25 : component applyConvolution_mux_3_2_32_1_1
    generic map (
        ID => 1,
        NUM_STAGE => 1,
        din0_WIDTH => 32,
        din1_WIDTH => 32,
        din2_WIDTH => 32,
        din3_WIDTH => 2,
        dout_WIDTH => 32)
    port map (
        din0 => sum_0_5,
        din1 => sum_1_5,
        din2 => sum_2_5,
        din3 => dc_fu_211_p4,
        dout => dc_fu_211_p5);

    flow_control_loop_pipe_sequential_init_U : component applyConvolution_flow_control_loop_pipe_sequential_init
    port map (
        ap_clk => ap_clk,
        ap_rst => ap_rst,
        ap_start => ap_start,
        ap_ready => ap_ready,
        ap_done => ap_done,
        ap_start_int => ap_start_int,
        ap_loop_init => ap_loop_init,
        ap_ready_int => ap_ready_int,
        ap_loop_exit_ready => ap_condition_exit_pp0_iter0_stage0,
        ap_loop_exit_done => ap_done_int,
        ap_continue_int => ap_continue_int,
        ap_done_int => ap_done_int);





    ap_CS_fsm_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_CS_fsm <= ap_ST_fsm_pp0_stage0;
            else
                ap_CS_fsm <= ap_NS_fsm;
            end if;
        end if;
    end process;


    ap_done_reg_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_done_reg <= ap_const_logic_0;
            else
                if ((ap_continue_int = ap_const_logic_1)) then 
                    ap_done_reg <= ap_const_logic_0;
                elsif (((ap_loop_exit_ready_pp0_iter3_reg = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
                    ap_done_reg <= ap_const_logic_1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter1_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
            else
                if ((ap_const_logic_1 = ap_condition_exit_pp0_iter0_stage0)) then 
                    ap_enable_reg_pp0_iter1 <= ap_const_logic_0;
                elsif (((ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
                    ap_enable_reg_pp0_iter1 <= ap_start_int;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter2_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter2 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter2 <= ap_enable_reg_pp0_iter1;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter3_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter3 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter3 <= ap_enable_reg_pp0_iter2;
                end if; 
            end if;
        end if;
    end process;


    ap_enable_reg_pp0_iter4_assign_proc : process(ap_clk)
    begin
        if (ap_clk'event and ap_clk =  '1') then
            if (ap_rst = '1') then
                ap_enable_reg_pp0_iter4 <= ap_const_logic_0;
            else
                if ((ap_const_boolean_0 = ap_block_pp0_stage0_subdone)) then 
                    ap_enable_reg_pp0_iter4 <= ap_enable_reg_pp0_iter3;
                end if; 
            end if;
        end if;
    end process;


    ap_phi_reg_pp0_iter4_storereflowmerge_reg_155_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_enable_reg_pp0_iter3 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                if (((icmp_ln43_reg_427_pp0_iter2_reg = ap_const_lv1_0) and (icmp_ln42_reg_413_pp0_iter2_reg = ap_const_lv1_1))) then 
                    ap_phi_reg_pp0_iter4_storereflowmerge_reg_155 <= input_r_addr_read_reg_451;
                elsif (((icmp_ln43_reg_427_pp0_iter2_reg = ap_const_lv1_1) and (icmp_ln42_reg_413_pp0_iter2_reg = ap_const_lv1_1))) then 
                    ap_phi_reg_pp0_iter4_storereflowmerge_reg_155 <= select_ln45_fu_339_p3;
                elsif ((ap_const_boolean_1 = ap_const_boolean_1)) then 
                    ap_phi_reg_pp0_iter4_storereflowmerge_reg_155 <= ap_phi_reg_pp0_iter3_storereflowmerge_reg_155;
                end if;
            end if; 
        end if;
    end process;

    ch_fu_102_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                if (((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (icmp_ln42_fu_177_p2 = ap_const_lv1_1))) then 
                    ch_fu_102 <= add_ln42_fu_183_p2;
                elsif ((ap_loop_init = ap_const_logic_1)) then 
                    ch_fu_102 <= ap_const_lv31_0;
                end if;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                ap_loop_exit_ready_pp0_iter1_reg <= ap_loop_exit_ready;
                ap_loop_exit_ready_pp0_iter2_reg <= ap_loop_exit_ready_pp0_iter1_reg;
                icmp_ln42_reg_413 <= icmp_ln42_fu_177_p2;
                icmp_ln42_reg_413_pp0_iter1_reg <= icmp_ln42_reg_413;
                icmp_ln43_reg_427 <= icmp_ln43_fu_201_p2;
                icmp_ln43_reg_427_pp0_iter1_reg <= icmp_ln43_reg_427;
                select_ln18_reg_446 <= select_ln18_fu_277_p3;
                tmp_reg_441 <= add_ln317_fu_253_p2(8 downto 8);
                trunc_ln342_reg_436 <= trunc_ln342_fu_245_p1;
                val_1_reg_473 <= val_1_fu_399_p3;
                xs_sign_reg_431 <= data_fu_223_p1(31 downto 31);
                xs_sign_reg_431_pp0_iter1_reg <= xs_sign_reg_431;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_boolean_0 = ap_block_pp0_stage0_11001)) then
                ap_loop_exit_ready_pp0_iter3_reg <= ap_loop_exit_ready_pp0_iter2_reg;
                icmp_ln42_reg_413_pp0_iter2_reg <= icmp_ln42_reg_413_pp0_iter1_reg;
                icmp_ln43_reg_427_pp0_iter2_reg <= icmp_ln43_reg_427_pp0_iter1_reg;
                icmp_ln45_reg_462 <= icmp_ln45_fu_311_p2;
                input_r_addr_read_reg_451 <= m_axi_input_r_RDATA;
                result_reg_456 <= result_fu_295_p3;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                ap_phi_reg_pp0_iter1_storereflowmerge_reg_155 <= ap_phi_reg_pp0_iter0_storereflowmerge_reg_155;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_enable_reg_pp0_iter1 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                ap_phi_reg_pp0_iter2_storereflowmerge_reg_155 <= ap_phi_reg_pp0_iter1_storereflowmerge_reg_155;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then
                ap_phi_reg_pp0_iter3_storereflowmerge_reg_155 <= ap_phi_reg_pp0_iter2_storereflowmerge_reg_155;
            end if;
        end if;
    end process;

    ap_NS_fsm_assign_proc : process (ap_CS_fsm)
    begin
        case ap_CS_fsm is
            when ap_ST_fsm_pp0_stage0 => 
                ap_NS_fsm <= ap_ST_fsm_pp0_stage0;
            when others =>  
                ap_NS_fsm <= "X";
        end case;
    end process;
    add_ln317_fu_253_p2 <= std_logic_vector(unsigned(zext_ln317_fu_249_p1) + unsigned(ap_const_lv9_181));
    add_ln42_fu_183_p2 <= std_logic_vector(unsigned(ap_sig_allocacmp_ch_1) + unsigned(ap_const_lv31_1));
    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(0);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_pp0_stage0_01001_assign_proc : process(ap_enable_reg_pp0_iter2, ap_block_state2_pp0_stage0_iter2)
    begin
                ap_block_pp0_stage0_01001 <= ((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state2_pp0_stage0_iter2));
    end process;


    ap_block_pp0_stage0_11001_assign_proc : process(ap_enable_reg_pp0_iter2, ap_enable_reg_pp0_iter4, ap_block_state2_pp0_stage0_iter2, m_axi_output_r_WREADY)
    begin
                ap_block_pp0_stage0_11001 <= (((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (m_axi_output_r_WREADY = ap_const_logic_0)) or ((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state2_pp0_stage0_iter2)));
    end process;


    ap_block_pp0_stage0_subdone_assign_proc : process(ap_enable_reg_pp0_iter2, ap_enable_reg_pp0_iter4, ap_block_state2_pp0_stage0_iter2, m_axi_output_r_WREADY)
    begin
                ap_block_pp0_stage0_subdone <= (((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (m_axi_output_r_WREADY = ap_const_logic_0)) or ((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state2_pp0_stage0_iter2)));
    end process;


    ap_block_state2_pp0_stage0_iter2_assign_proc : process(m_axi_input_r_RVALID, ap_predicate_op45_read_state2)
    begin
                ap_block_state2_pp0_stage0_iter2 <= ((m_axi_input_r_RVALID = ap_const_logic_0) and (ap_predicate_op45_read_state2 = ap_const_boolean_1));
    end process;


    ap_condition_exit_pp0_iter0_stage0_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_subdone, icmp_ln42_fu_177_p2)
    begin
        if (((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (icmp_ln42_fu_177_p2 = ap_const_lv1_0) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_1;
        else 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_0;
        end if; 
    end process;


    ap_done_int_assign_proc : process(ap_block_pp0_stage0_subdone, ap_done_reg, ap_loop_exit_ready_pp0_iter3_reg)
    begin
        if (((ap_loop_exit_ready_pp0_iter3_reg = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
            ap_done_int <= ap_const_logic_1;
        else 
            ap_done_int <= ap_done_reg;
        end if; 
    end process;

    ap_enable_pp0 <= (ap_idle_pp0 xor ap_const_logic_1);
    ap_enable_reg_pp0_iter0 <= ap_start_int;

    ap_idle_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_idle_pp0, ap_start_int)
    begin
        if (((ap_start_int = ap_const_logic_0) and (ap_idle_pp0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_idle <= ap_const_logic_1;
        else 
            ap_idle <= ap_const_logic_0;
        end if; 
    end process;


    ap_idle_pp0_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, ap_enable_reg_pp0_iter2, ap_enable_reg_pp0_iter3, ap_enable_reg_pp0_iter4)
    begin
        if (((ap_enable_reg_pp0_iter4 = ap_const_logic_0) and (ap_enable_reg_pp0_iter3 = ap_const_logic_0) and (ap_enable_reg_pp0_iter2 = ap_const_logic_0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0))) then 
            ap_idle_pp0 <= ap_const_logic_1;
        else 
            ap_idle_pp0 <= ap_const_logic_0;
        end if; 
    end process;

    ap_loop_exit_ready <= ap_condition_exit_pp0_iter0_stage0;
    ap_phi_reg_pp0_iter0_storereflowmerge_reg_155 <= "XXXXXXXX";

    ap_predicate_op45_read_state2_assign_proc : process(icmp_ln42_reg_413_pp0_iter1_reg, icmp_ln43_reg_427_pp0_iter1_reg)
    begin
                ap_predicate_op45_read_state2 <= ((icmp_ln43_reg_427_pp0_iter1_reg = ap_const_lv1_0) and (icmp_ln42_reg_413_pp0_iter1_reg = ap_const_lv1_1));
    end process;


    ap_ready_int_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_enable_reg_pp0_iter0, ap_block_pp0_stage0_subdone)
    begin
        if (((ap_enable_reg_pp0_iter0 = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0_subdone))) then 
            ap_ready_int <= ap_const_logic_1;
        else 
            ap_ready_int <= ap_const_logic_0;
        end if; 
    end process;


    ap_sig_allocacmp_ch_1_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0, ch_fu_102, ap_loop_init)
    begin
        if (((ap_loop_init = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_const_boolean_0 = ap_block_pp0_stage0))) then 
            ap_sig_allocacmp_ch_1 <= ap_const_lv31_0;
        else 
            ap_sig_allocacmp_ch_1 <= ch_fu_102;
        end if; 
    end process;

    data_fu_223_p1 <= dc_fu_211_p5;
    dc_fu_211_p4 <= ap_sig_allocacmp_ch_1(2 - 1 downto 0);
    icmp_ln42_fu_177_p2 <= "1" when (signed(zext_ln42_fu_173_p1) < signed(channels)) else "0";
    icmp_ln43_fu_201_p2 <= "1" when (unsigned(ap_sig_allocacmp_ch_1) < unsigned(ap_const_lv31_3)) else "0";
    icmp_ln45_fu_311_p2 <= "1" when (signed(tmp_1_fu_301_p4) > signed(ap_const_lv24_0)) else "0";

    input_r_blk_n_R_assign_proc : process(ap_enable_reg_pp0_iter2, m_axi_input_r_RVALID, ap_predicate_op45_read_state2, ap_block_pp0_stage0)
    begin
        if (((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_predicate_op45_read_state2 = ap_const_boolean_1))) then 
            input_r_blk_n_R <= m_axi_input_r_RVALID;
        else 
            input_r_blk_n_R <= ap_const_logic_1;
        end if; 
    end process;

    lshr_ln18_fu_367_p2 <= std_logic_vector(shift_right(unsigned(zext_ln15_fu_356_p1),to_integer(unsigned('0' & zext_ln18_fu_363_p1(31-1 downto 0)))));
    m_axi_input_r_ARADDR <= ap_const_lv64_0;
    m_axi_input_r_ARBURST <= ap_const_lv2_0;
    m_axi_input_r_ARCACHE <= ap_const_lv4_0;
    m_axi_input_r_ARID <= ap_const_lv1_0;
    m_axi_input_r_ARLEN <= ap_const_lv32_0;
    m_axi_input_r_ARLOCK <= ap_const_lv2_0;
    m_axi_input_r_ARPROT <= ap_const_lv3_0;
    m_axi_input_r_ARQOS <= ap_const_lv4_0;
    m_axi_input_r_ARREGION <= ap_const_lv4_0;
    m_axi_input_r_ARSIZE <= ap_const_lv3_0;
    m_axi_input_r_ARUSER <= ap_const_lv1_0;
    m_axi_input_r_ARVALID <= ap_const_logic_0;
    m_axi_input_r_AWADDR <= ap_const_lv64_0;
    m_axi_input_r_AWBURST <= ap_const_lv2_0;
    m_axi_input_r_AWCACHE <= ap_const_lv4_0;
    m_axi_input_r_AWID <= ap_const_lv1_0;
    m_axi_input_r_AWLEN <= ap_const_lv32_0;
    m_axi_input_r_AWLOCK <= ap_const_lv2_0;
    m_axi_input_r_AWPROT <= ap_const_lv3_0;
    m_axi_input_r_AWQOS <= ap_const_lv4_0;
    m_axi_input_r_AWREGION <= ap_const_lv4_0;
    m_axi_input_r_AWSIZE <= ap_const_lv3_0;
    m_axi_input_r_AWUSER <= ap_const_lv1_0;
    m_axi_input_r_AWVALID <= ap_const_logic_0;
    m_axi_input_r_BREADY <= ap_const_logic_0;

    m_axi_input_r_RREADY_assign_proc : process(ap_enable_reg_pp0_iter2, ap_predicate_op45_read_state2, ap_block_pp0_stage0_11001)
    begin
        if (((ap_enable_reg_pp0_iter2 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_predicate_op45_read_state2 = ap_const_boolean_1))) then 
            m_axi_input_r_RREADY <= ap_const_logic_1;
        else 
            m_axi_input_r_RREADY <= ap_const_logic_0;
        end if; 
    end process;

    m_axi_input_r_WDATA <= ap_const_lv8_0;
    m_axi_input_r_WID <= ap_const_lv1_0;
    m_axi_input_r_WLAST <= ap_const_logic_0;
    m_axi_input_r_WSTRB <= ap_const_lv1_0;
    m_axi_input_r_WUSER <= ap_const_lv1_0;
    m_axi_input_r_WVALID <= ap_const_logic_0;
    m_axi_output_r_ARADDR <= ap_const_lv64_0;
    m_axi_output_r_ARBURST <= ap_const_lv2_0;
    m_axi_output_r_ARCACHE <= ap_const_lv4_0;
    m_axi_output_r_ARID <= ap_const_lv1_0;
    m_axi_output_r_ARLEN <= ap_const_lv32_0;
    m_axi_output_r_ARLOCK <= ap_const_lv2_0;
    m_axi_output_r_ARPROT <= ap_const_lv3_0;
    m_axi_output_r_ARQOS <= ap_const_lv4_0;
    m_axi_output_r_ARREGION <= ap_const_lv4_0;
    m_axi_output_r_ARSIZE <= ap_const_lv3_0;
    m_axi_output_r_ARUSER <= ap_const_lv1_0;
    m_axi_output_r_ARVALID <= ap_const_logic_0;
    m_axi_output_r_AWADDR <= ap_const_lv64_0;
    m_axi_output_r_AWBURST <= ap_const_lv2_0;
    m_axi_output_r_AWCACHE <= ap_const_lv4_0;
    m_axi_output_r_AWID <= ap_const_lv1_0;
    m_axi_output_r_AWLEN <= ap_const_lv32_0;
    m_axi_output_r_AWLOCK <= ap_const_lv2_0;
    m_axi_output_r_AWPROT <= ap_const_lv3_0;
    m_axi_output_r_AWQOS <= ap_const_lv4_0;
    m_axi_output_r_AWREGION <= ap_const_lv4_0;
    m_axi_output_r_AWSIZE <= ap_const_lv3_0;
    m_axi_output_r_AWUSER <= ap_const_lv1_0;
    m_axi_output_r_AWVALID <= ap_const_logic_0;
    m_axi_output_r_BREADY <= ap_const_logic_0;
    m_axi_output_r_RREADY <= ap_const_logic_0;
    m_axi_output_r_WDATA <= ap_phi_reg_pp0_iter4_storereflowmerge_reg_155;
    m_axi_output_r_WID <= ap_const_lv1_0;
    m_axi_output_r_WLAST <= ap_const_logic_0;
    m_axi_output_r_WSTRB <= ap_const_lv1_1;
    m_axi_output_r_WUSER <= ap_const_lv1_0;

    m_axi_output_r_WVALID_assign_proc : process(ap_enable_reg_pp0_iter4, ap_block_pp0_stage0_11001)
    begin
        if (((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001))) then 
            m_axi_output_r_WVALID <= ap_const_logic_1;
        else 
            m_axi_output_r_WVALID <= ap_const_logic_0;
        end if; 
    end process;

    mantissa_fu_347_p4 <= ((ap_const_lv1_1 & trunc_ln342_reg_436) & ap_const_lv1_0);
    or_ln45_fu_334_p2 <= (tmp_2_fu_317_p3 or icmp_ln45_reg_462);

    output_r_blk_n_W_assign_proc : process(ap_enable_reg_pp0_iter4, m_axi_output_r_WREADY, ap_block_pp0_stage0)
    begin
        if (((ap_enable_reg_pp0_iter4 = ap_const_logic_1) and (ap_const_boolean_0 = ap_block_pp0_stage0))) then 
            output_r_blk_n_W <= m_axi_output_r_WREADY;
        else 
            output_r_blk_n_W <= ap_const_logic_1;
        end if; 
    end process;

    result_2_fu_290_p2 <= std_logic_vector(unsigned(ap_const_lv32_0) - unsigned(val_1_reg_473));
    result_fu_295_p3 <= 
        result_2_fu_290_p2 when (xs_sign_reg_431_pp0_iter1_reg(0) = '1') else 
        val_1_reg_473;
    select_ln18_fu_277_p3 <= 
        sext_ln18_fu_273_p1 when (tmp_fu_259_p3(0) = '1') else 
        add_ln317_fu_253_p2;
    select_ln45_1_fu_327_p3 <= 
        ap_const_lv8_FF when (icmp_ln45_reg_462(0) = '1') else 
        ap_const_lv8_0;
    select_ln45_fu_339_p3 <= 
        select_ln45_1_fu_327_p3 when (or_ln45_fu_334_p2(0) = '1') else 
        trunc_ln45_fu_324_p1;
        sext_ln18_1_fu_360_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(select_ln18_reg_446),32));

        sext_ln18_fu_273_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(sub_ln18_fu_267_p2),9));

    shl_ln18_fu_373_p2 <= std_logic_vector(shift_left(unsigned(zext_ln15_fu_356_p1),to_integer(unsigned('0' & zext_ln18_fu_363_p1(31-1 downto 0)))));
    sub_ln18_fu_267_p2 <= std_logic_vector(unsigned(ap_const_lv8_7F) - unsigned(xs_exp_fu_235_p4));
    tmp_1_fu_301_p4 <= result_fu_295_p3(31 downto 8);
    tmp_2_fu_317_p3 <= result_reg_456(31 downto 31);
    tmp_4_fu_379_p4 <= lshr_ln18_fu_367_p2(55 downto 24);
    tmp_5_fu_389_p4 <= shl_ln18_fu_373_p2(55 downto 24);
    tmp_fu_259_p3 <= add_ln317_fu_253_p2(8 downto 8);
    trunc_ln342_fu_245_p1 <= data_fu_223_p1(23 - 1 downto 0);
    trunc_ln45_fu_324_p1 <= result_reg_456(8 - 1 downto 0);
    val_1_fu_399_p3 <= 
        tmp_4_fu_379_p4 when (tmp_reg_441(0) = '1') else 
        tmp_5_fu_389_p4;
    xs_exp_fu_235_p4 <= data_fu_223_p1(30 downto 23);
    zext_ln15_fu_356_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(mantissa_fu_347_p4),79));
    zext_ln18_fu_363_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(sext_ln18_1_fu_360_p1),79));
    zext_ln317_fu_249_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(xs_exp_fu_235_p4),9));
    zext_ln42_fu_173_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(ap_sig_allocacmp_ch_1),32));
end behav;

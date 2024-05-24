-- ==============================================================
-- Generated by Vitis HLS v2023.2
-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- ==============================================================

library IEEE;
use IEEE.std_logic_1164.all;
use IEEE.numeric_std.all;

entity applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_41_6 is
port (
    ap_clk : IN STD_LOGIC;
    ap_rst : IN STD_LOGIC;
    ap_start : IN STD_LOGIC;
    ap_done : OUT STD_LOGIC;
    ap_idle : OUT STD_LOGIC;
    ap_ready : OUT STD_LOGIC;
    image_r_TVALID : IN STD_LOGIC;
    output_r_TREADY : IN STD_LOGIC;
    channels : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_0_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_1_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    sum_2_5 : IN STD_LOGIC_VECTOR (31 downto 0);
    output_r_TDATA : OUT STD_LOGIC_VECTOR (7 downto 0);
    output_r_TVALID : OUT STD_LOGIC;
    image_r_TDATA : IN STD_LOGIC_VECTOR (7 downto 0);
    image_r_TREADY : OUT STD_LOGIC );
end;


architecture behav of applyConvolution_applyConvolution_Pipeline_VITIS_LOOP_41_6 is 
    constant ap_const_logic_1 : STD_LOGIC := '1';
    constant ap_const_logic_0 : STD_LOGIC := '0';
    constant ap_ST_fsm_pp0_stage0 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv32_0 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000000000";
    constant ap_const_boolean_1 : BOOLEAN := true;
    constant ap_const_lv1_1 : STD_LOGIC_VECTOR (0 downto 0) := "1";
    constant ap_const_lv1_0 : STD_LOGIC_VECTOR (0 downto 0) := "0";
    constant ap_const_boolean_0 : BOOLEAN := false;
    constant ap_const_lv31_0 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000000";
    constant ap_const_lv31_1 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000001";
    constant ap_const_lv31_3 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000011";
    constant ap_const_lv32_1F : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011111";
    constant ap_const_lv32_17 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000010111";
    constant ap_const_lv32_1E : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011110";
    constant ap_const_lv9_181 : STD_LOGIC_VECTOR (8 downto 0) := "110000001";
    constant ap_const_lv32_8 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000001000";
    constant ap_const_lv8_7F : STD_LOGIC_VECTOR (7 downto 0) := "01111111";
    constant ap_const_lv32_18 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000011000";
    constant ap_const_lv32_37 : STD_LOGIC_VECTOR (31 downto 0) := "00000000000000000000000000110111";
    constant ap_const_lv24_0 : STD_LOGIC_VECTOR (23 downto 0) := "000000000000000000000000";
    constant ap_const_lv8_FF : STD_LOGIC_VECTOR (7 downto 0) := "11111111";
    constant ap_const_lv8_0 : STD_LOGIC_VECTOR (7 downto 0) := "00000000";

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
    signal ap_idle_pp0 : STD_LOGIC;
    signal icmp_ln41_fu_139_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln42_fu_151_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_predicate_op25_read_state1 : BOOLEAN;
    signal ap_block_state1_pp0_stage0_iter0 : BOOLEAN;
    signal icmp_ln42_reg_371 : STD_LOGIC_VECTOR (0 downto 0);
    signal icmp_ln42_reg_371_pp0_iter2_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal ap_block_state4_pp0_stage0_iter3 : BOOLEAN;
    signal ap_block_state4_io : BOOLEAN;
    signal ap_block_pp0_stage0_subdone : BOOLEAN;
    signal ap_condition_exit_pp0_iter0_stage0 : STD_LOGIC;
    signal ap_loop_exit_ready : STD_LOGIC;
    signal ap_ready_int : STD_LOGIC;
    signal output_r_TDATA_blk_n : STD_LOGIC;
    signal ap_block_pp0_stage0 : BOOLEAN;
    signal image_r_TDATA_blk_n : STD_LOGIC;
    signal ap_block_pp0_stage0_11001 : BOOLEAN;
    signal icmp_ln42_reg_371_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal image_r_read_reg_375 : STD_LOGIC_VECTOR (7 downto 0);
    signal image_r_read_reg_375_pp0_iter1_reg : STD_LOGIC_VECTOR (7 downto 0);
    signal image_r_read_reg_375_pp0_iter2_reg : STD_LOGIC_VECTOR (7 downto 0);
    signal xs_sign_reg_380 : STD_LOGIC_VECTOR (0 downto 0);
    signal xs_sign_reg_380_pp0_iter1_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal xs_sign_reg_380_pp0_iter2_reg : STD_LOGIC_VECTOR (0 downto 0);
    signal trunc_ln342_fu_195_p1 : STD_LOGIC_VECTOR (22 downto 0);
    signal trunc_ln342_reg_385 : STD_LOGIC_VECTOR (22 downto 0);
    signal tmp_fu_209_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_reg_390 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln18_fu_227_p3 : STD_LOGIC_VECTOR (8 downto 0);
    signal select_ln18_reg_395 : STD_LOGIC_VECTOR (8 downto 0);
    signal val_1_fu_292_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal val_1_reg_400 : STD_LOGIC_VECTOR (31 downto 0);
    signal val_1_reg_400_pp0_iter2_reg : STD_LOGIC_VECTOR (31 downto 0);
    signal result_2_fu_299_p2 : STD_LOGIC_VECTOR (31 downto 0);
    signal result_2_reg_406 : STD_LOGIC_VECTOR (31 downto 0);
    signal ch_fu_86 : STD_LOGIC_VECTOR (30 downto 0) := "0000000000000000000000000000000";
    signal add_ln41_fu_145_p2 : STD_LOGIC_VECTOR (30 downto 0);
    signal ap_loop_init : STD_LOGIC;
    signal ap_sig_allocacmp_ch_1 : STD_LOGIC_VECTOR (30 downto 0);
    signal ap_block_pp0_stage0_01001 : BOOLEAN;
    signal select_ln44_1_fu_351_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal zext_ln41_fu_135_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal dc_fu_161_p4 : STD_LOGIC_VECTOR (1 downto 0);
    signal dc_fu_161_p5 : STD_LOGIC_VECTOR (31 downto 0);
    signal data_fu_173_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal xs_exp_fu_185_p4 : STD_LOGIC_VECTOR (7 downto 0);
    signal zext_ln317_fu_199_p1 : STD_LOGIC_VECTOR (8 downto 0);
    signal add_ln317_fu_203_p2 : STD_LOGIC_VECTOR (8 downto 0);
    signal sub_ln18_fu_217_p2 : STD_LOGIC_VECTOR (7 downto 0);
    signal sext_ln18_fu_223_p1 : STD_LOGIC_VECTOR (8 downto 0);
    signal mantissa_fu_240_p4 : STD_LOGIC_VECTOR (24 downto 0);
    signal sext_ln18_1_fu_253_p1 : STD_LOGIC_VECTOR (31 downto 0);
    signal zext_ln15_fu_249_p1 : STD_LOGIC_VECTOR (78 downto 0);
    signal zext_ln18_fu_256_p1 : STD_LOGIC_VECTOR (78 downto 0);
    signal lshr_ln18_fu_260_p2 : STD_LOGIC_VECTOR (78 downto 0);
    signal shl_ln18_fu_266_p2 : STD_LOGIC_VECTOR (78 downto 0);
    signal tmp_3_fu_272_p4 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_4_fu_282_p4 : STD_LOGIC_VECTOR (31 downto 0);
    signal result_fu_304_p3 : STD_LOGIC_VECTOR (31 downto 0);
    signal tmp_1_fu_309_p4 : STD_LOGIC_VECTOR (23 downto 0);
    signal icmp_ln44_fu_319_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal tmp_2_fu_325_p3 : STD_LOGIC_VECTOR (0 downto 0);
    signal or_ln44_fu_345_p2 : STD_LOGIC_VECTOR (0 downto 0);
    signal select_ln44_fu_337_p3 : STD_LOGIC_VECTOR (7 downto 0);
    signal trunc_ln44_fu_333_p1 : STD_LOGIC_VECTOR (7 downto 0);
    signal ap_done_reg : STD_LOGIC := '0';
    signal ap_continue_int : STD_LOGIC;
    signal ap_done_int : STD_LOGIC;
    signal ap_loop_exit_ready_pp0_iter1_reg : STD_LOGIC;
    signal ap_loop_exit_ready_pp0_iter2_reg : STD_LOGIC;
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
    mux_3_2_32_1_1_U24 : component applyConvolution_mux_3_2_32_1_1
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
        din3 => dc_fu_161_p4,
        dout => dc_fu_161_p5);

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
                elsif (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_loop_exit_ready_pp0_iter2_reg = ap_const_logic_1))) then 
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
                elsif (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
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


    ch_fu_86_assign_proc : process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                if (((icmp_ln41_fu_139_p2 = ap_const_lv1_1) and (ap_start_int = ap_const_logic_1))) then 
                    ch_fu_86 <= add_ln41_fu_145_p2;
                elsif ((ap_loop_init = ap_const_logic_1)) then 
                    ch_fu_86 <= ap_const_lv31_0;
                end if;
            end if; 
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then
                ap_loop_exit_ready_pp0_iter1_reg <= ap_loop_exit_ready;
                ap_loop_exit_ready_pp0_iter2_reg <= ap_loop_exit_ready_pp0_iter1_reg;
                icmp_ln42_reg_371 <= icmp_ln42_fu_151_p2;
                icmp_ln42_reg_371_pp0_iter1_reg <= icmp_ln42_reg_371;
                image_r_read_reg_375 <= image_r_TDATA;
                image_r_read_reg_375_pp0_iter1_reg <= image_r_read_reg_375;
                select_ln18_reg_395 <= select_ln18_fu_227_p3;
                tmp_reg_390 <= add_ln317_fu_203_p2(8 downto 8);
                trunc_ln342_reg_385 <= trunc_ln342_fu_195_p1;
                val_1_reg_400 <= val_1_fu_292_p3;
                xs_sign_reg_380 <= data_fu_173_p1(31 downto 31);
                xs_sign_reg_380_pp0_iter1_reg <= xs_sign_reg_380;
            end if;
        end if;
    end process;
    process (ap_clk)
    begin
        if (ap_clk'event and ap_clk = '1') then
            if ((ap_const_boolean_0 = ap_block_pp0_stage0_11001)) then
                icmp_ln42_reg_371_pp0_iter2_reg <= icmp_ln42_reg_371_pp0_iter1_reg;
                image_r_read_reg_375_pp0_iter2_reg <= image_r_read_reg_375_pp0_iter1_reg;
                result_2_reg_406 <= result_2_fu_299_p2;
                val_1_reg_400_pp0_iter2_reg <= val_1_reg_400;
                xs_sign_reg_380_pp0_iter2_reg <= xs_sign_reg_380_pp0_iter1_reg;
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
    add_ln317_fu_203_p2 <= std_logic_vector(unsigned(zext_ln317_fu_199_p1) + unsigned(ap_const_lv9_181));
    add_ln41_fu_145_p2 <= std_logic_vector(unsigned(ap_sig_allocacmp_ch_1) + unsigned(ap_const_lv31_1));
    ap_CS_fsm_pp0_stage0 <= ap_CS_fsm(0);
        ap_block_pp0_stage0 <= not((ap_const_boolean_1 = ap_const_boolean_1));

    ap_block_pp0_stage0_01001_assign_proc : process(ap_enable_reg_pp0_iter3, ap_block_state1_pp0_stage0_iter0, ap_block_state4_pp0_stage0_iter3, ap_start_int)
    begin
                ap_block_pp0_stage0_01001 <= (((ap_enable_reg_pp0_iter3 = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state4_pp0_stage0_iter3)) or ((ap_start_int = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state1_pp0_stage0_iter0)));
    end process;


    ap_block_pp0_stage0_11001_assign_proc : process(ap_enable_reg_pp0_iter3, ap_block_state1_pp0_stage0_iter0, ap_block_state4_pp0_stage0_iter3, ap_block_state4_io, ap_start_int)
    begin
                ap_block_pp0_stage0_11001 <= (((ap_enable_reg_pp0_iter3 = ap_const_logic_1) and ((ap_const_boolean_1 = ap_block_state4_io) or (ap_const_boolean_1 = ap_block_state4_pp0_stage0_iter3))) or ((ap_start_int = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state1_pp0_stage0_iter0)));
    end process;


    ap_block_pp0_stage0_subdone_assign_proc : process(ap_enable_reg_pp0_iter3, ap_block_state1_pp0_stage0_iter0, ap_block_state4_pp0_stage0_iter3, ap_block_state4_io, ap_start_int)
    begin
                ap_block_pp0_stage0_subdone <= (((ap_enable_reg_pp0_iter3 = ap_const_logic_1) and ((ap_const_boolean_1 = ap_block_state4_io) or (ap_const_boolean_1 = ap_block_state4_pp0_stage0_iter3))) or ((ap_start_int = ap_const_logic_1) and (ap_const_boolean_1 = ap_block_state1_pp0_stage0_iter0)));
    end process;


    ap_block_state1_pp0_stage0_iter0_assign_proc : process(image_r_TVALID, ap_predicate_op25_read_state1)
    begin
                ap_block_state1_pp0_stage0_iter0 <= ((ap_predicate_op25_read_state1 = ap_const_boolean_1) and (image_r_TVALID = ap_const_logic_0));
    end process;


    ap_block_state4_io_assign_proc : process(output_r_TREADY, icmp_ln42_reg_371_pp0_iter2_reg)
    begin
                ap_block_state4_io <= (((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_1) and (output_r_TREADY = ap_const_logic_0)) or ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_0) and (output_r_TREADY = ap_const_logic_0)));
    end process;


    ap_block_state4_pp0_stage0_iter3_assign_proc : process(output_r_TREADY, icmp_ln42_reg_371_pp0_iter2_reg)
    begin
                ap_block_state4_pp0_stage0_iter3 <= (((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_1) and (output_r_TREADY = ap_const_logic_0)) or ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_0) and (output_r_TREADY = ap_const_logic_0)));
    end process;


    ap_condition_exit_pp0_iter0_stage0_assign_proc : process(ap_CS_fsm_pp0_stage0, icmp_ln41_fu_139_p2, ap_block_pp0_stage0_subdone, ap_start_int)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (icmp_ln41_fu_139_p2 = ap_const_lv1_0) and (ap_start_int = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_1;
        else 
            ap_condition_exit_pp0_iter0_stage0 <= ap_const_logic_0;
        end if; 
    end process;


    ap_done_int_assign_proc : process(ap_block_pp0_stage0_subdone, ap_done_reg, ap_loop_exit_ready_pp0_iter2_reg)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_loop_exit_ready_pp0_iter2_reg = ap_const_logic_1))) then 
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


    ap_idle_pp0_assign_proc : process(ap_enable_reg_pp0_iter0, ap_enable_reg_pp0_iter1, ap_enable_reg_pp0_iter2, ap_enable_reg_pp0_iter3)
    begin
        if (((ap_enable_reg_pp0_iter3 = ap_const_logic_0) and (ap_enable_reg_pp0_iter2 = ap_const_logic_0) and (ap_enable_reg_pp0_iter1 = ap_const_logic_0) and (ap_enable_reg_pp0_iter0 = ap_const_logic_0))) then 
            ap_idle_pp0 <= ap_const_logic_1;
        else 
            ap_idle_pp0 <= ap_const_logic_0;
        end if; 
    end process;

    ap_loop_exit_ready <= ap_condition_exit_pp0_iter0_stage0;

    ap_predicate_op25_read_state1_assign_proc : process(icmp_ln41_fu_139_p2, icmp_ln42_fu_151_p2)
    begin
                ap_predicate_op25_read_state1 <= ((icmp_ln42_fu_151_p2 = ap_const_lv1_0) and (icmp_ln41_fu_139_p2 = ap_const_lv1_1));
    end process;


    ap_ready_int_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0_subdone, ap_start_int)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_subdone) and (ap_start_int = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            ap_ready_int <= ap_const_logic_1;
        else 
            ap_ready_int <= ap_const_logic_0;
        end if; 
    end process;


    ap_sig_allocacmp_ch_1_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_block_pp0_stage0, ch_fu_86, ap_loop_init)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0) and (ap_loop_init = ap_const_logic_1))) then 
            ap_sig_allocacmp_ch_1 <= ap_const_lv31_0;
        else 
            ap_sig_allocacmp_ch_1 <= ch_fu_86;
        end if; 
    end process;

    data_fu_173_p1 <= dc_fu_161_p5;
    dc_fu_161_p4 <= ap_sig_allocacmp_ch_1(2 - 1 downto 0);
    icmp_ln41_fu_139_p2 <= "1" when (signed(zext_ln41_fu_135_p1) < signed(channels)) else "0";
    icmp_ln42_fu_151_p2 <= "1" when (unsigned(ap_sig_allocacmp_ch_1) < unsigned(ap_const_lv31_3)) else "0";
    icmp_ln44_fu_319_p2 <= "1" when (signed(tmp_1_fu_309_p4) > signed(ap_const_lv24_0)) else "0";

    image_r_TDATA_blk_n_assign_proc : process(ap_CS_fsm_pp0_stage0, image_r_TVALID, ap_predicate_op25_read_state1, ap_block_pp0_stage0, ap_start_int)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_predicate_op25_read_state1 = ap_const_boolean_1) and (ap_start_int = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            image_r_TDATA_blk_n <= image_r_TVALID;
        else 
            image_r_TDATA_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    image_r_TREADY_assign_proc : process(ap_CS_fsm_pp0_stage0, ap_predicate_op25_read_state1, ap_block_pp0_stage0_11001, ap_start_int)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_predicate_op25_read_state1 = ap_const_boolean_1) and (ap_start_int = ap_const_logic_1) and (ap_const_logic_1 = ap_CS_fsm_pp0_stage0))) then 
            image_r_TREADY <= ap_const_logic_1;
        else 
            image_r_TREADY <= ap_const_logic_0;
        end if; 
    end process;

    lshr_ln18_fu_260_p2 <= std_logic_vector(shift_right(unsigned(zext_ln15_fu_249_p1),to_integer(unsigned('0' & zext_ln18_fu_256_p1(31-1 downto 0)))));
    mantissa_fu_240_p4 <= ((ap_const_lv1_1 & trunc_ln342_reg_385) & ap_const_lv1_0);
    or_ln44_fu_345_p2 <= (tmp_2_fu_325_p3 or icmp_ln44_fu_319_p2);

    output_r_TDATA_assign_proc : process(ap_enable_reg_pp0_iter3, icmp_ln42_reg_371_pp0_iter2_reg, image_r_read_reg_375_pp0_iter2_reg, ap_block_pp0_stage0_01001, select_ln44_1_fu_351_p3)
    begin
        if (((ap_const_boolean_0 = ap_block_pp0_stage0_01001) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1))) then
            if ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_1)) then 
                output_r_TDATA <= select_ln44_1_fu_351_p3;
            elsif ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_0)) then 
                output_r_TDATA <= image_r_read_reg_375_pp0_iter2_reg;
            else 
                output_r_TDATA <= "XXXXXXXX";
            end if;
        else 
            output_r_TDATA <= "XXXXXXXX";
        end if; 
    end process;


    output_r_TDATA_blk_n_assign_proc : process(ap_enable_reg_pp0_iter3, output_r_TREADY, icmp_ln42_reg_371_pp0_iter2_reg, ap_block_pp0_stage0)
    begin
        if ((((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1)) or ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_0) and (ap_const_boolean_0 = ap_block_pp0_stage0) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1)))) then 
            output_r_TDATA_blk_n <= output_r_TREADY;
        else 
            output_r_TDATA_blk_n <= ap_const_logic_1;
        end if; 
    end process;


    output_r_TVALID_assign_proc : process(ap_enable_reg_pp0_iter3, icmp_ln42_reg_371_pp0_iter2_reg, ap_block_pp0_stage0_11001)
    begin
        if ((((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_1) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1)) or ((icmp_ln42_reg_371_pp0_iter2_reg = ap_const_lv1_0) and (ap_const_boolean_0 = ap_block_pp0_stage0_11001) and (ap_enable_reg_pp0_iter3 = ap_const_logic_1)))) then 
            output_r_TVALID <= ap_const_logic_1;
        else 
            output_r_TVALID <= ap_const_logic_0;
        end if; 
    end process;

    result_2_fu_299_p2 <= std_logic_vector(unsigned(ap_const_lv32_0) - unsigned(val_1_reg_400));
    result_fu_304_p3 <= 
        result_2_reg_406 when (xs_sign_reg_380_pp0_iter2_reg(0) = '1') else 
        val_1_reg_400_pp0_iter2_reg;
    select_ln18_fu_227_p3 <= 
        sext_ln18_fu_223_p1 when (tmp_fu_209_p3(0) = '1') else 
        add_ln317_fu_203_p2;
    select_ln44_1_fu_351_p3 <= 
        select_ln44_fu_337_p3 when (or_ln44_fu_345_p2(0) = '1') else 
        trunc_ln44_fu_333_p1;
    select_ln44_fu_337_p3 <= 
        ap_const_lv8_FF when (icmp_ln44_fu_319_p2(0) = '1') else 
        ap_const_lv8_0;
        sext_ln18_1_fu_253_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(select_ln18_reg_395),32));

        sext_ln18_fu_223_p1 <= std_logic_vector(IEEE.numeric_std.resize(signed(sub_ln18_fu_217_p2),9));

    shl_ln18_fu_266_p2 <= std_logic_vector(shift_left(unsigned(zext_ln15_fu_249_p1),to_integer(unsigned('0' & zext_ln18_fu_256_p1(31-1 downto 0)))));
    sub_ln18_fu_217_p2 <= std_logic_vector(unsigned(ap_const_lv8_7F) - unsigned(xs_exp_fu_185_p4));
    tmp_1_fu_309_p4 <= result_fu_304_p3(31 downto 8);
    tmp_2_fu_325_p3 <= result_fu_304_p3(31 downto 31);
    tmp_3_fu_272_p4 <= lshr_ln18_fu_260_p2(55 downto 24);
    tmp_4_fu_282_p4 <= shl_ln18_fu_266_p2(55 downto 24);
    tmp_fu_209_p3 <= add_ln317_fu_203_p2(8 downto 8);
    trunc_ln342_fu_195_p1 <= data_fu_173_p1(23 - 1 downto 0);
    trunc_ln44_fu_333_p1 <= result_fu_304_p3(8 - 1 downto 0);
    val_1_fu_292_p3 <= 
        tmp_3_fu_272_p4 when (tmp_reg_390(0) = '1') else 
        tmp_4_fu_282_p4;
    xs_exp_fu_185_p4 <= data_fu_173_p1(30 downto 23);
    zext_ln15_fu_249_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(mantissa_fu_240_p4),79));
    zext_ln18_fu_256_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(sext_ln18_1_fu_253_p1),79));
    zext_ln317_fu_199_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(xs_exp_fu_185_p4),9));
    zext_ln41_fu_135_p1 <= std_logic_vector(IEEE.numeric_std.resize(unsigned(ap_sig_allocacmp_ch_1),32));
end behav;

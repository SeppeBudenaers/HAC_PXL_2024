-- (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- (c) Copyright 2022-2024 Advanced Micro Devices, Inc. All rights reserved.
-- 
-- This file contains confidential and proprietary information
-- of AMD and is protected under U.S. and international copyright
-- and other intellectual property laws.
-- 
-- DISCLAIMER
-- This disclaimer is not a license and does not grant any
-- rights to the materials distributed herewith. Except as
-- otherwise provided in a valid license issued to you by
-- AMD, and to the maximum extent permitted by applicable
-- law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
-- WITH ALL FAULTS, AND AMD HEREBY DISCLAIMS ALL WARRANTIES
-- AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
-- BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
-- INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
-- (2) AMD shall not be liable (whether in contract or tort,
-- including negligence, or under any other theory of
-- liability) for any loss or damage of any kind or nature
-- related to, arising under or in connection with these
-- materials, including for any direct, or any indirect,
-- special, incidental, or consequential loss or damage
-- (including loss of data, profits, goodwill, or any type of
-- loss or damage suffered as a result of any action brought
-- by a third party) even if such damage or loss was
-- reasonably foreseeable or AMD had been advised of the
-- possibility of the same.
-- 
-- CRITICAL APPLICATIONS
-- AMD products are not designed or intended to be fail-
-- safe, or for use in any application requiring fail-safe
-- performance, such as life-support or safety devices or
-- systems, Class III medical devices, nuclear facilities,
-- applications related to the deployment of airbags, or any
-- other applications that could lead to death, personal
-- injury, or severe property or environmental damage
-- (individually and collectively, "Critical
-- Applications"). Customer assumes the sole risk and
-- liability of any use of AMD products in Critical
-- Applications, subject only to applicable laws and
-- regulations governing limitations on product liability.
-- 
-- THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
-- PART OF THIS FILE AT ALL TIMES.
-- 
-- DO NOT MODIFY THIS FILE.

-- IP VLNV: xilinx.com:hls:applyConvolution:1.0
-- IP Revision: 2113571659

LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
USE ieee.numeric_std.ALL;

ENTITY design_1_applyConvolution_0_1 IS
  PORT (
    s_axi_control_AWADDR : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
    s_axi_control_AWVALID : IN STD_LOGIC;
    s_axi_control_AWREADY : OUT STD_LOGIC;
    s_axi_control_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_control_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s_axi_control_WVALID : IN STD_LOGIC;
    s_axi_control_WREADY : OUT STD_LOGIC;
    s_axi_control_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_control_BVALID : OUT STD_LOGIC;
    s_axi_control_BREADY : IN STD_LOGIC;
    s_axi_control_ARADDR : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
    s_axi_control_ARVALID : IN STD_LOGIC;
    s_axi_control_ARREADY : OUT STD_LOGIC;
    s_axi_control_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_control_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_control_RVALID : OUT STD_LOGIC;
    s_axi_control_RREADY : IN STD_LOGIC;
    s_axi_control_r_AWADDR : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s_axi_control_r_AWVALID : IN STD_LOGIC;
    s_axi_control_r_AWREADY : OUT STD_LOGIC;
    s_axi_control_r_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_control_r_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s_axi_control_r_WVALID : IN STD_LOGIC;
    s_axi_control_r_WREADY : OUT STD_LOGIC;
    s_axi_control_r_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_control_r_BVALID : OUT STD_LOGIC;
    s_axi_control_r_BREADY : IN STD_LOGIC;
    s_axi_control_r_ARADDR : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
    s_axi_control_r_ARVALID : IN STD_LOGIC;
    s_axi_control_r_ARREADY : OUT STD_LOGIC;
    s_axi_control_r_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    s_axi_control_r_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    s_axi_control_r_RVALID : OUT STD_LOGIC;
    s_axi_control_r_RREADY : IN STD_LOGIC;
    ap_clk : IN STD_LOGIC;
    ap_rst_n : IN STD_LOGIC;
    interrupt : OUT STD_LOGIC;
    m_axi_input_r_AWID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_input_r_AWADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axi_input_r_AWLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axi_input_r_AWSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_input_r_AWBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_AWLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_AWREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_AWCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_AWPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_input_r_AWQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_AWVALID : OUT STD_LOGIC;
    m_axi_input_r_AWREADY : IN STD_LOGIC;
    m_axi_input_r_WID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_input_r_WDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axi_input_r_WSTRB : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_WLAST : OUT STD_LOGIC;
    m_axi_input_r_WVALID : OUT STD_LOGIC;
    m_axi_input_r_WREADY : IN STD_LOGIC;
    m_axi_input_r_BID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_input_r_BRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_BVALID : IN STD_LOGIC;
    m_axi_input_r_BREADY : OUT STD_LOGIC;
    m_axi_input_r_ARID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_input_r_ARADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axi_input_r_ARLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axi_input_r_ARSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_input_r_ARBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_ARLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_ARREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_ARCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_ARPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_input_r_ARQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_input_r_ARVALID : OUT STD_LOGIC;
    m_axi_input_r_ARREADY : IN STD_LOGIC;
    m_axi_input_r_RID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_input_r_RDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axi_input_r_RRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_input_r_RLAST : IN STD_LOGIC;
    m_axi_input_r_RVALID : IN STD_LOGIC;
    m_axi_input_r_RREADY : OUT STD_LOGIC;
    m_axi_output_r_AWID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_output_r_AWADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axi_output_r_AWLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axi_output_r_AWSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_output_r_AWBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_AWLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_AWREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_AWCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_AWPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_output_r_AWQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_AWVALID : OUT STD_LOGIC;
    m_axi_output_r_AWREADY : IN STD_LOGIC;
    m_axi_output_r_WID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_output_r_WDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axi_output_r_WSTRB : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_WLAST : OUT STD_LOGIC;
    m_axi_output_r_WVALID : OUT STD_LOGIC;
    m_axi_output_r_WREADY : IN STD_LOGIC;
    m_axi_output_r_BID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_output_r_BRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_BVALID : IN STD_LOGIC;
    m_axi_output_r_BREADY : OUT STD_LOGIC;
    m_axi_output_r_ARID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_output_r_ARADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
    m_axi_output_r_ARLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
    m_axi_output_r_ARSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_output_r_ARBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_ARLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_ARREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_ARCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_ARPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
    m_axi_output_r_ARQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
    m_axi_output_r_ARVALID : OUT STD_LOGIC;
    m_axi_output_r_ARREADY : IN STD_LOGIC;
    m_axi_output_r_RID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
    m_axi_output_r_RDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
    m_axi_output_r_RRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
    m_axi_output_r_RLAST : IN STD_LOGIC;
    m_axi_output_r_RVALID : IN STD_LOGIC;
    m_axi_output_r_RREADY : OUT STD_LOGIC
  );
END design_1_applyConvolution_0_1;

ARCHITECTURE design_1_applyConvolution_0_1_arch OF design_1_applyConvolution_0_1 IS
  ATTRIBUTE DowngradeIPIdentifiedWarnings : STRING;
  ATTRIBUTE DowngradeIPIdentifiedWarnings OF design_1_applyConvolution_0_1_arch: ARCHITECTURE IS "yes";
  COMPONENT applyConvolution IS
    GENERIC (
      C_S_AXI_CONTROL_ADDR_WIDTH : INTEGER;
      C_S_AXI_CONTROL_DATA_WIDTH : INTEGER;
      C_S_AXI_CONTROL_R_ADDR_WIDTH : INTEGER;
      C_S_AXI_CONTROL_R_DATA_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_ID_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_ADDR_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_DATA_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_AWUSER_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_ARUSER_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_WUSER_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_RUSER_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_BUSER_WIDTH : INTEGER;
      C_M_AXI_INPUT_R_USER_VALUE : INTEGER;
      C_M_AXI_INPUT_R_PROT_VALUE : INTEGER;
      C_M_AXI_INPUT_R_CACHE_VALUE : INTEGER;
      C_M_AXI_OUTPUT_R_ID_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_ADDR_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_DATA_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_AWUSER_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_ARUSER_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_WUSER_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_RUSER_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_BUSER_WIDTH : INTEGER;
      C_M_AXI_OUTPUT_R_USER_VALUE : INTEGER;
      C_M_AXI_OUTPUT_R_PROT_VALUE : INTEGER;
      C_M_AXI_OUTPUT_R_CACHE_VALUE : INTEGER
    );
    PORT (
      s_axi_control_AWADDR : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
      s_axi_control_AWVALID : IN STD_LOGIC;
      s_axi_control_AWREADY : OUT STD_LOGIC;
      s_axi_control_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_control_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s_axi_control_WVALID : IN STD_LOGIC;
      s_axi_control_WREADY : OUT STD_LOGIC;
      s_axi_control_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_control_BVALID : OUT STD_LOGIC;
      s_axi_control_BREADY : IN STD_LOGIC;
      s_axi_control_ARADDR : IN STD_LOGIC_VECTOR(5 DOWNTO 0);
      s_axi_control_ARVALID : IN STD_LOGIC;
      s_axi_control_ARREADY : OUT STD_LOGIC;
      s_axi_control_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_control_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_control_RVALID : OUT STD_LOGIC;
      s_axi_control_RREADY : IN STD_LOGIC;
      s_axi_control_r_AWADDR : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s_axi_control_r_AWVALID : IN STD_LOGIC;
      s_axi_control_r_AWREADY : OUT STD_LOGIC;
      s_axi_control_r_WDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_control_r_WSTRB : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s_axi_control_r_WVALID : IN STD_LOGIC;
      s_axi_control_r_WREADY : OUT STD_LOGIC;
      s_axi_control_r_BRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_control_r_BVALID : OUT STD_LOGIC;
      s_axi_control_r_BREADY : IN STD_LOGIC;
      s_axi_control_r_ARADDR : IN STD_LOGIC_VECTOR(3 DOWNTO 0);
      s_axi_control_r_ARVALID : IN STD_LOGIC;
      s_axi_control_r_ARREADY : OUT STD_LOGIC;
      s_axi_control_r_RDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      s_axi_control_r_RRESP : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      s_axi_control_r_RVALID : OUT STD_LOGIC;
      s_axi_control_r_RREADY : IN STD_LOGIC;
      ap_clk : IN STD_LOGIC;
      ap_rst_n : IN STD_LOGIC;
      interrupt : OUT STD_LOGIC;
      m_axi_input_r_AWID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_AWADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
      m_axi_input_r_AWLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      m_axi_input_r_AWSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_input_r_AWBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_AWLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_AWREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_AWCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_AWPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_input_r_AWQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_AWUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_AWVALID : OUT STD_LOGIC;
      m_axi_input_r_AWREADY : IN STD_LOGIC;
      m_axi_input_r_WID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_WDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      m_axi_input_r_WSTRB : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_WLAST : OUT STD_LOGIC;
      m_axi_input_r_WUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_WVALID : OUT STD_LOGIC;
      m_axi_input_r_WREADY : IN STD_LOGIC;
      m_axi_input_r_BID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_BRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_BUSER : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_BVALID : IN STD_LOGIC;
      m_axi_input_r_BREADY : OUT STD_LOGIC;
      m_axi_input_r_ARID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_ARADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
      m_axi_input_r_ARLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      m_axi_input_r_ARSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_input_r_ARBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_ARLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_ARREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_ARCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_ARPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_input_r_ARQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_input_r_ARUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_ARVALID : OUT STD_LOGIC;
      m_axi_input_r_ARREADY : IN STD_LOGIC;
      m_axi_input_r_RID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_RDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      m_axi_input_r_RRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_input_r_RLAST : IN STD_LOGIC;
      m_axi_input_r_RUSER : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_input_r_RVALID : IN STD_LOGIC;
      m_axi_input_r_RREADY : OUT STD_LOGIC;
      m_axi_output_r_AWID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_AWADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
      m_axi_output_r_AWLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      m_axi_output_r_AWSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_output_r_AWBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_AWLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_AWREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_AWCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_AWPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_output_r_AWQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_AWUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_AWVALID : OUT STD_LOGIC;
      m_axi_output_r_AWREADY : IN STD_LOGIC;
      m_axi_output_r_WID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_WDATA : OUT STD_LOGIC_VECTOR(31 DOWNTO 0);
      m_axi_output_r_WSTRB : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_WLAST : OUT STD_LOGIC;
      m_axi_output_r_WUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_WVALID : OUT STD_LOGIC;
      m_axi_output_r_WREADY : IN STD_LOGIC;
      m_axi_output_r_BID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_BRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_BUSER : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_BVALID : IN STD_LOGIC;
      m_axi_output_r_BREADY : OUT STD_LOGIC;
      m_axi_output_r_ARID : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_ARADDR : OUT STD_LOGIC_VECTOR(63 DOWNTO 0);
      m_axi_output_r_ARLEN : OUT STD_LOGIC_VECTOR(7 DOWNTO 0);
      m_axi_output_r_ARSIZE : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_output_r_ARBURST : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_ARLOCK : OUT STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_ARREGION : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_ARCACHE : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_ARPROT : OUT STD_LOGIC_VECTOR(2 DOWNTO 0);
      m_axi_output_r_ARQOS : OUT STD_LOGIC_VECTOR(3 DOWNTO 0);
      m_axi_output_r_ARUSER : OUT STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_ARVALID : OUT STD_LOGIC;
      m_axi_output_r_ARREADY : IN STD_LOGIC;
      m_axi_output_r_RID : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_RDATA : IN STD_LOGIC_VECTOR(31 DOWNTO 0);
      m_axi_output_r_RRESP : IN STD_LOGIC_VECTOR(1 DOWNTO 0);
      m_axi_output_r_RLAST : IN STD_LOGIC;
      m_axi_output_r_RUSER : IN STD_LOGIC_VECTOR(0 DOWNTO 0);
      m_axi_output_r_RVALID : IN STD_LOGIC;
      m_axi_output_r_RREADY : OUT STD_LOGIC
    );
  END COMPONENT applyConvolution;
  ATTRIBUTE X_CORE_INFO : STRING;
  ATTRIBUTE X_CORE_INFO OF design_1_applyConvolution_0_1_arch: ARCHITECTURE IS "applyConvolution,Vivado 2023.2";
  ATTRIBUTE CHECK_LICENSE_TYPE : STRING;
  ATTRIBUTE CHECK_LICENSE_TYPE OF design_1_applyConvolution_0_1_arch : ARCHITECTURE IS "design_1_applyConvolution_0_1,applyConvolution,{}";
  ATTRIBUTE CORE_GENERATION_INFO : STRING;
  ATTRIBUTE CORE_GENERATION_INFO OF design_1_applyConvolution_0_1_arch: ARCHITECTURE IS "design_1_applyConvolution_0_1,applyConvolution,{x_ipProduct=Vivado 2023.2,x_ipVendor=xilinx.com,x_ipLibrary=hls,x_ipName=applyConvolution,x_ipVersion=1.0,x_ipCoreRevision=2113571659,x_ipLanguage=VHDL,x_ipSimLanguage=MIXED,C_S_AXI_CONTROL_ADDR_WIDTH=6,C_S_AXI_CONTROL_DATA_WIDTH=32,C_S_AXI_CONTROL_R_ADDR_WIDTH=4,C_S_AXI_CONTROL_R_DATA_WIDTH=32,C_M_AXI_INPUT_R_ID_WIDTH=1,C_M_AXI_INPUT_R_ADDR_WIDTH=64,C_M_AXI_INPUT_R_DATA_WIDTH=32,C_M_AXI_INPUT_R_AWUSER_WIDTH=1,C_M_AXI_INPUT_R_ARUSER_WIDTH=1,C_M_AXI" & 
"_INPUT_R_WUSER_WIDTH=1,C_M_AXI_INPUT_R_RUSER_WIDTH=1,C_M_AXI_INPUT_R_BUSER_WIDTH=1,C_M_AXI_INPUT_R_USER_VALUE=0x00000000,C_M_AXI_INPUT_R_PROT_VALUE=000,C_M_AXI_INPUT_R_CACHE_VALUE=0011,C_M_AXI_OUTPUT_R_ID_WIDTH=1,C_M_AXI_OUTPUT_R_ADDR_WIDTH=64,C_M_AXI_OUTPUT_R_DATA_WIDTH=32,C_M_AXI_OUTPUT_R_AWUSER_WIDTH=1,C_M_AXI_OUTPUT_R_ARUSER_WIDTH=1,C_M_AXI_OUTPUT_R_WUSER_WIDTH=1,C_M_AXI_OUTPUT_R_RUSER_WIDTH=1,C_M_AXI_OUTPUT_R_BUSER_WIDTH=1,C_M_AXI_OUTPUT_R_USER_VALUE=0x00000000,C_M_AXI_OUTPUT_R_PROT_VALUE=0" & 
"00,C_M_AXI_OUTPUT_R_CACHE_VALUE=0011}";
  ATTRIBUTE SDX_KERNEL : STRING;
  ATTRIBUTE SDX_KERNEL OF applyConvolution: COMPONENT IS "true";
  ATTRIBUTE SDX_KERNEL_TYPE : STRING;
  ATTRIBUTE SDX_KERNEL_TYPE OF applyConvolution: COMPONENT IS "hls";
  ATTRIBUTE SDX_KERNEL_SYNTH_INST : STRING;
  ATTRIBUTE SDX_KERNEL_SYNTH_INST OF applyConvolution: COMPONENT IS "U0";
  ATTRIBUTE IP_DEFINITION_SOURCE : STRING;
  ATTRIBUTE IP_DEFINITION_SOURCE OF design_1_applyConvolution_0_1_arch: ARCHITECTURE IS "HLS";
  ATTRIBUTE X_INTERFACE_INFO : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER : STRING;
  ATTRIBUTE X_INTERFACE_PARAMETER OF ap_clk: SIGNAL IS "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control:s_axi_control_r:m_axi_input_r:m_axi_output_r, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF ap_clk: SIGNAL IS "xilinx.com:signal:clock:1.0 ap_clk CLK";
  ATTRIBUTE X_INTERFACE_PARAMETER OF ap_rst_n: SIGNAL IS "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF ap_rst_n: SIGNAL IS "xilinx.com:signal:reset:1.0 ap_rst_n RST";
  ATTRIBUTE X_INTERFACE_PARAMETER OF interrupt: SIGNAL IS "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PORTWIDTH 1";
  ATTRIBUTE X_INTERFACE_INFO OF interrupt: SIGNAL IS "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARBURST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARBURST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARCACHE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARCACHE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARLEN: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARLEN";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARLOCK: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARLOCK";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARPROT: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARPROT";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARQOS: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARQOS";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARREGION: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARREGION";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARSIZE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARSIZE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_ARVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r ARVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWADDR";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWBURST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWBURST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWCACHE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWCACHE";
  ATTRIBUTE X_INTERFACE_PARAMETER OF m_axi_input_r_AWID: SIGNAL IS "XIL_INTERFACENAME m_axi_input_r, NUM_READ_OUTSTANDING 16, NUM_WRITE_OUTSTANDING 16, MAX_READ_BURST_LENGTH 16, MAX_WRITE_BURST_LENGTH 16, MAX_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE READ_ONLY, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 1, ADDR_WIDTH 64, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN " & 
"design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWLEN: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWLEN";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWLOCK: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWLOCK";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWPROT: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWPROT";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWQOS: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWQOS";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWREGION: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWREGION";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWSIZE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWSIZE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_AWVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_BID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r BID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_BREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_BRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_BVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RLAST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RLAST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_RVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WLAST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WLAST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WSTRB: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_input_r_WVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_input_r WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARBURST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARBURST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARCACHE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARCACHE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARLEN: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARLEN";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARLOCK: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARLOCK";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARPROT: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARPROT";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARQOS: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARQOS";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARREGION: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARREGION";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARSIZE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARSIZE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_ARVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r ARVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWADDR";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWBURST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWBURST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWCACHE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWCACHE";
  ATTRIBUTE X_INTERFACE_PARAMETER OF m_axi_output_r_AWID: SIGNAL IS "XIL_INTERFACENAME m_axi_output_r, NUM_READ_OUTSTANDING 16, NUM_WRITE_OUTSTANDING 16, MAX_READ_BURST_LENGTH 16, MAX_WRITE_BURST_LENGTH 16, MAX_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE WRITE_ONLY, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 1, ADDR_WIDTH 64, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAI" & 
"N design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWLEN: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWLEN";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWLOCK: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWLOCK";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWPROT: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWPROT";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWQOS: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWQOS";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWREGION: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWREGION";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWSIZE: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWSIZE";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_AWVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_BID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r BID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_BREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_BRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_BVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RLAST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RLAST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_RVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WID";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WLAST: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WLAST";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WSTRB: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF m_axi_output_r_WVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 m_axi_output_r WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_ARADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_ARREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_ARVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s_axi_control_AWADDR: SIGNAL IS "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_T" & 
"HREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_AWADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_AWREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_AWVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_BREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_BRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_BVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_RDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_RREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_RRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_RVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_WDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_WREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_WSTRB: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_WVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control WVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_ARADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r ARADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_ARREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r ARREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_ARVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r ARVALID";
  ATTRIBUTE X_INTERFACE_PARAMETER OF s_axi_control_r_AWADDR: SIGNAL IS "XIL_INTERFACENAME s_axi_control_r, ADDR_WIDTH 4, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ" & 
"_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_AWADDR: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r AWADDR";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_AWREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r AWREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_AWVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r AWVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_BREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r BREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_BRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r BRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_BVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r BVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_RDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r RDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_RREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r RREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_RRESP: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r RRESP";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_RVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r RVALID";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_WDATA: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r WDATA";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_WREADY: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r WREADY";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_WSTRB: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r WSTRB";
  ATTRIBUTE X_INTERFACE_INFO OF s_axi_control_r_WVALID: SIGNAL IS "xilinx.com:interface:aximm:1.0 s_axi_control_r WVALID";
BEGIN
  U0 : applyConvolution
    GENERIC MAP (
      C_S_AXI_CONTROL_ADDR_WIDTH => 6,
      C_S_AXI_CONTROL_DATA_WIDTH => 32,
      C_S_AXI_CONTROL_R_ADDR_WIDTH => 4,
      C_S_AXI_CONTROL_R_DATA_WIDTH => 32,
      C_M_AXI_INPUT_R_ID_WIDTH => 1,
      C_M_AXI_INPUT_R_ADDR_WIDTH => 64,
      C_M_AXI_INPUT_R_DATA_WIDTH => 32,
      C_M_AXI_INPUT_R_AWUSER_WIDTH => 1,
      C_M_AXI_INPUT_R_ARUSER_WIDTH => 1,
      C_M_AXI_INPUT_R_WUSER_WIDTH => 1,
      C_M_AXI_INPUT_R_RUSER_WIDTH => 1,
      C_M_AXI_INPUT_R_BUSER_WIDTH => 1,
      C_M_AXI_INPUT_R_USER_VALUE => 0,
      C_M_AXI_INPUT_R_PROT_VALUE => 0,
      C_M_AXI_INPUT_R_CACHE_VALUE => 3,
      C_M_AXI_OUTPUT_R_ID_WIDTH => 1,
      C_M_AXI_OUTPUT_R_ADDR_WIDTH => 64,
      C_M_AXI_OUTPUT_R_DATA_WIDTH => 32,
      C_M_AXI_OUTPUT_R_AWUSER_WIDTH => 1,
      C_M_AXI_OUTPUT_R_ARUSER_WIDTH => 1,
      C_M_AXI_OUTPUT_R_WUSER_WIDTH => 1,
      C_M_AXI_OUTPUT_R_RUSER_WIDTH => 1,
      C_M_AXI_OUTPUT_R_BUSER_WIDTH => 1,
      C_M_AXI_OUTPUT_R_USER_VALUE => 0,
      C_M_AXI_OUTPUT_R_PROT_VALUE => 0,
      C_M_AXI_OUTPUT_R_CACHE_VALUE => 3
    )
    PORT MAP (
      s_axi_control_AWADDR => s_axi_control_AWADDR,
      s_axi_control_AWVALID => s_axi_control_AWVALID,
      s_axi_control_AWREADY => s_axi_control_AWREADY,
      s_axi_control_WDATA => s_axi_control_WDATA,
      s_axi_control_WSTRB => s_axi_control_WSTRB,
      s_axi_control_WVALID => s_axi_control_WVALID,
      s_axi_control_WREADY => s_axi_control_WREADY,
      s_axi_control_BRESP => s_axi_control_BRESP,
      s_axi_control_BVALID => s_axi_control_BVALID,
      s_axi_control_BREADY => s_axi_control_BREADY,
      s_axi_control_ARADDR => s_axi_control_ARADDR,
      s_axi_control_ARVALID => s_axi_control_ARVALID,
      s_axi_control_ARREADY => s_axi_control_ARREADY,
      s_axi_control_RDATA => s_axi_control_RDATA,
      s_axi_control_RRESP => s_axi_control_RRESP,
      s_axi_control_RVALID => s_axi_control_RVALID,
      s_axi_control_RREADY => s_axi_control_RREADY,
      s_axi_control_r_AWADDR => s_axi_control_r_AWADDR,
      s_axi_control_r_AWVALID => s_axi_control_r_AWVALID,
      s_axi_control_r_AWREADY => s_axi_control_r_AWREADY,
      s_axi_control_r_WDATA => s_axi_control_r_WDATA,
      s_axi_control_r_WSTRB => s_axi_control_r_WSTRB,
      s_axi_control_r_WVALID => s_axi_control_r_WVALID,
      s_axi_control_r_WREADY => s_axi_control_r_WREADY,
      s_axi_control_r_BRESP => s_axi_control_r_BRESP,
      s_axi_control_r_BVALID => s_axi_control_r_BVALID,
      s_axi_control_r_BREADY => s_axi_control_r_BREADY,
      s_axi_control_r_ARADDR => s_axi_control_r_ARADDR,
      s_axi_control_r_ARVALID => s_axi_control_r_ARVALID,
      s_axi_control_r_ARREADY => s_axi_control_r_ARREADY,
      s_axi_control_r_RDATA => s_axi_control_r_RDATA,
      s_axi_control_r_RRESP => s_axi_control_r_RRESP,
      s_axi_control_r_RVALID => s_axi_control_r_RVALID,
      s_axi_control_r_RREADY => s_axi_control_r_RREADY,
      ap_clk => ap_clk,
      ap_rst_n => ap_rst_n,
      interrupt => interrupt,
      m_axi_input_r_AWID => m_axi_input_r_AWID,
      m_axi_input_r_AWADDR => m_axi_input_r_AWADDR,
      m_axi_input_r_AWLEN => m_axi_input_r_AWLEN,
      m_axi_input_r_AWSIZE => m_axi_input_r_AWSIZE,
      m_axi_input_r_AWBURST => m_axi_input_r_AWBURST,
      m_axi_input_r_AWLOCK => m_axi_input_r_AWLOCK,
      m_axi_input_r_AWREGION => m_axi_input_r_AWREGION,
      m_axi_input_r_AWCACHE => m_axi_input_r_AWCACHE,
      m_axi_input_r_AWPROT => m_axi_input_r_AWPROT,
      m_axi_input_r_AWQOS => m_axi_input_r_AWQOS,
      m_axi_input_r_AWVALID => m_axi_input_r_AWVALID,
      m_axi_input_r_AWREADY => m_axi_input_r_AWREADY,
      m_axi_input_r_WID => m_axi_input_r_WID,
      m_axi_input_r_WDATA => m_axi_input_r_WDATA,
      m_axi_input_r_WSTRB => m_axi_input_r_WSTRB,
      m_axi_input_r_WLAST => m_axi_input_r_WLAST,
      m_axi_input_r_WVALID => m_axi_input_r_WVALID,
      m_axi_input_r_WREADY => m_axi_input_r_WREADY,
      m_axi_input_r_BID => m_axi_input_r_BID,
      m_axi_input_r_BRESP => m_axi_input_r_BRESP,
      m_axi_input_r_BUSER => STD_LOGIC_VECTOR(TO_UNSIGNED(0, 1)),
      m_axi_input_r_BVALID => m_axi_input_r_BVALID,
      m_axi_input_r_BREADY => m_axi_input_r_BREADY,
      m_axi_input_r_ARID => m_axi_input_r_ARID,
      m_axi_input_r_ARADDR => m_axi_input_r_ARADDR,
      m_axi_input_r_ARLEN => m_axi_input_r_ARLEN,
      m_axi_input_r_ARSIZE => m_axi_input_r_ARSIZE,
      m_axi_input_r_ARBURST => m_axi_input_r_ARBURST,
      m_axi_input_r_ARLOCK => m_axi_input_r_ARLOCK,
      m_axi_input_r_ARREGION => m_axi_input_r_ARREGION,
      m_axi_input_r_ARCACHE => m_axi_input_r_ARCACHE,
      m_axi_input_r_ARPROT => m_axi_input_r_ARPROT,
      m_axi_input_r_ARQOS => m_axi_input_r_ARQOS,
      m_axi_input_r_ARVALID => m_axi_input_r_ARVALID,
      m_axi_input_r_ARREADY => m_axi_input_r_ARREADY,
      m_axi_input_r_RID => m_axi_input_r_RID,
      m_axi_input_r_RDATA => m_axi_input_r_RDATA,
      m_axi_input_r_RRESP => m_axi_input_r_RRESP,
      m_axi_input_r_RLAST => m_axi_input_r_RLAST,
      m_axi_input_r_RUSER => STD_LOGIC_VECTOR(TO_UNSIGNED(0, 1)),
      m_axi_input_r_RVALID => m_axi_input_r_RVALID,
      m_axi_input_r_RREADY => m_axi_input_r_RREADY,
      m_axi_output_r_AWID => m_axi_output_r_AWID,
      m_axi_output_r_AWADDR => m_axi_output_r_AWADDR,
      m_axi_output_r_AWLEN => m_axi_output_r_AWLEN,
      m_axi_output_r_AWSIZE => m_axi_output_r_AWSIZE,
      m_axi_output_r_AWBURST => m_axi_output_r_AWBURST,
      m_axi_output_r_AWLOCK => m_axi_output_r_AWLOCK,
      m_axi_output_r_AWREGION => m_axi_output_r_AWREGION,
      m_axi_output_r_AWCACHE => m_axi_output_r_AWCACHE,
      m_axi_output_r_AWPROT => m_axi_output_r_AWPROT,
      m_axi_output_r_AWQOS => m_axi_output_r_AWQOS,
      m_axi_output_r_AWVALID => m_axi_output_r_AWVALID,
      m_axi_output_r_AWREADY => m_axi_output_r_AWREADY,
      m_axi_output_r_WID => m_axi_output_r_WID,
      m_axi_output_r_WDATA => m_axi_output_r_WDATA,
      m_axi_output_r_WSTRB => m_axi_output_r_WSTRB,
      m_axi_output_r_WLAST => m_axi_output_r_WLAST,
      m_axi_output_r_WVALID => m_axi_output_r_WVALID,
      m_axi_output_r_WREADY => m_axi_output_r_WREADY,
      m_axi_output_r_BID => m_axi_output_r_BID,
      m_axi_output_r_BRESP => m_axi_output_r_BRESP,
      m_axi_output_r_BUSER => STD_LOGIC_VECTOR(TO_UNSIGNED(0, 1)),
      m_axi_output_r_BVALID => m_axi_output_r_BVALID,
      m_axi_output_r_BREADY => m_axi_output_r_BREADY,
      m_axi_output_r_ARID => m_axi_output_r_ARID,
      m_axi_output_r_ARADDR => m_axi_output_r_ARADDR,
      m_axi_output_r_ARLEN => m_axi_output_r_ARLEN,
      m_axi_output_r_ARSIZE => m_axi_output_r_ARSIZE,
      m_axi_output_r_ARBURST => m_axi_output_r_ARBURST,
      m_axi_output_r_ARLOCK => m_axi_output_r_ARLOCK,
      m_axi_output_r_ARREGION => m_axi_output_r_ARREGION,
      m_axi_output_r_ARCACHE => m_axi_output_r_ARCACHE,
      m_axi_output_r_ARPROT => m_axi_output_r_ARPROT,
      m_axi_output_r_ARQOS => m_axi_output_r_ARQOS,
      m_axi_output_r_ARVALID => m_axi_output_r_ARVALID,
      m_axi_output_r_ARREADY => m_axi_output_r_ARREADY,
      m_axi_output_r_RID => m_axi_output_r_RID,
      m_axi_output_r_RDATA => m_axi_output_r_RDATA,
      m_axi_output_r_RRESP => m_axi_output_r_RRESP,
      m_axi_output_r_RLAST => m_axi_output_r_RLAST,
      m_axi_output_r_RUSER => STD_LOGIC_VECTOR(TO_UNSIGNED(0, 1)),
      m_axi_output_r_RVALID => m_axi_output_r_RVALID,
      m_axi_output_r_RREADY => m_axi_output_r_RREADY
    );
END design_1_applyConvolution_0_1_arch;

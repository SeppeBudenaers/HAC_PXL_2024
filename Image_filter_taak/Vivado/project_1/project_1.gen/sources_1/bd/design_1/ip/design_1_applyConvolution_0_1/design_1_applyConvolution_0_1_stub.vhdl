-- Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
-- Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2023.2 (win64) Build 4029153 Fri Oct 13 20:14:34 MDT 2023
-- Date        : Fri May 24 16:00:59 2024
-- Host        : Beta running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub
--               c:/XilinxDev/HACPXL2024/Image_filter_taak/Vivado/project_1/project_1.gen/sources_1/bd/design_1/ip/design_1_applyConvolution_0_1/design_1_applyConvolution_0_1_stub.vhdl
-- Design      : design_1_applyConvolution_0_1
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7z020clg400-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity design_1_applyConvolution_0_1 is
  Port ( 
    s_axi_control_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_control_AWVALID : in STD_LOGIC;
    s_axi_control_AWREADY : out STD_LOGIC;
    s_axi_control_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_control_WVALID : in STD_LOGIC;
    s_axi_control_WREADY : out STD_LOGIC;
    s_axi_control_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_BVALID : out STD_LOGIC;
    s_axi_control_BREADY : in STD_LOGIC;
    s_axi_control_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_control_ARVALID : in STD_LOGIC;
    s_axi_control_ARREADY : out STD_LOGIC;
    s_axi_control_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_control_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_control_RVALID : out STD_LOGIC;
    s_axi_control_RREADY : in STD_LOGIC;
    s_axi_conv_AWADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_conv_AWVALID : in STD_LOGIC;
    s_axi_conv_AWREADY : out STD_LOGIC;
    s_axi_conv_WDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_conv_WSTRB : in STD_LOGIC_VECTOR ( 3 downto 0 );
    s_axi_conv_WVALID : in STD_LOGIC;
    s_axi_conv_WREADY : out STD_LOGIC;
    s_axi_conv_BRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_conv_BVALID : out STD_LOGIC;
    s_axi_conv_BREADY : in STD_LOGIC;
    s_axi_conv_ARADDR : in STD_LOGIC_VECTOR ( 5 downto 0 );
    s_axi_conv_ARVALID : in STD_LOGIC;
    s_axi_conv_ARREADY : out STD_LOGIC;
    s_axi_conv_RDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    s_axi_conv_RRESP : out STD_LOGIC_VECTOR ( 1 downto 0 );
    s_axi_conv_RVALID : out STD_LOGIC;
    s_axi_conv_RREADY : in STD_LOGIC;
    ap_clk : in STD_LOGIC;
    ap_rst_n : in STD_LOGIC;
    interrupt : out STD_LOGIC;
    m_axi_input_r_AWID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_input_r_AWADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_input_r_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_input_r_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_AWVALID : out STD_LOGIC;
    m_axi_input_r_AWREADY : in STD_LOGIC;
    m_axi_input_r_WID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_input_r_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_input_r_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_WLAST : out STD_LOGIC;
    m_axi_input_r_WVALID : out STD_LOGIC;
    m_axi_input_r_WREADY : in STD_LOGIC;
    m_axi_input_r_BID : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_input_r_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_BVALID : in STD_LOGIC;
    m_axi_input_r_BREADY : out STD_LOGIC;
    m_axi_input_r_ARID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_input_r_ARADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_input_r_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_input_r_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_input_r_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_input_r_ARVALID : out STD_LOGIC;
    m_axi_input_r_ARREADY : in STD_LOGIC;
    m_axi_input_r_RID : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_input_r_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_input_r_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_input_r_RLAST : in STD_LOGIC;
    m_axi_input_r_RVALID : in STD_LOGIC;
    m_axi_input_r_RREADY : out STD_LOGIC;
    m_axi_output_r_AWID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_output_r_AWADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_output_r_AWLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_output_r_AWSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_AWBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_AWLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_AWREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_AWQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_AWVALID : out STD_LOGIC;
    m_axi_output_r_AWREADY : in STD_LOGIC;
    m_axi_output_r_WID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_output_r_WDATA : out STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_output_r_WSTRB : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_WLAST : out STD_LOGIC;
    m_axi_output_r_WVALID : out STD_LOGIC;
    m_axi_output_r_WREADY : in STD_LOGIC;
    m_axi_output_r_BID : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_output_r_BRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_BVALID : in STD_LOGIC;
    m_axi_output_r_BREADY : out STD_LOGIC;
    m_axi_output_r_ARID : out STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_output_r_ARADDR : out STD_LOGIC_VECTOR ( 63 downto 0 );
    m_axi_output_r_ARLEN : out STD_LOGIC_VECTOR ( 7 downto 0 );
    m_axi_output_r_ARSIZE : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_ARBURST : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_ARLOCK : out STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_ARREGION : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARCACHE : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARPROT : out STD_LOGIC_VECTOR ( 2 downto 0 );
    m_axi_output_r_ARQOS : out STD_LOGIC_VECTOR ( 3 downto 0 );
    m_axi_output_r_ARVALID : out STD_LOGIC;
    m_axi_output_r_ARREADY : in STD_LOGIC;
    m_axi_output_r_RID : in STD_LOGIC_VECTOR ( 0 to 0 );
    m_axi_output_r_RDATA : in STD_LOGIC_VECTOR ( 31 downto 0 );
    m_axi_output_r_RRESP : in STD_LOGIC_VECTOR ( 1 downto 0 );
    m_axi_output_r_RLAST : in STD_LOGIC;
    m_axi_output_r_RVALID : in STD_LOGIC;
    m_axi_output_r_RREADY : out STD_LOGIC
  );

end design_1_applyConvolution_0_1;

architecture stub of design_1_applyConvolution_0_1 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "s_axi_control_AWADDR[5:0],s_axi_control_AWVALID,s_axi_control_AWREADY,s_axi_control_WDATA[31:0],s_axi_control_WSTRB[3:0],s_axi_control_WVALID,s_axi_control_WREADY,s_axi_control_BRESP[1:0],s_axi_control_BVALID,s_axi_control_BREADY,s_axi_control_ARADDR[5:0],s_axi_control_ARVALID,s_axi_control_ARREADY,s_axi_control_RDATA[31:0],s_axi_control_RRESP[1:0],s_axi_control_RVALID,s_axi_control_RREADY,s_axi_conv_AWADDR[5:0],s_axi_conv_AWVALID,s_axi_conv_AWREADY,s_axi_conv_WDATA[31:0],s_axi_conv_WSTRB[3:0],s_axi_conv_WVALID,s_axi_conv_WREADY,s_axi_conv_BRESP[1:0],s_axi_conv_BVALID,s_axi_conv_BREADY,s_axi_conv_ARADDR[5:0],s_axi_conv_ARVALID,s_axi_conv_ARREADY,s_axi_conv_RDATA[31:0],s_axi_conv_RRESP[1:0],s_axi_conv_RVALID,s_axi_conv_RREADY,ap_clk,ap_rst_n,interrupt,m_axi_input_r_AWID[0:0],m_axi_input_r_AWADDR[63:0],m_axi_input_r_AWLEN[7:0],m_axi_input_r_AWSIZE[2:0],m_axi_input_r_AWBURST[1:0],m_axi_input_r_AWLOCK[1:0],m_axi_input_r_AWREGION[3:0],m_axi_input_r_AWCACHE[3:0],m_axi_input_r_AWPROT[2:0],m_axi_input_r_AWQOS[3:0],m_axi_input_r_AWVALID,m_axi_input_r_AWREADY,m_axi_input_r_WID[0:0],m_axi_input_r_WDATA[31:0],m_axi_input_r_WSTRB[3:0],m_axi_input_r_WLAST,m_axi_input_r_WVALID,m_axi_input_r_WREADY,m_axi_input_r_BID[0:0],m_axi_input_r_BRESP[1:0],m_axi_input_r_BVALID,m_axi_input_r_BREADY,m_axi_input_r_ARID[0:0],m_axi_input_r_ARADDR[63:0],m_axi_input_r_ARLEN[7:0],m_axi_input_r_ARSIZE[2:0],m_axi_input_r_ARBURST[1:0],m_axi_input_r_ARLOCK[1:0],m_axi_input_r_ARREGION[3:0],m_axi_input_r_ARCACHE[3:0],m_axi_input_r_ARPROT[2:0],m_axi_input_r_ARQOS[3:0],m_axi_input_r_ARVALID,m_axi_input_r_ARREADY,m_axi_input_r_RID[0:0],m_axi_input_r_RDATA[31:0],m_axi_input_r_RRESP[1:0],m_axi_input_r_RLAST,m_axi_input_r_RVALID,m_axi_input_r_RREADY,m_axi_output_r_AWID[0:0],m_axi_output_r_AWADDR[63:0],m_axi_output_r_AWLEN[7:0],m_axi_output_r_AWSIZE[2:0],m_axi_output_r_AWBURST[1:0],m_axi_output_r_AWLOCK[1:0],m_axi_output_r_AWREGION[3:0],m_axi_output_r_AWCACHE[3:0],m_axi_output_r_AWPROT[2:0],m_axi_output_r_AWQOS[3:0],m_axi_output_r_AWVALID,m_axi_output_r_AWREADY,m_axi_output_r_WID[0:0],m_axi_output_r_WDATA[31:0],m_axi_output_r_WSTRB[3:0],m_axi_output_r_WLAST,m_axi_output_r_WVALID,m_axi_output_r_WREADY,m_axi_output_r_BID[0:0],m_axi_output_r_BRESP[1:0],m_axi_output_r_BVALID,m_axi_output_r_BREADY,m_axi_output_r_ARID[0:0],m_axi_output_r_ARADDR[63:0],m_axi_output_r_ARLEN[7:0],m_axi_output_r_ARSIZE[2:0],m_axi_output_r_ARBURST[1:0],m_axi_output_r_ARLOCK[1:0],m_axi_output_r_ARREGION[3:0],m_axi_output_r_ARCACHE[3:0],m_axi_output_r_ARPROT[2:0],m_axi_output_r_ARQOS[3:0],m_axi_output_r_ARVALID,m_axi_output_r_ARREADY,m_axi_output_r_RID[0:0],m_axi_output_r_RDATA[31:0],m_axi_output_r_RRESP[1:0],m_axi_output_r_RLAST,m_axi_output_r_RVALID,m_axi_output_r_RREADY";
attribute x_core_info : string;
attribute x_core_info of stub : architecture is "applyConvolution,Vivado 2023.2";
begin
end;

// (c) Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// (c) Copyright 2022-2024 Advanced Micro Devices, Inc. All rights reserved.
// 
// This file contains confidential and proprietary information
// of AMD and is protected under U.S. and international copyright
// and other intellectual property laws.
// 
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// AMD, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND AMD HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) AMD shall not be liable (whether in contract or tort,
// including negligence, or under any other theory of
// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or AMD had been advised of the
// possibility of the same.
// 
// CRITICAL APPLICATIONS
// AMD products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of AMD products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
// 
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
// 
// DO NOT MODIFY THIS FILE.


// IP VLNV: xilinx.com:hls:applyConvolution:1.0
// IP Revision: 2113571804

`timescale 1ns/1ps

(* IP_DEFINITION_SOURCE = "HLS" *)
(* DowngradeIPIdentifiedWarnings = "yes" *)
module design_1_applyConvolution_0_1 (
  s_axi_control_AWADDR,
  s_axi_control_AWVALID,
  s_axi_control_AWREADY,
  s_axi_control_WDATA,
  s_axi_control_WSTRB,
  s_axi_control_WVALID,
  s_axi_control_WREADY,
  s_axi_control_BRESP,
  s_axi_control_BVALID,
  s_axi_control_BREADY,
  s_axi_control_ARADDR,
  s_axi_control_ARVALID,
  s_axi_control_ARREADY,
  s_axi_control_RDATA,
  s_axi_control_RRESP,
  s_axi_control_RVALID,
  s_axi_control_RREADY,
  s_axi_conv_AWADDR,
  s_axi_conv_AWVALID,
  s_axi_conv_AWREADY,
  s_axi_conv_WDATA,
  s_axi_conv_WSTRB,
  s_axi_conv_WVALID,
  s_axi_conv_WREADY,
  s_axi_conv_BRESP,
  s_axi_conv_BVALID,
  s_axi_conv_BREADY,
  s_axi_conv_ARADDR,
  s_axi_conv_ARVALID,
  s_axi_conv_ARREADY,
  s_axi_conv_RDATA,
  s_axi_conv_RRESP,
  s_axi_conv_RVALID,
  s_axi_conv_RREADY,
  ap_clk,
  ap_rst_n,
  interrupt,
  m_axi_input_r_AWID,
  m_axi_input_r_AWADDR,
  m_axi_input_r_AWLEN,
  m_axi_input_r_AWSIZE,
  m_axi_input_r_AWBURST,
  m_axi_input_r_AWLOCK,
  m_axi_input_r_AWREGION,
  m_axi_input_r_AWCACHE,
  m_axi_input_r_AWPROT,
  m_axi_input_r_AWQOS,
  m_axi_input_r_AWVALID,
  m_axi_input_r_AWREADY,
  m_axi_input_r_WID,
  m_axi_input_r_WDATA,
  m_axi_input_r_WSTRB,
  m_axi_input_r_WLAST,
  m_axi_input_r_WVALID,
  m_axi_input_r_WREADY,
  m_axi_input_r_BID,
  m_axi_input_r_BRESP,
  m_axi_input_r_BVALID,
  m_axi_input_r_BREADY,
  m_axi_input_r_ARID,
  m_axi_input_r_ARADDR,
  m_axi_input_r_ARLEN,
  m_axi_input_r_ARSIZE,
  m_axi_input_r_ARBURST,
  m_axi_input_r_ARLOCK,
  m_axi_input_r_ARREGION,
  m_axi_input_r_ARCACHE,
  m_axi_input_r_ARPROT,
  m_axi_input_r_ARQOS,
  m_axi_input_r_ARVALID,
  m_axi_input_r_ARREADY,
  m_axi_input_r_RID,
  m_axi_input_r_RDATA,
  m_axi_input_r_RRESP,
  m_axi_input_r_RLAST,
  m_axi_input_r_RVALID,
  m_axi_input_r_RREADY,
  m_axi_output_r_AWID,
  m_axi_output_r_AWADDR,
  m_axi_output_r_AWLEN,
  m_axi_output_r_AWSIZE,
  m_axi_output_r_AWBURST,
  m_axi_output_r_AWLOCK,
  m_axi_output_r_AWREGION,
  m_axi_output_r_AWCACHE,
  m_axi_output_r_AWPROT,
  m_axi_output_r_AWQOS,
  m_axi_output_r_AWVALID,
  m_axi_output_r_AWREADY,
  m_axi_output_r_WID,
  m_axi_output_r_WDATA,
  m_axi_output_r_WSTRB,
  m_axi_output_r_WLAST,
  m_axi_output_r_WVALID,
  m_axi_output_r_WREADY,
  m_axi_output_r_BID,
  m_axi_output_r_BRESP,
  m_axi_output_r_BVALID,
  m_axi_output_r_BREADY,
  m_axi_output_r_ARID,
  m_axi_output_r_ARADDR,
  m_axi_output_r_ARLEN,
  m_axi_output_r_ARSIZE,
  m_axi_output_r_ARBURST,
  m_axi_output_r_ARLOCK,
  m_axi_output_r_ARREGION,
  m_axi_output_r_ARCACHE,
  m_axi_output_r_ARPROT,
  m_axi_output_r_ARQOS,
  m_axi_output_r_ARVALID,
  m_axi_output_r_ARREADY,
  m_axi_output_r_RID,
  m_axi_output_r_RDATA,
  m_axi_output_r_RRESP,
  m_axi_output_r_RLAST,
  m_axi_output_r_RVALID,
  m_axi_output_r_RREADY
);

(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWADDR" *)
input wire [5 : 0] s_axi_control_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWVALID" *)
input wire s_axi_control_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control AWREADY" *)
output wire s_axi_control_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WDATA" *)
input wire [31 : 0] s_axi_control_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WSTRB" *)
input wire [3 : 0] s_axi_control_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WVALID" *)
input wire s_axi_control_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control WREADY" *)
output wire s_axi_control_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BRESP" *)
output wire [1 : 0] s_axi_control_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BVALID" *)
output wire s_axi_control_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control BREADY" *)
input wire s_axi_control_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARADDR" *)
input wire [5 : 0] s_axi_control_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARVALID" *)
input wire s_axi_control_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control ARREADY" *)
output wire s_axi_control_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RDATA" *)
output wire [31 : 0] s_axi_control_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RRESP" *)
output wire [1 : 0] s_axi_control_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RVALID" *)
output wire s_axi_control_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_control, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_T\
HREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_control RREADY" *)
input wire s_axi_control_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv AWADDR" *)
input wire [5 : 0] s_axi_conv_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv AWVALID" *)
input wire s_axi_conv_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv AWREADY" *)
output wire s_axi_conv_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv WDATA" *)
input wire [31 : 0] s_axi_conv_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv WSTRB" *)
input wire [3 : 0] s_axi_conv_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv WVALID" *)
input wire s_axi_conv_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv WREADY" *)
output wire s_axi_conv_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv BRESP" *)
output wire [1 : 0] s_axi_conv_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv BVALID" *)
output wire s_axi_conv_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv BREADY" *)
input wire s_axi_conv_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv ARADDR" *)
input wire [5 : 0] s_axi_conv_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv ARVALID" *)
input wire s_axi_conv_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv ARREADY" *)
output wire s_axi_conv_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv RDATA" *)
output wire [31 : 0] s_axi_conv_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv RRESP" *)
output wire [1 : 0] s_axi_conv_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv RVALID" *)
output wire s_axi_conv_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME s_axi_conv, ADDR_WIDTH 6, DATA_WIDTH 32, PROTOCOL AXI4LITE, READ_WRITE_MODE READ_WRITE, FREQ_HZ 100000000, ID_WIDTH 0, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_BURST 0, HAS_LOCK 0, HAS_PROT 0, HAS_CACHE 0, HAS_QOS 0, HAS_REGION 0, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, SUPPORTS_NARROW_BURST 0, NUM_READ_OUTSTANDING 1, NUM_WRITE_OUTSTANDING 1, MAX_BURST_LENGTH 1, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_THRE\
ADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 s_axi_conv RREADY" *)
input wire s_axi_conv_RREADY;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_clk, ASSOCIATED_BUSIF s_axi_control:s_axi_conv:m_axi_input_r:m_axi_output_r, ASSOCIATED_RESET ap_rst_n, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.0, CLK_DOMAIN design_1_processing_system7_0_0_FCLK_CLK0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:clock:1.0 ap_clk CLK" *)
input wire ap_clk;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME ap_rst_n, POLARITY ACTIVE_LOW, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:reset:1.0 ap_rst_n RST" *)
input wire ap_rst_n;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME interrupt, SENSITIVITY LEVEL_HIGH, PortWidth 1" *)
(* X_INTERFACE_INFO = "xilinx.com:signal:interrupt:1.0 interrupt INTERRUPT" *)
output wire interrupt;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWID" *)
output wire [0 : 0] m_axi_input_r_AWID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWADDR" *)
output wire [63 : 0] m_axi_input_r_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWLEN" *)
output wire [7 : 0] m_axi_input_r_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWSIZE" *)
output wire [2 : 0] m_axi_input_r_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWBURST" *)
output wire [1 : 0] m_axi_input_r_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWLOCK" *)
output wire [1 : 0] m_axi_input_r_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWREGION" *)
output wire [3 : 0] m_axi_input_r_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWCACHE" *)
output wire [3 : 0] m_axi_input_r_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWPROT" *)
output wire [2 : 0] m_axi_input_r_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWQOS" *)
output wire [3 : 0] m_axi_input_r_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWVALID" *)
output wire m_axi_input_r_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r AWREADY" *)
input wire m_axi_input_r_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WID" *)
output wire [0 : 0] m_axi_input_r_WID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WDATA" *)
output wire [31 : 0] m_axi_input_r_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WSTRB" *)
output wire [3 : 0] m_axi_input_r_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WLAST" *)
output wire m_axi_input_r_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WVALID" *)
output wire m_axi_input_r_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r WREADY" *)
input wire m_axi_input_r_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r BID" *)
input wire [0 : 0] m_axi_input_r_BID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r BRESP" *)
input wire [1 : 0] m_axi_input_r_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r BVALID" *)
input wire m_axi_input_r_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r BREADY" *)
output wire m_axi_input_r_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARID" *)
output wire [0 : 0] m_axi_input_r_ARID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARADDR" *)
output wire [63 : 0] m_axi_input_r_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARLEN" *)
output wire [7 : 0] m_axi_input_r_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARSIZE" *)
output wire [2 : 0] m_axi_input_r_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARBURST" *)
output wire [1 : 0] m_axi_input_r_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARLOCK" *)
output wire [1 : 0] m_axi_input_r_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARREGION" *)
output wire [3 : 0] m_axi_input_r_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARCACHE" *)
output wire [3 : 0] m_axi_input_r_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARPROT" *)
output wire [2 : 0] m_axi_input_r_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARQOS" *)
output wire [3 : 0] m_axi_input_r_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARVALID" *)
output wire m_axi_input_r_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r ARREADY" *)
input wire m_axi_input_r_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RID" *)
input wire [0 : 0] m_axi_input_r_RID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RDATA" *)
input wire [31 : 0] m_axi_input_r_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RRESP" *)
input wire [1 : 0] m_axi_input_r_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RLAST" *)
input wire m_axi_input_r_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RVALID" *)
input wire m_axi_input_r_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_input_r, NUM_READ_OUTSTANDING 16, NUM_WRITE_OUTSTANDING 16, MAX_READ_BURST_LENGTH 16, MAX_WRITE_BURST_LENGTH 16, MAX_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE READ_ONLY, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 1, ADDR_WIDTH 64, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAIN \
design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_input_r RREADY" *)
output wire m_axi_input_r_RREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWID" *)
output wire [0 : 0] m_axi_output_r_AWID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWADDR" *)
output wire [63 : 0] m_axi_output_r_AWADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWLEN" *)
output wire [7 : 0] m_axi_output_r_AWLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWSIZE" *)
output wire [2 : 0] m_axi_output_r_AWSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWBURST" *)
output wire [1 : 0] m_axi_output_r_AWBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWLOCK" *)
output wire [1 : 0] m_axi_output_r_AWLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWREGION" *)
output wire [3 : 0] m_axi_output_r_AWREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWCACHE" *)
output wire [3 : 0] m_axi_output_r_AWCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWPROT" *)
output wire [2 : 0] m_axi_output_r_AWPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWQOS" *)
output wire [3 : 0] m_axi_output_r_AWQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWVALID" *)
output wire m_axi_output_r_AWVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r AWREADY" *)
input wire m_axi_output_r_AWREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WID" *)
output wire [0 : 0] m_axi_output_r_WID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WDATA" *)
output wire [31 : 0] m_axi_output_r_WDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WSTRB" *)
output wire [3 : 0] m_axi_output_r_WSTRB;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WLAST" *)
output wire m_axi_output_r_WLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WVALID" *)
output wire m_axi_output_r_WVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r WREADY" *)
input wire m_axi_output_r_WREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r BID" *)
input wire [0 : 0] m_axi_output_r_BID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r BRESP" *)
input wire [1 : 0] m_axi_output_r_BRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r BVALID" *)
input wire m_axi_output_r_BVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r BREADY" *)
output wire m_axi_output_r_BREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARID" *)
output wire [0 : 0] m_axi_output_r_ARID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARADDR" *)
output wire [63 : 0] m_axi_output_r_ARADDR;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARLEN" *)
output wire [7 : 0] m_axi_output_r_ARLEN;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARSIZE" *)
output wire [2 : 0] m_axi_output_r_ARSIZE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARBURST" *)
output wire [1 : 0] m_axi_output_r_ARBURST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARLOCK" *)
output wire [1 : 0] m_axi_output_r_ARLOCK;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARREGION" *)
output wire [3 : 0] m_axi_output_r_ARREGION;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARCACHE" *)
output wire [3 : 0] m_axi_output_r_ARCACHE;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARPROT" *)
output wire [2 : 0] m_axi_output_r_ARPROT;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARQOS" *)
output wire [3 : 0] m_axi_output_r_ARQOS;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARVALID" *)
output wire m_axi_output_r_ARVALID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r ARREADY" *)
input wire m_axi_output_r_ARREADY;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RID" *)
input wire [0 : 0] m_axi_output_r_RID;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RDATA" *)
input wire [31 : 0] m_axi_output_r_RDATA;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RRESP" *)
input wire [1 : 0] m_axi_output_r_RRESP;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RLAST" *)
input wire m_axi_output_r_RLAST;
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RVALID" *)
input wire m_axi_output_r_RVALID;
(* X_INTERFACE_PARAMETER = "XIL_INTERFACENAME m_axi_output_r, NUM_READ_OUTSTANDING 16, NUM_WRITE_OUTSTANDING 16, MAX_READ_BURST_LENGTH 16, MAX_WRITE_BURST_LENGTH 16, MAX_BURST_LENGTH 256, PROTOCOL AXI4, READ_WRITE_MODE WRITE_ONLY, HAS_BURST 0, SUPPORTS_NARROW_BURST 0, DATA_WIDTH 32, FREQ_HZ 100000000, ID_WIDTH 1, ADDR_WIDTH 64, AWUSER_WIDTH 0, ARUSER_WIDTH 0, WUSER_WIDTH 0, RUSER_WIDTH 0, BUSER_WIDTH 0, HAS_LOCK 1, HAS_PROT 1, HAS_CACHE 1, HAS_QOS 1, HAS_REGION 1, HAS_WSTRB 1, HAS_BRESP 1, HAS_RRESP 1, PHASE 0.0, CLK_DOMAI\
N design_1_processing_system7_0_0_FCLK_CLK0, NUM_READ_THREADS 1, NUM_WRITE_THREADS 1, RUSER_BITS_PER_BYTE 0, WUSER_BITS_PER_BYTE 0, INSERT_VIP 0" *)
(* X_INTERFACE_INFO = "xilinx.com:interface:aximm:1.0 m_axi_output_r RREADY" *)
output wire m_axi_output_r_RREADY;

(* SDX_KERNEL = "true" *)
(* SDX_KERNEL_TYPE = "hls" *)
(* SDX_KERNEL_SIM_INST = "" *)
  applyConvolution #(
    .C_S_AXI_CONTROL_ADDR_WIDTH(6),
    .C_S_AXI_CONTROL_DATA_WIDTH(32),
    .C_S_AXI_CONV_ADDR_WIDTH(6),
    .C_S_AXI_CONV_DATA_WIDTH(32),
    .C_M_AXI_INPUT_R_ID_WIDTH(1),
    .C_M_AXI_INPUT_R_ADDR_WIDTH(64),
    .C_M_AXI_INPUT_R_DATA_WIDTH(32),
    .C_M_AXI_INPUT_R_AWUSER_WIDTH(1),
    .C_M_AXI_INPUT_R_ARUSER_WIDTH(1),
    .C_M_AXI_INPUT_R_WUSER_WIDTH(1),
    .C_M_AXI_INPUT_R_RUSER_WIDTH(1),
    .C_M_AXI_INPUT_R_BUSER_WIDTH(1),
    .C_M_AXI_INPUT_R_USER_VALUE(32'H00000000),
    .C_M_AXI_INPUT_R_PROT_VALUE(3'B000),
    .C_M_AXI_INPUT_R_CACHE_VALUE(4'B0011),
    .C_M_AXI_OUTPUT_R_ID_WIDTH(1),
    .C_M_AXI_OUTPUT_R_ADDR_WIDTH(64),
    .C_M_AXI_OUTPUT_R_DATA_WIDTH(32),
    .C_M_AXI_OUTPUT_R_AWUSER_WIDTH(1),
    .C_M_AXI_OUTPUT_R_ARUSER_WIDTH(1),
    .C_M_AXI_OUTPUT_R_WUSER_WIDTH(1),
    .C_M_AXI_OUTPUT_R_RUSER_WIDTH(1),
    .C_M_AXI_OUTPUT_R_BUSER_WIDTH(1),
    .C_M_AXI_OUTPUT_R_USER_VALUE(32'H00000000),
    .C_M_AXI_OUTPUT_R_PROT_VALUE(3'B000),
    .C_M_AXI_OUTPUT_R_CACHE_VALUE(4'B0011)
  ) inst (
    .s_axi_control_AWADDR(s_axi_control_AWADDR),
    .s_axi_control_AWVALID(s_axi_control_AWVALID),
    .s_axi_control_AWREADY(s_axi_control_AWREADY),
    .s_axi_control_WDATA(s_axi_control_WDATA),
    .s_axi_control_WSTRB(s_axi_control_WSTRB),
    .s_axi_control_WVALID(s_axi_control_WVALID),
    .s_axi_control_WREADY(s_axi_control_WREADY),
    .s_axi_control_BRESP(s_axi_control_BRESP),
    .s_axi_control_BVALID(s_axi_control_BVALID),
    .s_axi_control_BREADY(s_axi_control_BREADY),
    .s_axi_control_ARADDR(s_axi_control_ARADDR),
    .s_axi_control_ARVALID(s_axi_control_ARVALID),
    .s_axi_control_ARREADY(s_axi_control_ARREADY),
    .s_axi_control_RDATA(s_axi_control_RDATA),
    .s_axi_control_RRESP(s_axi_control_RRESP),
    .s_axi_control_RVALID(s_axi_control_RVALID),
    .s_axi_control_RREADY(s_axi_control_RREADY),
    .s_axi_conv_AWADDR(s_axi_conv_AWADDR),
    .s_axi_conv_AWVALID(s_axi_conv_AWVALID),
    .s_axi_conv_AWREADY(s_axi_conv_AWREADY),
    .s_axi_conv_WDATA(s_axi_conv_WDATA),
    .s_axi_conv_WSTRB(s_axi_conv_WSTRB),
    .s_axi_conv_WVALID(s_axi_conv_WVALID),
    .s_axi_conv_WREADY(s_axi_conv_WREADY),
    .s_axi_conv_BRESP(s_axi_conv_BRESP),
    .s_axi_conv_BVALID(s_axi_conv_BVALID),
    .s_axi_conv_BREADY(s_axi_conv_BREADY),
    .s_axi_conv_ARADDR(s_axi_conv_ARADDR),
    .s_axi_conv_ARVALID(s_axi_conv_ARVALID),
    .s_axi_conv_ARREADY(s_axi_conv_ARREADY),
    .s_axi_conv_RDATA(s_axi_conv_RDATA),
    .s_axi_conv_RRESP(s_axi_conv_RRESP),
    .s_axi_conv_RVALID(s_axi_conv_RVALID),
    .s_axi_conv_RREADY(s_axi_conv_RREADY),
    .ap_clk(ap_clk),
    .ap_rst_n(ap_rst_n),
    .interrupt(interrupt),
    .m_axi_input_r_AWID(m_axi_input_r_AWID),
    .m_axi_input_r_AWADDR(m_axi_input_r_AWADDR),
    .m_axi_input_r_AWLEN(m_axi_input_r_AWLEN),
    .m_axi_input_r_AWSIZE(m_axi_input_r_AWSIZE),
    .m_axi_input_r_AWBURST(m_axi_input_r_AWBURST),
    .m_axi_input_r_AWLOCK(m_axi_input_r_AWLOCK),
    .m_axi_input_r_AWREGION(m_axi_input_r_AWREGION),
    .m_axi_input_r_AWCACHE(m_axi_input_r_AWCACHE),
    .m_axi_input_r_AWPROT(m_axi_input_r_AWPROT),
    .m_axi_input_r_AWQOS(m_axi_input_r_AWQOS),
    .m_axi_input_r_AWUSER(),
    .m_axi_input_r_AWVALID(m_axi_input_r_AWVALID),
    .m_axi_input_r_AWREADY(m_axi_input_r_AWREADY),
    .m_axi_input_r_WID(m_axi_input_r_WID),
    .m_axi_input_r_WDATA(m_axi_input_r_WDATA),
    .m_axi_input_r_WSTRB(m_axi_input_r_WSTRB),
    .m_axi_input_r_WLAST(m_axi_input_r_WLAST),
    .m_axi_input_r_WUSER(),
    .m_axi_input_r_WVALID(m_axi_input_r_WVALID),
    .m_axi_input_r_WREADY(m_axi_input_r_WREADY),
    .m_axi_input_r_BID(m_axi_input_r_BID),
    .m_axi_input_r_BRESP(m_axi_input_r_BRESP),
    .m_axi_input_r_BUSER(1'B0),
    .m_axi_input_r_BVALID(m_axi_input_r_BVALID),
    .m_axi_input_r_BREADY(m_axi_input_r_BREADY),
    .m_axi_input_r_ARID(m_axi_input_r_ARID),
    .m_axi_input_r_ARADDR(m_axi_input_r_ARADDR),
    .m_axi_input_r_ARLEN(m_axi_input_r_ARLEN),
    .m_axi_input_r_ARSIZE(m_axi_input_r_ARSIZE),
    .m_axi_input_r_ARBURST(m_axi_input_r_ARBURST),
    .m_axi_input_r_ARLOCK(m_axi_input_r_ARLOCK),
    .m_axi_input_r_ARREGION(m_axi_input_r_ARREGION),
    .m_axi_input_r_ARCACHE(m_axi_input_r_ARCACHE),
    .m_axi_input_r_ARPROT(m_axi_input_r_ARPROT),
    .m_axi_input_r_ARQOS(m_axi_input_r_ARQOS),
    .m_axi_input_r_ARUSER(),
    .m_axi_input_r_ARVALID(m_axi_input_r_ARVALID),
    .m_axi_input_r_ARREADY(m_axi_input_r_ARREADY),
    .m_axi_input_r_RID(m_axi_input_r_RID),
    .m_axi_input_r_RDATA(m_axi_input_r_RDATA),
    .m_axi_input_r_RRESP(m_axi_input_r_RRESP),
    .m_axi_input_r_RLAST(m_axi_input_r_RLAST),
    .m_axi_input_r_RUSER(1'B0),
    .m_axi_input_r_RVALID(m_axi_input_r_RVALID),
    .m_axi_input_r_RREADY(m_axi_input_r_RREADY),
    .m_axi_output_r_AWID(m_axi_output_r_AWID),
    .m_axi_output_r_AWADDR(m_axi_output_r_AWADDR),
    .m_axi_output_r_AWLEN(m_axi_output_r_AWLEN),
    .m_axi_output_r_AWSIZE(m_axi_output_r_AWSIZE),
    .m_axi_output_r_AWBURST(m_axi_output_r_AWBURST),
    .m_axi_output_r_AWLOCK(m_axi_output_r_AWLOCK),
    .m_axi_output_r_AWREGION(m_axi_output_r_AWREGION),
    .m_axi_output_r_AWCACHE(m_axi_output_r_AWCACHE),
    .m_axi_output_r_AWPROT(m_axi_output_r_AWPROT),
    .m_axi_output_r_AWQOS(m_axi_output_r_AWQOS),
    .m_axi_output_r_AWUSER(),
    .m_axi_output_r_AWVALID(m_axi_output_r_AWVALID),
    .m_axi_output_r_AWREADY(m_axi_output_r_AWREADY),
    .m_axi_output_r_WID(m_axi_output_r_WID),
    .m_axi_output_r_WDATA(m_axi_output_r_WDATA),
    .m_axi_output_r_WSTRB(m_axi_output_r_WSTRB),
    .m_axi_output_r_WLAST(m_axi_output_r_WLAST),
    .m_axi_output_r_WUSER(),
    .m_axi_output_r_WVALID(m_axi_output_r_WVALID),
    .m_axi_output_r_WREADY(m_axi_output_r_WREADY),
    .m_axi_output_r_BID(m_axi_output_r_BID),
    .m_axi_output_r_BRESP(m_axi_output_r_BRESP),
    .m_axi_output_r_BUSER(1'B0),
    .m_axi_output_r_BVALID(m_axi_output_r_BVALID),
    .m_axi_output_r_BREADY(m_axi_output_r_BREADY),
    .m_axi_output_r_ARID(m_axi_output_r_ARID),
    .m_axi_output_r_ARADDR(m_axi_output_r_ARADDR),
    .m_axi_output_r_ARLEN(m_axi_output_r_ARLEN),
    .m_axi_output_r_ARSIZE(m_axi_output_r_ARSIZE),
    .m_axi_output_r_ARBURST(m_axi_output_r_ARBURST),
    .m_axi_output_r_ARLOCK(m_axi_output_r_ARLOCK),
    .m_axi_output_r_ARREGION(m_axi_output_r_ARREGION),
    .m_axi_output_r_ARCACHE(m_axi_output_r_ARCACHE),
    .m_axi_output_r_ARPROT(m_axi_output_r_ARPROT),
    .m_axi_output_r_ARQOS(m_axi_output_r_ARQOS),
    .m_axi_output_r_ARUSER(),
    .m_axi_output_r_ARVALID(m_axi_output_r_ARVALID),
    .m_axi_output_r_ARREADY(m_axi_output_r_ARREADY),
    .m_axi_output_r_RID(m_axi_output_r_RID),
    .m_axi_output_r_RDATA(m_axi_output_r_RDATA),
    .m_axi_output_r_RRESP(m_axi_output_r_RRESP),
    .m_axi_output_r_RLAST(m_axi_output_r_RLAST),
    .m_axi_output_r_RUSER(1'B0),
    .m_axi_output_r_RVALID(m_axi_output_r_RVALID),
    .m_axi_output_r_RREADY(m_axi_output_r_RREADY)
  );
endmodule
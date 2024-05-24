set moduleName applyConvolution_Pipeline_VITIS_LOOP_42_6
set isTopModule 0
set isCombinational 0
set isDatapathOnly 0
set isPipelined 1
set pipeline_type none
set FunctionProtocol ap_ctrl_hs
set isOneStateSeq 0
set ProfileFlag 0
set StallSigGenFlag 0
set isEnableWaveformDebug 1
set hasInterrupt 0
set DLRegFirstOffset 0
set DLRegItemOffset 0
set C_modelName {applyConvolution_Pipeline_VITIS_LOOP_42_6}
set C_modelType { void 0 }
set C_modelArgList {
	{ output_r int 8 regular {axi_master 1}  }
	{ input_r int 8 regular {axi_master 0}  }
	{ channels int 32 regular  }
	{ sum_0_5 float 32 regular  }
	{ sum_1_5 float 32 regular  }
	{ sum_2_5 float 32 regular  }
	{ output_r_offset int 64 regular  }
	{ add_ln26_1 int 64 regular  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "output_r", "interface" : "axi_master", "bitwidth" : 8, "direction" : "WRITEONLY", "bitSlice":[ {"cElement": [{"cName": "output_r_offset","offset": { "type": "dynamic","port_name": "output_r_offset"},"direction": "WRITEONLY"}]}]} , 
 	{ "Name" : "input_r", "interface" : "axi_master", "bitwidth" : 8, "direction" : "READONLY", "bitSlice":[ {"cElement": [{"cName": "image_r","offset": { "type": "dynamic","port_name": "image_r","bundle": "control"},"direction": "READONLY"}]}]} , 
 	{ "Name" : "channels", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_0_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_1_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_2_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "output_r_offset", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} , 
 	{ "Name" : "add_ln26_1", "interface" : "wire", "bitwidth" : 64, "direction" : "READONLY"} ]}
# RTL Port declarations: 
set portNum 104
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ m_axi_input_r_AWVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_AWREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_AWADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_input_r_AWID sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_AWLEN sc_out sc_lv 32 signal 1 } 
	{ m_axi_input_r_AWSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_input_r_AWBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_input_r_AWLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_input_r_AWCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_AWPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_input_r_AWQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_AWREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_AWUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_WVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_WREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_WDATA sc_out sc_lv 8 signal 1 } 
	{ m_axi_input_r_WSTRB sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_WLAST sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_WID sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_WUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_ARVALID sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_ARREADY sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_ARADDR sc_out sc_lv 64 signal 1 } 
	{ m_axi_input_r_ARID sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_ARLEN sc_out sc_lv 32 signal 1 } 
	{ m_axi_input_r_ARSIZE sc_out sc_lv 3 signal 1 } 
	{ m_axi_input_r_ARBURST sc_out sc_lv 2 signal 1 } 
	{ m_axi_input_r_ARLOCK sc_out sc_lv 2 signal 1 } 
	{ m_axi_input_r_ARCACHE sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_ARPROT sc_out sc_lv 3 signal 1 } 
	{ m_axi_input_r_ARQOS sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_ARREGION sc_out sc_lv 4 signal 1 } 
	{ m_axi_input_r_ARUSER sc_out sc_lv 1 signal 1 } 
	{ m_axi_input_r_RVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_RREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_RDATA sc_in sc_lv 8 signal 1 } 
	{ m_axi_input_r_RLAST sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_RID sc_in sc_lv 1 signal 1 } 
	{ m_axi_input_r_RFIFONUM sc_in sc_lv 11 signal 1 } 
	{ m_axi_input_r_RUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_input_r_RRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_input_r_BVALID sc_in sc_logic 1 signal 1 } 
	{ m_axi_input_r_BREADY sc_out sc_logic 1 signal 1 } 
	{ m_axi_input_r_BRESP sc_in sc_lv 2 signal 1 } 
	{ m_axi_input_r_BID sc_in sc_lv 1 signal 1 } 
	{ m_axi_input_r_BUSER sc_in sc_lv 1 signal 1 } 
	{ m_axi_output_r_AWVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_AWREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_AWADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_output_r_AWID sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_AWLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_output_r_AWSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_output_r_AWBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_output_r_AWLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_output_r_AWCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_AWPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_output_r_AWQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_AWREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_AWUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_WVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_WREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_WDATA sc_out sc_lv 8 signal 0 } 
	{ m_axi_output_r_WSTRB sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_WLAST sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_WID sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_WUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_ARVALID sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_ARREADY sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_ARADDR sc_out sc_lv 64 signal 0 } 
	{ m_axi_output_r_ARID sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_ARLEN sc_out sc_lv 32 signal 0 } 
	{ m_axi_output_r_ARSIZE sc_out sc_lv 3 signal 0 } 
	{ m_axi_output_r_ARBURST sc_out sc_lv 2 signal 0 } 
	{ m_axi_output_r_ARLOCK sc_out sc_lv 2 signal 0 } 
	{ m_axi_output_r_ARCACHE sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_ARPROT sc_out sc_lv 3 signal 0 } 
	{ m_axi_output_r_ARQOS sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_ARREGION sc_out sc_lv 4 signal 0 } 
	{ m_axi_output_r_ARUSER sc_out sc_lv 1 signal 0 } 
	{ m_axi_output_r_RVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_RREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_RDATA sc_in sc_lv 8 signal 0 } 
	{ m_axi_output_r_RLAST sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_RID sc_in sc_lv 1 signal 0 } 
	{ m_axi_output_r_RFIFONUM sc_in sc_lv 11 signal 0 } 
	{ m_axi_output_r_RUSER sc_in sc_lv 1 signal 0 } 
	{ m_axi_output_r_RRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_output_r_BVALID sc_in sc_logic 1 signal 0 } 
	{ m_axi_output_r_BREADY sc_out sc_logic 1 signal 0 } 
	{ m_axi_output_r_BRESP sc_in sc_lv 2 signal 0 } 
	{ m_axi_output_r_BID sc_in sc_lv 1 signal 0 } 
	{ m_axi_output_r_BUSER sc_in sc_lv 1 signal 0 } 
	{ channels sc_in sc_lv 32 signal 2 } 
	{ sum_0_5 sc_in sc_lv 32 signal 3 } 
	{ sum_1_5 sc_in sc_lv 32 signal 4 } 
	{ sum_2_5 sc_in sc_lv 32 signal 5 } 
	{ output_r_offset sc_in sc_lv 64 signal 6 } 
	{ add_ln26_1 sc_in sc_lv 64 signal 7 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "m_axi_input_r_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "AWVALID" }} , 
 	{ "name": "m_axi_input_r_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "AWREADY" }} , 
 	{ "name": "m_axi_input_r_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_r", "role": "AWADDR" }} , 
 	{ "name": "m_axi_input_r_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "AWID" }} , 
 	{ "name": "m_axi_input_r_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_r", "role": "AWLEN" }} , 
 	{ "name": "m_axi_input_r_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "input_r", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_input_r_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "AWBURST" }} , 
 	{ "name": "m_axi_input_r_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_input_r_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_input_r_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "input_r", "role": "AWPROT" }} , 
 	{ "name": "m_axi_input_r_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "AWQOS" }} , 
 	{ "name": "m_axi_input_r_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "AWREGION" }} , 
 	{ "name": "m_axi_input_r_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "AWUSER" }} , 
 	{ "name": "m_axi_input_r_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WVALID" }} , 
 	{ "name": "m_axi_input_r_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WREADY" }} , 
 	{ "name": "m_axi_input_r_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "input_r", "role": "WDATA" }} , 
 	{ "name": "m_axi_input_r_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WSTRB" }} , 
 	{ "name": "m_axi_input_r_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WLAST" }} , 
 	{ "name": "m_axi_input_r_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WID" }} , 
 	{ "name": "m_axi_input_r_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "WUSER" }} , 
 	{ "name": "m_axi_input_r_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "ARVALID" }} , 
 	{ "name": "m_axi_input_r_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "ARREADY" }} , 
 	{ "name": "m_axi_input_r_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "input_r", "role": "ARADDR" }} , 
 	{ "name": "m_axi_input_r_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "ARID" }} , 
 	{ "name": "m_axi_input_r_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "input_r", "role": "ARLEN" }} , 
 	{ "name": "m_axi_input_r_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "input_r", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_input_r_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "ARBURST" }} , 
 	{ "name": "m_axi_input_r_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_input_r_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_input_r_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "input_r", "role": "ARPROT" }} , 
 	{ "name": "m_axi_input_r_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "ARQOS" }} , 
 	{ "name": "m_axi_input_r_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "input_r", "role": "ARREGION" }} , 
 	{ "name": "m_axi_input_r_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "ARUSER" }} , 
 	{ "name": "m_axi_input_r_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "RVALID" }} , 
 	{ "name": "m_axi_input_r_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "RREADY" }} , 
 	{ "name": "m_axi_input_r_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "input_r", "role": "RDATA" }} , 
 	{ "name": "m_axi_input_r_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "RLAST" }} , 
 	{ "name": "m_axi_input_r_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "RID" }} , 
 	{ "name": "m_axi_input_r_RFIFONUM", "direction": "in", "datatype": "sc_lv", "bitwidth":11, "type": "signal", "bundle":{"name": "input_r", "role": "RFIFONUM" }} , 
 	{ "name": "m_axi_input_r_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "RUSER" }} , 
 	{ "name": "m_axi_input_r_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "RRESP" }} , 
 	{ "name": "m_axi_input_r_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "BVALID" }} , 
 	{ "name": "m_axi_input_r_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "BREADY" }} , 
 	{ "name": "m_axi_input_r_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "input_r", "role": "BRESP" }} , 
 	{ "name": "m_axi_input_r_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "BID" }} , 
 	{ "name": "m_axi_input_r_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "input_r", "role": "BUSER" }} , 
 	{ "name": "m_axi_output_r_AWVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "AWVALID" }} , 
 	{ "name": "m_axi_output_r_AWREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "AWREADY" }} , 
 	{ "name": "m_axi_output_r_AWADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "output_r", "role": "AWADDR" }} , 
 	{ "name": "m_axi_output_r_AWID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "AWID" }} , 
 	{ "name": "m_axi_output_r_AWLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_r", "role": "AWLEN" }} , 
 	{ "name": "m_axi_output_r_AWSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "output_r", "role": "AWSIZE" }} , 
 	{ "name": "m_axi_output_r_AWBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "AWBURST" }} , 
 	{ "name": "m_axi_output_r_AWLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "AWLOCK" }} , 
 	{ "name": "m_axi_output_r_AWCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "AWCACHE" }} , 
 	{ "name": "m_axi_output_r_AWPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "output_r", "role": "AWPROT" }} , 
 	{ "name": "m_axi_output_r_AWQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "AWQOS" }} , 
 	{ "name": "m_axi_output_r_AWREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "AWREGION" }} , 
 	{ "name": "m_axi_output_r_AWUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "AWUSER" }} , 
 	{ "name": "m_axi_output_r_WVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WVALID" }} , 
 	{ "name": "m_axi_output_r_WREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WREADY" }} , 
 	{ "name": "m_axi_output_r_WDATA", "direction": "out", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "output_r", "role": "WDATA" }} , 
 	{ "name": "m_axi_output_r_WSTRB", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WSTRB" }} , 
 	{ "name": "m_axi_output_r_WLAST", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WLAST" }} , 
 	{ "name": "m_axi_output_r_WID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WID" }} , 
 	{ "name": "m_axi_output_r_WUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "WUSER" }} , 
 	{ "name": "m_axi_output_r_ARVALID", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "ARVALID" }} , 
 	{ "name": "m_axi_output_r_ARREADY", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "ARREADY" }} , 
 	{ "name": "m_axi_output_r_ARADDR", "direction": "out", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "output_r", "role": "ARADDR" }} , 
 	{ "name": "m_axi_output_r_ARID", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "ARID" }} , 
 	{ "name": "m_axi_output_r_ARLEN", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "output_r", "role": "ARLEN" }} , 
 	{ "name": "m_axi_output_r_ARSIZE", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "output_r", "role": "ARSIZE" }} , 
 	{ "name": "m_axi_output_r_ARBURST", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "ARBURST" }} , 
 	{ "name": "m_axi_output_r_ARLOCK", "direction": "out", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "ARLOCK" }} , 
 	{ "name": "m_axi_output_r_ARCACHE", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "ARCACHE" }} , 
 	{ "name": "m_axi_output_r_ARPROT", "direction": "out", "datatype": "sc_lv", "bitwidth":3, "type": "signal", "bundle":{"name": "output_r", "role": "ARPROT" }} , 
 	{ "name": "m_axi_output_r_ARQOS", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "ARQOS" }} , 
 	{ "name": "m_axi_output_r_ARREGION", "direction": "out", "datatype": "sc_lv", "bitwidth":4, "type": "signal", "bundle":{"name": "output_r", "role": "ARREGION" }} , 
 	{ "name": "m_axi_output_r_ARUSER", "direction": "out", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "ARUSER" }} , 
 	{ "name": "m_axi_output_r_RVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "RVALID" }} , 
 	{ "name": "m_axi_output_r_RREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "RREADY" }} , 
 	{ "name": "m_axi_output_r_RDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":8, "type": "signal", "bundle":{"name": "output_r", "role": "RDATA" }} , 
 	{ "name": "m_axi_output_r_RLAST", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "RLAST" }} , 
 	{ "name": "m_axi_output_r_RID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "RID" }} , 
 	{ "name": "m_axi_output_r_RFIFONUM", "direction": "in", "datatype": "sc_lv", "bitwidth":11, "type": "signal", "bundle":{"name": "output_r", "role": "RFIFONUM" }} , 
 	{ "name": "m_axi_output_r_RUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "RUSER" }} , 
 	{ "name": "m_axi_output_r_RRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "RRESP" }} , 
 	{ "name": "m_axi_output_r_BVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "BVALID" }} , 
 	{ "name": "m_axi_output_r_BREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "BREADY" }} , 
 	{ "name": "m_axi_output_r_BRESP", "direction": "in", "datatype": "sc_lv", "bitwidth":2, "type": "signal", "bundle":{"name": "output_r", "role": "BRESP" }} , 
 	{ "name": "m_axi_output_r_BID", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "BID" }} , 
 	{ "name": "m_axi_output_r_BUSER", "direction": "in", "datatype": "sc_lv", "bitwidth":1, "type": "signal", "bundle":{"name": "output_r", "role": "BUSER" }} , 
 	{ "name": "channels", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "channels", "role": "default" }} , 
 	{ "name": "sum_0_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_0_5", "role": "default" }} , 
 	{ "name": "sum_1_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_1_5", "role": "default" }} , 
 	{ "name": "sum_2_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_2_5", "role": "default" }} , 
 	{ "name": "output_r_offset", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "output_r_offset", "role": "default" }} , 
 	{ "name": "add_ln26_1", "direction": "in", "datatype": "sc_lv", "bitwidth":64, "type": "signal", "bundle":{"name": "add_ln26_1", "role": "default" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2"],
		"CDFG" : "applyConvolution_Pipeline_VITIS_LOOP_42_6",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "-1", "EstimateLatencyMax" : "-1",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "output_r", "Type" : "MAXI", "Direction" : "O",
				"BlockSignal" : [
					{"Name" : "output_r_blk_n_W", "Type" : "RtlSignal"}]},
			{"Name" : "input_r", "Type" : "MAXI", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "input_r_blk_n_R", "Type" : "RtlSignal"}]},
			{"Name" : "channels", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_0_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_1_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_2_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "output_r_offset", "Type" : "None", "Direction" : "I"},
			{"Name" : "add_ln26_1", "Type" : "None", "Direction" : "I"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_42_6", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage0", "LastStateIter" : "ap_enable_reg_pp0_iter4", "LastStateBlock" : "ap_block_pp0_stage0_subdone", "QuitState" : "ap_ST_fsm_pp0_stage0", "QuitStateIter" : "ap_enable_reg_pp0_iter4", "QuitStateBlock" : "ap_block_pp0_stage0_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mux_3_2_32_1_1_U25", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	applyConvolution_Pipeline_VITIS_LOOP_42_6 {
		output_r {Type O LastRead -1 FirstWrite 4}
		input_r {Type I LastRead 2 FirstWrite -1}
		channels {Type I LastRead 0 FirstWrite -1}
		sum_0_5 {Type I LastRead 0 FirstWrite -1}
		sum_1_5 {Type I LastRead 0 FirstWrite -1}
		sum_2_5 {Type I LastRead 0 FirstWrite -1}
		output_r_offset {Type I LastRead 0 FirstWrite -1}
		add_ln26_1 {Type I LastRead 0 FirstWrite -1}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	 { m_axi {  { m_axi_output_r_AWVALID VALID 1 1 }  { m_axi_output_r_AWREADY READY 0 1 }  { m_axi_output_r_AWADDR ADDR 1 64 }  { m_axi_output_r_AWID ID 1 1 }  { m_axi_output_r_AWLEN SIZE 1 32 }  { m_axi_output_r_AWSIZE BURST 1 3 }  { m_axi_output_r_AWBURST LOCK 1 2 }  { m_axi_output_r_AWLOCK CACHE 1 2 }  { m_axi_output_r_AWCACHE PROT 1 4 }  { m_axi_output_r_AWPROT QOS 1 3 }  { m_axi_output_r_AWQOS REGION 1 4 }  { m_axi_output_r_AWREGION USER 1 4 }  { m_axi_output_r_AWUSER DATA 1 1 }  { m_axi_output_r_WVALID VALID 1 1 }  { m_axi_output_r_WREADY READY 0 1 }  { m_axi_output_r_WDATA FIFONUM 1 8 }  { m_axi_output_r_WSTRB STRB 1 1 }  { m_axi_output_r_WLAST LAST 1 1 }  { m_axi_output_r_WID ID 1 1 }  { m_axi_output_r_WUSER DATA 1 1 }  { m_axi_output_r_ARVALID VALID 1 1 }  { m_axi_output_r_ARREADY READY 0 1 }  { m_axi_output_r_ARADDR ADDR 1 64 }  { m_axi_output_r_ARID ID 1 1 }  { m_axi_output_r_ARLEN SIZE 1 32 }  { m_axi_output_r_ARSIZE BURST 1 3 }  { m_axi_output_r_ARBURST LOCK 1 2 }  { m_axi_output_r_ARLOCK CACHE 1 2 }  { m_axi_output_r_ARCACHE PROT 1 4 }  { m_axi_output_r_ARPROT QOS 1 3 }  { m_axi_output_r_ARQOS REGION 1 4 }  { m_axi_output_r_ARREGION USER 1 4 }  { m_axi_output_r_ARUSER DATA 1 1 }  { m_axi_output_r_RVALID VALID 0 1 }  { m_axi_output_r_RREADY READY 1 1 }  { m_axi_output_r_RDATA FIFONUM 0 8 }  { m_axi_output_r_RLAST LAST 0 1 }  { m_axi_output_r_RID ID 0 1 }  { m_axi_output_r_RFIFONUM LEN 0 11 }  { m_axi_output_r_RUSER DATA 0 1 }  { m_axi_output_r_RRESP RESP 0 2 }  { m_axi_output_r_BVALID VALID 0 1 }  { m_axi_output_r_BREADY READY 1 1 }  { m_axi_output_r_BRESP RESP 0 2 }  { m_axi_output_r_BID ID 0 1 }  { m_axi_output_r_BUSER DATA 0 1 } } }
	 { m_axi {  { m_axi_input_r_AWVALID VALID 1 1 }  { m_axi_input_r_AWREADY READY 0 1 }  { m_axi_input_r_AWADDR ADDR 1 64 }  { m_axi_input_r_AWID ID 1 1 }  { m_axi_input_r_AWLEN SIZE 1 32 }  { m_axi_input_r_AWSIZE BURST 1 3 }  { m_axi_input_r_AWBURST LOCK 1 2 }  { m_axi_input_r_AWLOCK CACHE 1 2 }  { m_axi_input_r_AWCACHE PROT 1 4 }  { m_axi_input_r_AWPROT QOS 1 3 }  { m_axi_input_r_AWQOS REGION 1 4 }  { m_axi_input_r_AWREGION USER 1 4 }  { m_axi_input_r_AWUSER DATA 1 1 }  { m_axi_input_r_WVALID VALID 1 1 }  { m_axi_input_r_WREADY READY 0 1 }  { m_axi_input_r_WDATA FIFONUM 1 8 }  { m_axi_input_r_WSTRB STRB 1 1 }  { m_axi_input_r_WLAST LAST 1 1 }  { m_axi_input_r_WID ID 1 1 }  { m_axi_input_r_WUSER DATA 1 1 }  { m_axi_input_r_ARVALID VALID 1 1 }  { m_axi_input_r_ARREADY READY 0 1 }  { m_axi_input_r_ARADDR ADDR 1 64 }  { m_axi_input_r_ARID ID 1 1 }  { m_axi_input_r_ARLEN SIZE 1 32 }  { m_axi_input_r_ARSIZE BURST 1 3 }  { m_axi_input_r_ARBURST LOCK 1 2 }  { m_axi_input_r_ARLOCK CACHE 1 2 }  { m_axi_input_r_ARCACHE PROT 1 4 }  { m_axi_input_r_ARPROT QOS 1 3 }  { m_axi_input_r_ARQOS REGION 1 4 }  { m_axi_input_r_ARREGION USER 1 4 }  { m_axi_input_r_ARUSER DATA 1 1 }  { m_axi_input_r_RVALID VALID 0 1 }  { m_axi_input_r_RREADY READY 1 1 }  { m_axi_input_r_RDATA FIFONUM 0 8 }  { m_axi_input_r_RLAST LAST 0 1 }  { m_axi_input_r_RID ID 0 1 }  { m_axi_input_r_RFIFONUM LEN 0 11 }  { m_axi_input_r_RUSER DATA 0 1 }  { m_axi_input_r_RRESP RESP 0 2 }  { m_axi_input_r_BVALID VALID 0 1 }  { m_axi_input_r_BREADY READY 1 1 }  { m_axi_input_r_BRESP RESP 0 2 }  { m_axi_input_r_BID ID 0 1 }  { m_axi_input_r_BUSER DATA 0 1 } } }
	channels { ap_none {  { channels in_data 0 32 } } }
	sum_0_5 { ap_none {  { sum_0_5 in_data 0 32 } } }
	sum_1_5 { ap_none {  { sum_1_5 in_data 0 32 } } }
	sum_2_5 { ap_none {  { sum_2_5 in_data 0 32 } } }
	output_r_offset { ap_none {  { output_r_offset in_data 0 64 } } }
	add_ln26_1 { ap_none {  { add_ln26_1 in_data 0 64 } } }
}

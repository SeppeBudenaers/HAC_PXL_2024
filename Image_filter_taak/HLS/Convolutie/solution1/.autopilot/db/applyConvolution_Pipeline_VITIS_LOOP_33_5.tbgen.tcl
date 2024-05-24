set moduleName applyConvolution_Pipeline_VITIS_LOOP_33_5
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
set C_modelName {applyConvolution_Pipeline_VITIS_LOOP_33_5}
set C_modelType { void 0 }
set C_modelArgList {
	{ sum_2_5 float 32 regular  }
	{ sum_1_5 float 32 regular  }
	{ sum_0_5 float 32 regular  }
	{ channels int 32 regular  }
	{ image_r int 32 regular {axi_s 0 volatile  { image_r Data } }  }
	{ kernel_load float 32 regular  }
	{ sum_2_6_out float 32 regular {pointer 1}  }
	{ sum_1_6_out float 32 regular {pointer 1}  }
	{ sum_0_6_out float 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "sum_2_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_1_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_0_5", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "channels", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "image_r", "interface" : "axis", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "kernel_load", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_2_6_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "sum_1_6_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "sum_0_6_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 20
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ sum_2_5 sc_in sc_lv 32 signal 0 } 
	{ sum_1_5 sc_in sc_lv 32 signal 1 } 
	{ sum_0_5 sc_in sc_lv 32 signal 2 } 
	{ channels sc_in sc_lv 32 signal 3 } 
	{ image_r_TDATA sc_in sc_lv 32 signal 4 } 
	{ image_r_TVALID sc_in sc_logic 1 invld 4 } 
	{ image_r_TREADY sc_out sc_logic 1 inacc 4 } 
	{ kernel_load sc_in sc_lv 32 signal 5 } 
	{ sum_2_6_out sc_out sc_lv 32 signal 6 } 
	{ sum_2_6_out_ap_vld sc_out sc_logic 1 outvld 6 } 
	{ sum_1_6_out sc_out sc_lv 32 signal 7 } 
	{ sum_1_6_out_ap_vld sc_out sc_logic 1 outvld 7 } 
	{ sum_0_6_out sc_out sc_lv 32 signal 8 } 
	{ sum_0_6_out_ap_vld sc_out sc_logic 1 outvld 8 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "sum_2_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_2_5", "role": "default" }} , 
 	{ "name": "sum_1_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_1_5", "role": "default" }} , 
 	{ "name": "sum_0_5", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_0_5", "role": "default" }} , 
 	{ "name": "channels", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "channels", "role": "default" }} , 
 	{ "name": "image_r_TDATA", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "image_r", "role": "TDATA" }} , 
 	{ "name": "image_r_TVALID", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "invld", "bundle":{"name": "image_r", "role": "TVALID" }} , 
 	{ "name": "image_r_TREADY", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "inacc", "bundle":{"name": "image_r", "role": "TREADY" }} , 
 	{ "name": "kernel_load", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "kernel_load", "role": "default" }} , 
 	{ "name": "sum_2_6_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_2_6_out", "role": "default" }} , 
 	{ "name": "sum_2_6_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_2_6_out", "role": "ap_vld" }} , 
 	{ "name": "sum_1_6_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_1_6_out", "role": "default" }} , 
 	{ "name": "sum_1_6_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_1_6_out", "role": "ap_vld" }} , 
 	{ "name": "sum_0_6_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_0_6_out", "role": "default" }} , 
 	{ "name": "sum_0_6_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_0_6_out", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1", "2", "3", "4", "5"],
		"CDFG" : "applyConvolution_Pipeline_VITIS_LOOP_33_5",
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
			{"Name" : "sum_2_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_1_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_0_5", "Type" : "None", "Direction" : "I"},
			{"Name" : "channels", "Type" : "None", "Direction" : "I"},
			{"Name" : "image_r", "Type" : "Axis", "Direction" : "I",
				"BlockSignal" : [
					{"Name" : "image_r_TDATA_blk_n", "Type" : "RtlSignal"}]},
			{"Name" : "kernel_load", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_2_6_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "sum_1_6_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "sum_0_6_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "VITIS_LOOP_33_5", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "9", "FirstState" : "ap_ST_fsm_pp0_stage0", "FirstStateIter" : "ap_enable_reg_pp0_iter0", "FirstStateBlock" : "ap_block_pp0_stage0_subdone", "LastState" : "ap_ST_fsm_pp0_stage3", "LastStateIter" : "ap_enable_reg_pp0_iter2", "LastStateBlock" : "ap_block_pp0_stage3_subdone", "QuitState" : "ap_ST_fsm_pp0_stage3", "QuitStateIter" : "ap_enable_reg_pp0_iter2", "QuitStateBlock" : "ap_block_pp0_stage3_subdone", "OneDepthLoop" : "0", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fadd_32ns_32ns_32_8_full_dsp_1_U7", "Parent" : "0"},
	{"ID" : "2", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.fmul_32ns_32ns_32_4_max_dsp_1_U8", "Parent" : "0"},
	{"ID" : "3", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.sitofp_32ns_32_7_no_dsp_1_U9", "Parent" : "0"},
	{"ID" : "4", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.mux_3_2_32_1_1_U10", "Parent" : "0"},
	{"ID" : "5", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	applyConvolution_Pipeline_VITIS_LOOP_33_5 {
		sum_2_5 {Type I LastRead 0 FirstWrite -1}
		sum_1_5 {Type I LastRead 0 FirstWrite -1}
		sum_0_5 {Type I LastRead 0 FirstWrite -1}
		channels {Type I LastRead 0 FirstWrite -1}
		image_r {Type I LastRead 1 FirstWrite -1}
		kernel_load {Type I LastRead 0 FirstWrite -1}
		sum_2_6_out {Type O LastRead -1 FirstWrite 12}
		sum_1_6_out {Type O LastRead -1 FirstWrite 12}
		sum_0_6_out {Type O LastRead -1 FirstWrite 12}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "-1", "Max" : "-1"}
	, {"Name" : "Interval", "Min" : "-1", "Max" : "-1"}
]}

set PipelineEnableSignalInfo {[
	{"Pipeline" : "0", "EnableSignal" : "ap_enable_pp0"}
]}

set Spec2ImplPortList { 
	sum_2_5 { ap_none {  { sum_2_5 in_data 0 32 } } }
	sum_1_5 { ap_none {  { sum_1_5 in_data 0 32 } } }
	sum_0_5 { ap_none {  { sum_0_5 in_data 0 32 } } }
	channels { ap_none {  { channels in_data 0 32 } } }
	image_r { axis {  { image_r_TDATA in_data 0 32 }  { image_r_TVALID in_vld 0 1 }  { image_r_TREADY in_acc 1 1 } } }
	kernel_load { ap_none {  { kernel_load in_data 0 32 } } }
	sum_2_6_out { ap_vld {  { sum_2_6_out out_data 1 32 }  { sum_2_6_out_ap_vld out_vld 1 1 } } }
	sum_1_6_out { ap_vld {  { sum_1_6_out out_data 1 32 }  { sum_1_6_out_ap_vld out_vld 1 1 } } }
	sum_0_6_out { ap_vld {  { sum_0_6_out out_data 1 32 }  { sum_0_6_out_ap_vld out_vld 1 1 } } }
}

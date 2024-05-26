set moduleName applyConvolution_Pipeline_1
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
set C_modelName {applyConvolution_Pipeline_1}
set C_modelType { void 0 }
set C_modelArgList {
	{ sum_2_1 float 32 regular  }
	{ sum_1_1 float 32 regular  }
	{ sum_0_1 float 32 regular  }
	{ sum_2_2_out float 32 regular {pointer 1}  }
	{ sum_1_2_out float 32 regular {pointer 1}  }
	{ sum_0_21_out float 32 regular {pointer 1}  }
}
set hasAXIMCache 0
set AXIMCacheInstList { }
set C_modelArgMapList {[ 
	{ "Name" : "sum_2_1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_1_1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_0_1", "interface" : "wire", "bitwidth" : 32, "direction" : "READONLY"} , 
 	{ "Name" : "sum_2_2_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "sum_1_2_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} , 
 	{ "Name" : "sum_0_21_out", "interface" : "wire", "bitwidth" : 32, "direction" : "WRITEONLY"} ]}
# RTL Port declarations: 
set portNum 15
set portList { 
	{ ap_clk sc_in sc_logic 1 clock -1 } 
	{ ap_rst sc_in sc_logic 1 reset -1 active_high_sync } 
	{ ap_start sc_in sc_logic 1 start -1 } 
	{ ap_done sc_out sc_logic 1 predone -1 } 
	{ ap_idle sc_out sc_logic 1 done -1 } 
	{ ap_ready sc_out sc_logic 1 ready -1 } 
	{ sum_2_1 sc_in sc_lv 32 signal 0 } 
	{ sum_1_1 sc_in sc_lv 32 signal 1 } 
	{ sum_0_1 sc_in sc_lv 32 signal 2 } 
	{ sum_2_2_out sc_out sc_lv 32 signal 3 } 
	{ sum_2_2_out_ap_vld sc_out sc_logic 1 outvld 3 } 
	{ sum_1_2_out sc_out sc_lv 32 signal 4 } 
	{ sum_1_2_out_ap_vld sc_out sc_logic 1 outvld 4 } 
	{ sum_0_21_out sc_out sc_lv 32 signal 5 } 
	{ sum_0_21_out_ap_vld sc_out sc_logic 1 outvld 5 } 
}
set NewPortList {[ 
	{ "name": "ap_clk", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "clock", "bundle":{"name": "ap_clk", "role": "default" }} , 
 	{ "name": "ap_rst", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "reset", "bundle":{"name": "ap_rst", "role": "default" }} , 
 	{ "name": "ap_start", "direction": "in", "datatype": "sc_logic", "bitwidth":1, "type": "start", "bundle":{"name": "ap_start", "role": "default" }} , 
 	{ "name": "ap_done", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "predone", "bundle":{"name": "ap_done", "role": "default" }} , 
 	{ "name": "ap_idle", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "done", "bundle":{"name": "ap_idle", "role": "default" }} , 
 	{ "name": "ap_ready", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "ready", "bundle":{"name": "ap_ready", "role": "default" }} , 
 	{ "name": "sum_2_1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_2_1", "role": "default" }} , 
 	{ "name": "sum_1_1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_1_1", "role": "default" }} , 
 	{ "name": "sum_0_1", "direction": "in", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_0_1", "role": "default" }} , 
 	{ "name": "sum_2_2_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_2_2_out", "role": "default" }} , 
 	{ "name": "sum_2_2_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_2_2_out", "role": "ap_vld" }} , 
 	{ "name": "sum_1_2_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_1_2_out", "role": "default" }} , 
 	{ "name": "sum_1_2_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_1_2_out", "role": "ap_vld" }} , 
 	{ "name": "sum_0_21_out", "direction": "out", "datatype": "sc_lv", "bitwidth":32, "type": "signal", "bundle":{"name": "sum_0_21_out", "role": "default" }} , 
 	{ "name": "sum_0_21_out_ap_vld", "direction": "out", "datatype": "sc_logic", "bitwidth":1, "type": "outvld", "bundle":{"name": "sum_0_21_out", "role": "ap_vld" }}  ]}

set RtlHierarchyInfo {[
	{"ID" : "0", "Level" : "0", "Path" : "`AUTOTB_DUT_INST", "Parent" : "", "Child" : ["1"],
		"CDFG" : "applyConvolution_Pipeline_1",
		"Protocol" : "ap_ctrl_hs",
		"ControlExist" : "1", "ap_start" : "1", "ap_ready" : "1", "ap_done" : "1", "ap_continue" : "0", "ap_idle" : "1", "real_start" : "0",
		"Pipeline" : "None", "UnalignedPipeline" : "0", "RewindPipeline" : "0", "ProcessNetwork" : "0",
		"II" : "0",
		"VariableLatency" : "1", "ExactLatency" : "-1", "EstimateLatencyMin" : "5", "EstimateLatencyMax" : "5",
		"Combinational" : "0",
		"Datapath" : "0",
		"ClockEnable" : "0",
		"HasSubDataflow" : "0",
		"InDataflowNetwork" : "0",
		"HasNonBlockingOperation" : "0",
		"IsBlackBox" : "0",
		"Port" : [
			{"Name" : "sum_2_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_1_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_0_1", "Type" : "None", "Direction" : "I"},
			{"Name" : "sum_2_2_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "sum_1_2_out", "Type" : "Vld", "Direction" : "O"},
			{"Name" : "sum_0_21_out", "Type" : "Vld", "Direction" : "O"}],
		"Loop" : [
			{"Name" : "Loop 1", "PipelineType" : "UPC",
				"LoopDec" : {"FSMBitwidth" : "1", "FirstState" : "ap_ST_fsm_state1", "FirstStateIter" : "", "FirstStateBlock" : "ap_ST_fsm_state1_blk", "LastState" : "ap_ST_fsm_state1", "LastStateIter" : "", "LastStateBlock" : "ap_ST_fsm_state1_blk", "QuitState" : "ap_ST_fsm_state1", "QuitStateIter" : "", "QuitStateBlock" : "ap_ST_fsm_state1_blk", "OneDepthLoop" : "1", "has_ap_ctrl" : "1", "has_continue" : "0"}}]},
	{"ID" : "1", "Level" : "1", "Path" : "`AUTOTB_DUT_INST.flow_control_loop_pipe_sequential_init_U", "Parent" : "0"}]}


set ArgLastReadFirstWriteLatency {
	applyConvolution_Pipeline_1 {
		sum_2_1 {Type I LastRead 0 FirstWrite -1}
		sum_1_1 {Type I LastRead 0 FirstWrite -1}
		sum_0_1 {Type I LastRead 0 FirstWrite -1}
		sum_2_2_out {Type O LastRead -1 FirstWrite 0}
		sum_1_2_out {Type O LastRead -1 FirstWrite 0}
		sum_0_21_out {Type O LastRead -1 FirstWrite 0}}}

set hasDtUnsupportedChannel 0

set PerformanceInfo {[
	{"Name" : "Latency", "Min" : "5", "Max" : "5"}
	, {"Name" : "Interval", "Min" : "5", "Max" : "5"}
]}

set PipelineEnableSignalInfo {[
]}

set Spec2ImplPortList { 
	sum_2_1 { ap_none {  { sum_2_1 in_data 0 32 } } }
	sum_1_1 { ap_none {  { sum_1_1 in_data 0 32 } } }
	sum_0_1 { ap_none {  { sum_0_1 in_data 0 32 } } }
	sum_2_2_out { ap_vld {  { sum_2_2_out out_data 1 32 }  { sum_2_2_out_ap_vld out_vld 1 1 } } }
	sum_1_2_out { ap_vld {  { sum_1_2_out out_data 1 32 }  { sum_1_2_out_ap_vld out_vld 1 1 } } }
	sum_0_21_out { ap_vld {  { sum_0_21_out out_data 1 32 }  { sum_0_21_out_ap_vld out_vld 1 1 } } }
}
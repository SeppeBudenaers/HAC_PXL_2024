set ModuleHierarchy {[{
"Name" : "applyConvolution","ID" : "0","Type" : "sequential",
"SubLoops" : [
	{"Name" : "VITIS_LOOP_24_1_VITIS_LOOP_25_2","ID" : "1","Type" : "no",
	"SubInsts" : [
	{"Name" : "grp_applyConvolution_Pipeline_1_fu_275","ID" : "2","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "Loop 1","ID" : "3","Type" : "pipeline"},]},
	{"Name" : "grp_applyConvolution_Pipeline_VITIS_LOOP_41_6_fu_303","ID" : "4","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "VITIS_LOOP_41_6","ID" : "5","Type" : "pipeline"},]},],
	"SubLoops" : [
	{"Name" : "VITIS_LOOP_27_3_VITIS_LOOP_28_4","ID" : "6","Type" : "no",
		"SubInsts" : [
		{"Name" : "grp_applyConvolution_Pipeline_VITIS_LOOP_33_5_fu_285","ID" : "7","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_33_5","ID" : "8","Type" : "pipeline"},]},]},]},]
}]}
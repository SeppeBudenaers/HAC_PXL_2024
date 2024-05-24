set ModuleHierarchy {[{
"Name" : "applyConvolution","ID" : "0","Type" : "sequential",
"SubLoops" : [
	{"Name" : "VITIS_LOOP_25_1_VITIS_LOOP_26_2","ID" : "1","Type" : "no",
	"SubInsts" : [
	{"Name" : "grp_applyConvolution_Pipeline_1_fu_365","ID" : "2","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "Loop 1","ID" : "3","Type" : "pipeline"},]},
	{"Name" : "grp_applyConvolution_Pipeline_VITIS_LOOP_42_6_fu_394","ID" : "4","Type" : "sequential",
			"SubLoops" : [
			{"Name" : "VITIS_LOOP_42_6","ID" : "5","Type" : "pipeline"},]},],
	"SubLoops" : [
	{"Name" : "VITIS_LOOP_28_3_VITIS_LOOP_29_4","ID" : "6","Type" : "no",
		"SubInsts" : [
		{"Name" : "grp_applyConvolution_Pipeline_VITIS_LOOP_34_5_fu_375","ID" : "7","Type" : "sequential",
				"SubLoops" : [
				{"Name" : "VITIS_LOOP_34_5","ID" : "8","Type" : "pipeline"},]},]},]},]
}]}
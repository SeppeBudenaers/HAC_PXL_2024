// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef __linux__

#include "xstatus.h"
#ifdef SDT
#include "xparameters.h"
#endif
#include "xapplyconvolution.h"

extern XApplyconvolution_Config XApplyconvolution_ConfigTable[];

#ifdef SDT
XApplyconvolution_Config *XApplyconvolution_LookupConfig(UINTPTR BaseAddress) {
	XApplyconvolution_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XApplyconvolution_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XApplyconvolution_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XApplyconvolution_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XApplyconvolution_Initialize(XApplyconvolution *InstancePtr, UINTPTR BaseAddress) {
	XApplyconvolution_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XApplyconvolution_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XApplyconvolution_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XApplyconvolution_Config *XApplyconvolution_LookupConfig(u16 DeviceId) {
	XApplyconvolution_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XAPPLYCONVOLUTION_NUM_INSTANCES; Index++) {
		if (XApplyconvolution_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XApplyconvolution_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XApplyconvolution_Initialize(XApplyconvolution *InstancePtr, u16 DeviceId) {
	XApplyconvolution_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XApplyconvolution_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XApplyconvolution_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif


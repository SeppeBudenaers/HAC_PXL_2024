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
#include "ximagetransform.h"

extern XImagetransform_Config XImagetransform_ConfigTable[];

#ifdef SDT
XImagetransform_Config *XImagetransform_LookupConfig(UINTPTR BaseAddress) {
	XImagetransform_Config *ConfigPtr = NULL;

	int Index;

	for (Index = (u32)0x0; XImagetransform_ConfigTable[Index].Name != NULL; Index++) {
		if (!BaseAddress || XImagetransform_ConfigTable[Index].Control_BaseAddress == BaseAddress) {
			ConfigPtr = &XImagetransform_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XImagetransform_Initialize(XImagetransform *InstancePtr, UINTPTR BaseAddress) {
	XImagetransform_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XImagetransform_LookupConfig(BaseAddress);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XImagetransform_CfgInitialize(InstancePtr, ConfigPtr);
}
#else
XImagetransform_Config *XImagetransform_LookupConfig(u16 DeviceId) {
	XImagetransform_Config *ConfigPtr = NULL;

	int Index;

	for (Index = 0; Index < XPAR_XIMAGETRANSFORM_NUM_INSTANCES; Index++) {
		if (XImagetransform_ConfigTable[Index].DeviceId == DeviceId) {
			ConfigPtr = &XImagetransform_ConfigTable[Index];
			break;
		}
	}

	return ConfigPtr;
}

int XImagetransform_Initialize(XImagetransform *InstancePtr, u16 DeviceId) {
	XImagetransform_Config *ConfigPtr;

	Xil_AssertNonvoid(InstancePtr != NULL);

	ConfigPtr = XImagetransform_LookupConfig(DeviceId);
	if (ConfigPtr == NULL) {
		InstancePtr->IsReady = 0;
		return (XST_DEVICE_NOT_FOUND);
	}

	return XImagetransform_CfgInitialize(InstancePtr, ConfigPtr);
}
#endif

#endif


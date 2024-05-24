// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "xapplyconvolution.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XApplyconvolution_CfgInitialize(XApplyconvolution *InstancePtr, XApplyconvolution_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->Conv_BaseAddress = ConfigPtr->Conv_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XApplyconvolution_Start(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL) & 0x80;
    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XApplyconvolution_IsDone(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XApplyconvolution_IsIdle(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XApplyconvolution_IsReady(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XApplyconvolution_EnableAutoRestart(XApplyconvolution *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XApplyconvolution_DisableAutoRestart(XApplyconvolution *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_AP_CTRL, 0);
}

void XApplyconvolution_Set_image_r(XApplyconvolution *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IMAGE_R_DATA, (u32)(Data));
    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IMAGE_R_DATA + 4, (u32)(Data >> 32));
}

u64 XApplyconvolution_Get_image_r(XApplyconvolution *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IMAGE_R_DATA);
    Data += (u64)XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IMAGE_R_DATA + 4) << 32;
    return Data;
}

void XApplyconvolution_Set_out_r(XApplyconvolution *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_OUT_R_DATA, (u32)(Data));
    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_OUT_R_DATA + 4, (u32)(Data >> 32));
}

u64 XApplyconvolution_Get_out_r(XApplyconvolution *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_OUT_R_DATA);
    Data += (u64)XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_OUT_R_DATA + 4) << 32;
    return Data;
}

void XApplyconvolution_Set_width(XApplyconvolution *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_WIDTH_DATA, Data);
}

u32 XApplyconvolution_Get_width(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_WIDTH_DATA);
    return Data;
}

void XApplyconvolution_Set_height(XApplyconvolution *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_HEIGHT_DATA, Data);
}

u32 XApplyconvolution_Get_height(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_HEIGHT_DATA);
    return Data;
}

void XApplyconvolution_Set_channels(XApplyconvolution *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_CHANNELS_DATA, Data);
}

u32 XApplyconvolution_Get_channels(XApplyconvolution *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XApplyconvolution_ReadReg(InstancePtr->Conv_BaseAddress, XAPPLYCONVOLUTION_CONV_ADDR_CHANNELS_DATA);
    return Data;
}

void XApplyconvolution_InterruptGlobalEnable(XApplyconvolution *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_GIE, 1);
}

void XApplyconvolution_InterruptGlobalDisable(XApplyconvolution *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_GIE, 0);
}

void XApplyconvolution_InterruptEnable(XApplyconvolution *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IER);
    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IER, Register | Mask);
}

void XApplyconvolution_InterruptDisable(XApplyconvolution *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IER);
    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IER, Register & (~Mask));
}

void XApplyconvolution_InterruptClear(XApplyconvolution *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XApplyconvolution_WriteReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_ISR, Mask);
}

u32 XApplyconvolution_InterruptGetEnabled(XApplyconvolution *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_IER);
}

u32 XApplyconvolution_InterruptGetStatus(XApplyconvolution *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XApplyconvolution_ReadReg(InstancePtr->Control_BaseAddress, XAPPLYCONVOLUTION_CONTROL_ADDR_ISR);
}


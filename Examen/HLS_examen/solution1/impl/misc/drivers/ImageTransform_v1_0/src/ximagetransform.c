// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
/***************************** Include Files *********************************/
#include "ximagetransform.h"

/************************** Function Implementation *************************/
#ifndef __linux__
int XImagetransform_CfgInitialize(XImagetransform *InstancePtr, XImagetransform_Config *ConfigPtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(ConfigPtr != NULL);

    InstancePtr->Control_BaseAddress = ConfigPtr->Control_BaseAddress;
    InstancePtr->Control_r_BaseAddress = ConfigPtr->Control_r_BaseAddress;
    InstancePtr->IsReady = XIL_COMPONENT_IS_READY;

    return XST_SUCCESS;
}
#endif

void XImagetransform_Start(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL) & 0x80;
    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL, Data | 0x01);
}

u32 XImagetransform_IsDone(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 1) & 0x1;
}

u32 XImagetransform_IsIdle(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL);
    return (Data >> 2) & 0x1;
}

u32 XImagetransform_IsReady(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL);
    // check ap_start to see if the pcore is ready for next input
    return !(Data & 0x1);
}

void XImagetransform_EnableAutoRestart(XImagetransform *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL, 0x80);
}

void XImagetransform_DisableAutoRestart(XImagetransform *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_AP_CTRL, 0);
}

void XImagetransform_Set_centerX(XImagetransform *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_CENTERX_DATA, Data);
}

u32 XImagetransform_Get_centerX(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_CENTERX_DATA);
    return Data;
}

void XImagetransform_Set_centerY(XImagetransform *InstancePtr, u32 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_CENTERY_DATA, Data);
}

u32 XImagetransform_Get_centerY(XImagetransform *InstancePtr) {
    u32 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_CENTERY_DATA);
    return Data;
}

void XImagetransform_Set_imageRGBA(XImagetransform *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_IMAGERGBA_DATA, (u32)(Data));
    XImagetransform_WriteReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_IMAGERGBA_DATA + 4, (u32)(Data >> 32));
}

u64 XImagetransform_Get_imageRGBA(XImagetransform *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_IMAGERGBA_DATA);
    Data += (u64)XImagetransform_ReadReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_IMAGERGBA_DATA + 4) << 32;
    return Data;
}

void XImagetransform_Set_output_r_offset(XImagetransform *InstancePtr, u64 Data) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_OUTPUT_R_OFFSET_DATA, (u32)(Data));
    XImagetransform_WriteReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_OUTPUT_R_OFFSET_DATA + 4, (u32)(Data >> 32));
}

u64 XImagetransform_Get_output_r_offset(XImagetransform *InstancePtr) {
    u64 Data;

    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Data = XImagetransform_ReadReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_OUTPUT_R_OFFSET_DATA);
    Data += (u64)XImagetransform_ReadReg(InstancePtr->Control_r_BaseAddress, XIMAGETRANSFORM_CONTROL_R_ADDR_OUTPUT_R_OFFSET_DATA + 4) << 32;
    return Data;
}

void XImagetransform_InterruptGlobalEnable(XImagetransform *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_GIE, 1);
}

void XImagetransform_InterruptGlobalDisable(XImagetransform *InstancePtr) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_GIE, 0);
}

void XImagetransform_InterruptEnable(XImagetransform *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_IER);
    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_IER, Register | Mask);
}

void XImagetransform_InterruptDisable(XImagetransform *InstancePtr, u32 Mask) {
    u32 Register;

    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    Register =  XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_IER);
    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_IER, Register & (~Mask));
}

void XImagetransform_InterruptClear(XImagetransform *InstancePtr, u32 Mask) {
    Xil_AssertVoid(InstancePtr != NULL);
    Xil_AssertVoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    XImagetransform_WriteReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_ISR, Mask);
}

u32 XImagetransform_InterruptGetEnabled(XImagetransform *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_IER);
}

u32 XImagetransform_InterruptGetStatus(XImagetransform *InstancePtr) {
    Xil_AssertNonvoid(InstancePtr != NULL);
    Xil_AssertNonvoid(InstancePtr->IsReady == XIL_COMPONENT_IS_READY);

    return XImagetransform_ReadReg(InstancePtr->Control_BaseAddress, XIMAGETRANSFORM_CONTROL_ADDR_ISR);
}


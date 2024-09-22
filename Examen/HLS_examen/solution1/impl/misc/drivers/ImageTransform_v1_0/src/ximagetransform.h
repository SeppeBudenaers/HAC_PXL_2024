// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XIMAGETRANSFORM_H
#define XIMAGETRANSFORM_H

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/
#ifndef __linux__
#include "xil_types.h"
#include "xil_assert.h"
#include "xstatus.h"
#include "xil_io.h"
#else
#include <stdint.h>
#include <assert.h>
#include <dirent.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>
#include <stddef.h>
#endif
#include "ximagetransform_hw.h"

/**************************** Type Definitions ******************************/
#ifdef __linux__
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;
#else
typedef struct {
#ifdef SDT
    char *Name;
#else
    u16 DeviceId;
#endif
    u64 Control_BaseAddress;
    u64 Control_r_BaseAddress;
} XImagetransform_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u64 Control_r_BaseAddress;
    u32 IsReady;
} XImagetransform;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XImagetransform_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XImagetransform_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XImagetransform_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XImagetransform_ReadReg(BaseAddress, RegOffset) \
    *(volatile u32*)((BaseAddress) + (RegOffset))

#define Xil_AssertVoid(expr)    assert(expr)
#define Xil_AssertNonvoid(expr) assert(expr)

#define XST_SUCCESS             0
#define XST_DEVICE_NOT_FOUND    2
#define XST_OPEN_DEVICE_FAILED  3
#define XIL_COMPONENT_IS_READY  1
#endif

/************************** Function Prototypes *****************************/
#ifndef __linux__
#ifdef SDT
int XImagetransform_Initialize(XImagetransform *InstancePtr, UINTPTR BaseAddress);
XImagetransform_Config* XImagetransform_LookupConfig(UINTPTR BaseAddress);
#else
int XImagetransform_Initialize(XImagetransform *InstancePtr, u16 DeviceId);
XImagetransform_Config* XImagetransform_LookupConfig(u16 DeviceId);
#endif
int XImagetransform_CfgInitialize(XImagetransform *InstancePtr, XImagetransform_Config *ConfigPtr);
#else
int XImagetransform_Initialize(XImagetransform *InstancePtr, const char* InstanceName);
int XImagetransform_Release(XImagetransform *InstancePtr);
#endif

void XImagetransform_Start(XImagetransform *InstancePtr);
u32 XImagetransform_IsDone(XImagetransform *InstancePtr);
u32 XImagetransform_IsIdle(XImagetransform *InstancePtr);
u32 XImagetransform_IsReady(XImagetransform *InstancePtr);
void XImagetransform_EnableAutoRestart(XImagetransform *InstancePtr);
void XImagetransform_DisableAutoRestart(XImagetransform *InstancePtr);

void XImagetransform_Set_centerX(XImagetransform *InstancePtr, u32 Data);
u32 XImagetransform_Get_centerX(XImagetransform *InstancePtr);
void XImagetransform_Set_centerY(XImagetransform *InstancePtr, u32 Data);
u32 XImagetransform_Get_centerY(XImagetransform *InstancePtr);
void XImagetransform_Set_imageRGBA(XImagetransform *InstancePtr, u64 Data);
u64 XImagetransform_Get_imageRGBA(XImagetransform *InstancePtr);
void XImagetransform_Set_output_r_offset(XImagetransform *InstancePtr, u64 Data);
u64 XImagetransform_Get_output_r_offset(XImagetransform *InstancePtr);

void XImagetransform_InterruptGlobalEnable(XImagetransform *InstancePtr);
void XImagetransform_InterruptGlobalDisable(XImagetransform *InstancePtr);
void XImagetransform_InterruptEnable(XImagetransform *InstancePtr, u32 Mask);
void XImagetransform_InterruptDisable(XImagetransform *InstancePtr, u32 Mask);
void XImagetransform_InterruptClear(XImagetransform *InstancePtr, u32 Mask);
u32 XImagetransform_InterruptGetEnabled(XImagetransform *InstancePtr);
u32 XImagetransform_InterruptGetStatus(XImagetransform *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

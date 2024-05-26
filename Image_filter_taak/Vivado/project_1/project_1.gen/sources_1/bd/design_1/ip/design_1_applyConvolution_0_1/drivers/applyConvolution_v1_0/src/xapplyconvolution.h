// ==============================================================
// Vitis HLS - High-Level Synthesis from C, C++ and OpenCL v2023.2 (64-bit)
// Tool Version Limit: 2023.10
// Copyright 1986-2022 Xilinx, Inc. All Rights Reserved.
// Copyright 2022-2023 Advanced Micro Devices, Inc. All Rights Reserved.
// 
// ==============================================================
#ifndef XAPPLYCONVOLUTION_H
#define XAPPLYCONVOLUTION_H

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
#include "xapplyconvolution_hw.h"

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
    u64 Conv_BaseAddress;
} XApplyconvolution_Config;
#endif

typedef struct {
    u64 Control_BaseAddress;
    u64 Conv_BaseAddress;
    u32 IsReady;
} XApplyconvolution;

typedef u32 word_type;

/***************** Macros (Inline Functions) Definitions *********************/
#ifndef __linux__
#define XApplyconvolution_WriteReg(BaseAddress, RegOffset, Data) \
    Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))
#define XApplyconvolution_ReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))
#else
#define XApplyconvolution_WriteReg(BaseAddress, RegOffset, Data) \
    *(volatile u32*)((BaseAddress) + (RegOffset)) = (u32)(Data)
#define XApplyconvolution_ReadReg(BaseAddress, RegOffset) \
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
int XApplyconvolution_Initialize(XApplyconvolution *InstancePtr, UINTPTR BaseAddress);
XApplyconvolution_Config* XApplyconvolution_LookupConfig(UINTPTR BaseAddress);
#else
int XApplyconvolution_Initialize(XApplyconvolution *InstancePtr, u16 DeviceId);
XApplyconvolution_Config* XApplyconvolution_LookupConfig(u16 DeviceId);
#endif
int XApplyconvolution_CfgInitialize(XApplyconvolution *InstancePtr, XApplyconvolution_Config *ConfigPtr);
#else
int XApplyconvolution_Initialize(XApplyconvolution *InstancePtr, const char* InstanceName);
int XApplyconvolution_Release(XApplyconvolution *InstancePtr);
#endif

void XApplyconvolution_Start(XApplyconvolution *InstancePtr);
u32 XApplyconvolution_IsDone(XApplyconvolution *InstancePtr);
u32 XApplyconvolution_IsIdle(XApplyconvolution *InstancePtr);
u32 XApplyconvolution_IsReady(XApplyconvolution *InstancePtr);
void XApplyconvolution_EnableAutoRestart(XApplyconvolution *InstancePtr);
void XApplyconvolution_DisableAutoRestart(XApplyconvolution *InstancePtr);

void XApplyconvolution_Set_image_r(XApplyconvolution *InstancePtr, u64 Data);
u64 XApplyconvolution_Get_image_r(XApplyconvolution *InstancePtr);
void XApplyconvolution_Set_out_r(XApplyconvolution *InstancePtr, u64 Data);
u64 XApplyconvolution_Get_out_r(XApplyconvolution *InstancePtr);
void XApplyconvolution_Set_width(XApplyconvolution *InstancePtr, u32 Data);
u32 XApplyconvolution_Get_width(XApplyconvolution *InstancePtr);
void XApplyconvolution_Set_height(XApplyconvolution *InstancePtr, u32 Data);
u32 XApplyconvolution_Get_height(XApplyconvolution *InstancePtr);
void XApplyconvolution_Set_channels(XApplyconvolution *InstancePtr, u32 Data);
u32 XApplyconvolution_Get_channels(XApplyconvolution *InstancePtr);

void XApplyconvolution_InterruptGlobalEnable(XApplyconvolution *InstancePtr);
void XApplyconvolution_InterruptGlobalDisable(XApplyconvolution *InstancePtr);
void XApplyconvolution_InterruptEnable(XApplyconvolution *InstancePtr, u32 Mask);
void XApplyconvolution_InterruptDisable(XApplyconvolution *InstancePtr, u32 Mask);
void XApplyconvolution_InterruptClear(XApplyconvolution *InstancePtr, u32 Mask);
u32 XApplyconvolution_InterruptGetEnabled(XApplyconvolution *InstancePtr);
u32 XApplyconvolution_InterruptGetStatus(XApplyconvolution *InstancePtr);

#ifdef __cplusplus
}
#endif

#endif

// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of image_r
//        bit 31~0 - image_r[31:0] (Read/Write)
// 0x14 : Data signal of image_r
//        bit 31~0 - image_r[63:32] (Read/Write)
// 0x18 : reserved
// 0x1c : Data signal of output_r_offset
//        bit 31~0 - output_r_offset[31:0] (Read/Write)
// 0x20 : Data signal of output_r_offset
//        bit 31~0 - output_r_offset[63:32] (Read/Write)
// 0x24 : reserved
// 0x28 : Data signal of width
//        bit 31~0 - width[31:0] (Read/Write)
// 0x2c : reserved
// 0x30 : Data signal of height
//        bit 31~0 - height[31:0] (Read/Write)
// 0x34 : reserved
// 0x38 : Data signal of channels
//        bit 31~0 - channels[31:0] (Read/Write)
// 0x3c : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONTROL_ADDR_IMAGE_R_DATA         0x10
#define CONTROL_BITS_IMAGE_R_DATA         64
#define CONTROL_ADDR_OUTPUT_R_OFFSET_DATA 0x1c
#define CONTROL_BITS_OUTPUT_R_OFFSET_DATA 64
#define CONTROL_ADDR_WIDTH_DATA           0x28
#define CONTROL_BITS_WIDTH_DATA           32
#define CONTROL_ADDR_HEIGHT_DATA          0x30
#define CONTROL_BITS_HEIGHT_DATA          32
#define CONTROL_ADDR_CHANNELS_DATA        0x38
#define CONTROL_BITS_CHANNELS_DATA        32

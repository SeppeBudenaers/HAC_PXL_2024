// 0x00 : reserved
// 0x04 : reserved
// 0x08 : reserved
// 0x0c : reserved
// 0x10 : Data signal of width
//        bit 31~0 - width[31:0] (Read/Write)
// 0x14 : reserved
// 0x18 : Data signal of height
//        bit 31~0 - height[31:0] (Read/Write)
// 0x1c : reserved
// 0x20 : Data signal of channels
//        bit 31~0 - channels[31:0] (Read/Write)
// 0x24 : reserved
// (SC = Self Clear, COR = Clear on Read, TOW = Toggle on Write, COH = Clear on Handshake)

#define CONV_ADDR_WIDTH_DATA    0x10
#define CONV_BITS_WIDTH_DATA    32
#define CONV_ADDR_HEIGHT_DATA   0x18
#define CONV_BITS_HEIGHT_DATA   32
#define CONV_ADDR_CHANNELS_DATA 0x20
#define CONV_BITS_CHANNELS_DATA 32

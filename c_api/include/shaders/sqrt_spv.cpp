#include <cstdlib>
 namespace kernel { namespace shaders {

extern const unsigned int sqrt_spv[472] = {
    0x07230203,0x00010000,0x00080007,0x00000047,0x00000000,0x00020011,0x00000001,0x0006000b,
    0x00000001,0x4c534c47,0x6474732e,0x3035342e,0x00000000,0x0003000e,0x00000000,0x00000001,
    0x0007000f,0x00000005,0x00000004,0x6e69616d,0x00000000,0x0000000c,0x0000003d,0x00060010,
    0x00000004,0x00000011,0x00000400,0x00000001,0x00000001,0x00030003,0x00000002,0x000001c2,
    0x00040005,0x00000004,0x6e69616d,0x00000000,0x00030005,0x00000008,0x00000069,0x00080005,
    0x0000000c,0x475f6c67,0x61626f6c,0x766e496c,0x7461636f,0x496e6f69,0x00000044,0x00050005,
    0x00000018,0x68737570,0x636f6c42,0x0000006b,0x00050006,0x00000018,0x00000000,0x61746f74,
    0x0000006c,0x00030005,0x0000001a,0x00000070,0x00040005,0x00000023,0x74706e69,0x00000000,
    0x00040005,0x00000025,0x31667562,0x00000000,0x00040006,0x00000025,0x00000000,0x00000058,
    0x00030005,0x00000027,0x00000000,0x00040005,0x0000002d,0x32667562,0x00000000,0x00040006,
    0x0000002d,0x00000000,0x00000059,0x00030005,0x0000002f,0x00000000,0x00070005,0x0000003d,
    0x4e5f6c67,0x6f576d75,0x72476b72,0x7370756f,0x00000000,0x00040047,0x0000000c,0x0000000b,
    0x0000001c,0x00050048,0x00000018,0x00000000,0x00000023,0x00000000,0x00030047,0x00000018,
    0x00000002,0x00040047,0x00000024,0x00000006,0x00000004,0x00040048,0x00000025,0x00000000,
    0x00000018,0x00050048,0x00000025,0x00000000,0x00000023,0x00000000,0x00030047,0x00000025,
    0x00000003,0x00040047,0x00000027,0x00000022,0x00000000,0x00040047,0x00000027,0x00000021,
    0x00000000,0x00040047,0x0000002c,0x00000006,0x00000004,0x00040048,0x0000002d,0x00000000,
    0x00000019,0x00050048,0x0000002d,0x00000000,0x00000023,0x00000000,0x00030047,0x0000002d,
    0x00000003,0x00040047,0x0000002f,0x00000022,0x00000000,0x00040047,0x0000002f,0x00000021,
    0x00000001,0x00040047,0x0000003d,0x0000000b,0x00000018,0x00040047,0x00000046,0x0000000b,
    0x00000019,0x00020013,0x00000002,0x00030021,0x00000003,0x00000002,0x00040015,0x00000006,
    0x00000020,0x00000001,0x00040020,0x00000007,0x00000007,0x00000006,0x00040015,0x00000009,
    0x00000020,0x00000000,0x00040017,0x0000000a,0x00000009,0x00000003,0x00040020,0x0000000b,
    0x00000001,0x0000000a,0x0004003b,0x0000000b,0x0000000c,0x00000001,0x0004002b,0x00000009,
    0x0000000d,0x00000000,0x00040020,0x0000000e,0x00000001,0x00000009,0x0003001e,0x00000018,
    0x00000006,0x00040020,0x00000019,0x00000009,0x00000018,0x0004003b,0x00000019,0x0000001a,
    0x00000009,0x0004002b,0x00000006,0x0000001b,0x00000000,0x00040020,0x0000001c,0x00000009,
    0x00000006,0x00020014,0x0000001f,0x00030016,0x00000021,0x00000020,0x00040020,0x00000022,
    0x00000007,0x00000021,0x0003001d,0x00000024,0x00000021,0x0003001e,0x00000025,0x00000024,
    0x00040020,0x00000026,0x00000002,0x00000025,0x0004003b,0x00000026,0x00000027,0x00000002,
    0x00040020,0x00000029,0x00000002,0x00000021,0x0003001d,0x0000002c,0x00000021,0x0003001e,
    0x0000002d,0x0000002c,0x00040020,0x0000002e,0x00000002,0x0000002d,0x0004003b,0x0000002e,
    0x0000002f,0x00000002,0x0004002b,0x00000021,0x00000032,0x00000000,0x0004002b,0x00000021,
    0x00000038,0x3f000000,0x0004003b,0x0000000b,0x0000003d,0x00000001,0x0004002b,0x00000009,
    0x00000040,0x00000400,0x0004002b,0x00000009,0x00000045,0x00000001,0x0006002c,0x0000000a,
    0x00000046,0x00000040,0x00000045,0x00000045,0x00050036,0x00000002,0x00000004,0x00000000,
    0x00000003,0x000200f8,0x00000005,0x0004003b,0x00000007,0x00000008,0x00000007,0x0004003b,
    0x00000022,0x00000023,0x00000007,0x0004003b,0x00000022,0x00000034,0x00000007,0x00050041,
    0x0000000e,0x0000000f,0x0000000c,0x0000000d,0x0004003d,0x00000009,0x00000010,0x0000000f,
    0x0004007c,0x00000006,0x00000011,0x00000010,0x0003003e,0x00000008,0x00000011,0x000200f9,
    0x00000012,0x000200f8,0x00000012,0x000400f6,0x00000014,0x00000015,0x00000000,0x000200f9,
    0x00000016,0x000200f8,0x00000016,0x0004003d,0x00000006,0x00000017,0x00000008,0x00050041,
    0x0000001c,0x0000001d,0x0000001a,0x0000001b,0x0004003d,0x00000006,0x0000001e,0x0000001d,
    0x000500b1,0x0000001f,0x00000020,0x00000017,0x0000001e,0x000400fa,0x00000020,0x00000013,
    0x00000014,0x000200f8,0x00000013,0x0004003d,0x00000006,0x00000028,0x00000008,0x00060041,
    0x00000029,0x0000002a,0x00000027,0x0000001b,0x00000028,0x0004003d,0x00000021,0x0000002b,
    0x0000002a,0x0003003e,0x00000023,0x0000002b,0x0004003d,0x00000006,0x00000030,0x00000008,
    0x0004003d,0x00000021,0x00000031,0x00000023,0x000500be,0x0000001f,0x00000033,0x00000031,
    0x00000032,0x000300f7,0x00000036,0x00000000,0x000400fa,0x00000033,0x00000035,0x0000003a,
    0x000200f8,0x00000035,0x0004003d,0x00000021,0x00000037,0x00000023,0x0007000c,0x00000021,
    0x00000039,0x00000001,0x0000001a,0x00000037,0x00000038,0x0003003e,0x00000034,0x00000039,
    0x000200f9,0x00000036,0x000200f8,0x0000003a,0x0003003e,0x00000034,0x00000032,0x000200f9,
    0x00000036,0x000200f8,0x00000036,0x0004003d,0x00000021,0x0000003b,0x00000034,0x00060041,
    0x00000029,0x0000003c,0x0000002f,0x0000001b,0x00000030,0x0003003e,0x0000003c,0x0000003b,
    0x000200f9,0x00000015,0x000200f8,0x00000015,0x00050041,0x0000000e,0x0000003e,0x0000003d,
    0x0000000d,0x0004003d,0x00000009,0x0000003f,0x0000003e,0x00050084,0x00000009,0x00000041,
    0x0000003f,0x00000040,0x0004007c,0x00000006,0x00000042,0x00000041,0x0004003d,0x00000006,
    0x00000043,0x00000008,0x00050080,0x00000006,0x00000044,0x00000043,0x00000042,0x0003003e,
    0x00000008,0x00000044,0x000200f9,0x00000012,0x000200f8,0x00000014,0x000100fd,0x00010038
};
}} //namespace kernel, shaders
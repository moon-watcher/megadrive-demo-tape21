#include "framebuffer.h"

u8* GSKE_FrameBuffer;
u16 GSKE_Height;
u16 GSKE_HLineOffsets[256];

void FB_init()
{
    BMP_init(BMP_ENABLE_ASYNCFLIP | BMP_ENABLE_EXTENDEDBLANK);
    GSKE_FrameBuffer = NULL;
    
    u16 i;
    for (i=0 ; i<BMP_HEIGHT ; ++i)
        GSKE_HLineOffsets[i] = i*BMP_WIDTH;
}

void FB_exit()
{
    BMP_end();
}

void FB_flip()
{
    BMP_flip();
}

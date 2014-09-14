#ifndef _GSKE_FRAMEBUFFER_H_
#define _GSKE_FRAMEBUFFER_H_

#include "genesis.h"

extern u8* GSKE_FrameBuffer;
extern u16 GSKE_HLineOffsets[256];

void FB_init();
void FB_exit();
void FB_flip();

#endif

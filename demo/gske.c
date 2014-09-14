#include "gske.h"
#include "music.h"

u32 SND_getTime_PCM()
{
    Z80_requestBus(1);
    vu8 *pb = (u8*)(Z80_DRV_PARAMS+0x10);
    u8 a=pb[0];
    u8 b=pb[1];
    Z80_releaseBus();
    u32 cr = (u32)a<<8|(u32)b<<16;
    cr -= (u32)music;
    cr /= 16;
    return cr;
}

void GSKE_init(u16 hard)
{
    // handle reset
    if (hard==0)
    {
        GSKE_DestroyScene();
    }
    
    VDP_init();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
    VDP_setScreenWidth256(); 
    
    GSKE_CreateScene();
}

void GSKE_exit()
{
    GSKE_DestroyScene();
}

void GSKE_init3d()
{
    VDP_init();
    VDP_setHInterrupt(0);
    VDP_setHilightShadow(0);
    VDP_setScreenWidth320(); 
    FB_init();   
    GSKE_setScrollMode(GSKE_HSCROLL_Plane, GSKE_VSCROLL_Plane);
    
    M3D_reset();
    M3D_setViewport(BMP_WIDTH, BMP_HEIGHT); 
}

void GSKE_exit3d()
{
    FB_exit();
}

void GSKE_update3d()
{
    FB_flip();
    BMP_clear();
    GSKE_FrameBuffer = BMP_getWritePointer();
    GSKE_UpdateScene();
}

void GSKE_setScrollMode(u8 horizontal, u8 vertical)
{
    VDP_setReg(0x0b, horizontal|vertical);
} 

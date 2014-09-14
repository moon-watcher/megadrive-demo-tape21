#include "effect_nuclear.h"

u8* getNuclear(int i)
{
    if (i==0) return (u8*)&nuclear_1[18];
    if (i==1) return (u8*)&nuclear_2[18];
    if (i==2) return (u8*)&nuclear_3[18];
    if (i==3) return (u8*)&nuclear_4[18];
    if (i==4) return (u8*)&nuclear_5[18];
    if (i==5) return (u8*)&nuclear_6[18];
    if (i==6) return (u8*)&nuclear_7[18];
    if (i==7) return (u8*)&nuclear_8[18];
    if (i==8) return (u8*)&nuclear_9[18];
    if (i==9) return (u8*)&nuclear_10[18];
    if (i==10) return (u8*)&nuclear_11[18];
    if (i==11) return (u8*)&nuclear_12[18];
    if (i==12) return (u8*)&nuclear_13[18];
    if (i==13) return (u8*)&nuclear_14[18];
    if (i==14) return (u8*)&nuclear_15[18];
    if (i==15) return (u8*)&nuclear_16[18];
    if (i==16) return (u8*)&nuclear_17[18];
    if (i==17) return (u8*)&nuclear_18[18];
    if (i==18) return (u8*)&nuclear_19[18];
    return (u8*)&nuclear_20[18];
}

void EFFECT_nuclear()
{
    //GSKE_init3d();
    VDP_setPalette(PAL0, (u16*)&nuclear_1[2]);
    
    int i;
    for (i=0 ; i<8 ; ++i)
    {
        VDP_setPaletteColor(PAL0, i, (i*2));
        VDP_setPaletteColor(PAL0, i+8, (i+8));
    }
    u32 start = SND_getTime_PCM();
    u32 t=0;
    while(t<4000)
    {
        u32 ct = SND_getTime_PCM();
        if (ct>start) t = ct-start;
    
        GSKE_update3d();
        
        u8* frame = getNuclear((t/200)%20);
       
        memcpy(GSKE_FrameBuffer, frame, BMP_WIDTH*BMP_HEIGHT);
    }    
    
    //GSKE_exit3d();
}

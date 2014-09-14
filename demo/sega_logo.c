#include "sega_logo.h"

void EFFECT_logo()
{
    GSKE_init3d();
    
    VDP_setPalette(PAL0, (u16*)&logo_sega[2]);
    u8* logo = (u8*)&logo_sega[18];
    u32 t=0;    
    while(SND_getTime_PCM()<3500)
    {
        GSKE_update3d();
        t+=12;
            
        u32 y;
        u32 s = t%128;
        for (y=0 ; y<56 ; ++y)
        {
            u32 off = sinFix16(y*40+t/2)*(y>s-6&&y<s+6?1:0)/6;
            memcpy(GSKE_FrameBuffer+(y+(BMP_HEIGHT-56)/2)*BMP_WIDTH+(BMP_WIDTH-84)/2+off, logo+y*84, 84);
        }
        
        for (y=4 ; y<16 ; ++y)
        {
            u32 col = sinFix16(-y*30+t*10)/60;
            //col = (col/20)&15;
            VDP_setPaletteColor(PAL0, y, col&15);
        }
        
        u32 c = (t%45)/12+2;
        VDP_setPaletteColor(PAL0, 3, c);
    }
    
}

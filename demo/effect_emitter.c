#include "effect_emitter.h"

void EFFECT_emitter(int speed, int length)
{
    u16* scrollTable;
    u16 curY;
    int curX;
    u16 t=0;
    int vscroll;
    u16 scrollX[21];

    void initTable()
    {
        scrollTable = (u16*)MEM_alloc(VDP_getScreenHeight()*sizeof(u16));
        vscroll=0x840; 
        int k;
        int h = VDP_getScreenHeight();
        for (k=0 ; k<h ; ++k)
        {
            int count = (k*k)*0.4f; //k*(1.0f+k*1.6f/((h*2)-1)); // 
            if (0x840-vscroll<count) vscroll = 0x840-count;
            scrollTable[k] = vscroll;
        }
        
        for (h=0 ; h<21 ; ++h)
            scrollX[h] = -(h-10)*(h-10)/6;
    }

    int posY = 0;

    void vblank()
    {
        curY = 0;
        posY +=speed;
    } 

    void hblank()
    {
        vu16 *pw = (u16 *) GFX_DATA_PORT;
        vu32 *pl = (u32 *) GFX_CTRL_PORT;
        int val = scrollTable[curY]+posY+t/4;
        int val2 = scrollTable[curY]+(posY+t/8)/3;
        
        int x;
        for (x=0 ; x<21 ; ++x)
        {
            u16 addr = (x&0x1F)*4;
            *pl = GFX_WRITE_VSRAM_ADDR(addr);
            *pw = val+scrollX[x];
            *pl = GFX_WRITE_VSRAM_ADDR(addr+2);
            *pw = val2+scrollX[x];
        }
        
        ++curY;
    } 
    
    initTable();
    u32 start = SND_getTime_PCM();
    
    int xs=0, ys=0;
    
    u16 w = emitter[0];
    u16 h = emitter[1];
    VDP_setPalette(PAL2, &emitter[2]);
    VDP_loadBMPTileData((u32*) &emitter[18], 1, w / 8, h / 8, w/8 );
    for (ys=0 ; ys<VDP_getPlanHeight()/(h/8); ++ys)
    for (xs=0 ; xs<VDP_getPlanWidth()/(w/8); ++xs)
        VDP_fillTileMapRectInc(APLAN, TILE_ATTR_FULL(PAL2, 0, 0, 0, 1), xs*(w/8), ys*(h/8), w / 8, h / 8);
    
    w = emitter_back[0];
    h = emitter_back[1];
    VDP_setPalette(PAL1, &emitter_back[2]);
    VDP_loadBMPTileData((u32*) &emitter_back[18], 257, w / 8, h / 8, w/8 );
    for (ys=0 ; ys<VDP_getPlanHeight()/(h/8); ++ys)
    for (xs=0 ; xs<VDP_getPlanWidth()/(w/8); ++xs)
        VDP_fillTileMapRectInc(BPLAN, TILE_ATTR_FULL(PAL1, 0, 0, 0, 257), xs*(w/8), ys*(h/8), w / 8, h / 8);
    
    SYS_setVIntCallback(vblank);
    SYS_setHIntCallback(hblank);
    GSKE_setScrollMode(GSKE_HSCROLL_Line, GSKE_VSCROLL_Column);
    VDP_setHIntCounter(1);
    VDP_setHInterrupt(1); 

    curY = 0;
    
    int m;
    for (m=0 ; m<VDP_getScreenHeight() ; ++m)
    {
        VDP_setHorizontalScroll(APLAN, m, sinFix16(m+1800));
        VDP_setHorizontalScroll(BPLAN, m, sinFix16(m+1800));
    }
    
    m = 0;
    t=0;
    do
    {
        u32 ct = SND_getTime_PCM();
        if (ct>start) t = ct-start;
        
        VDP_waitDMACompletion(); 
        ++m;
    }
    while(t<length);
    
    SYS_setVIntCallback(0);
    SYS_setHIntCallback(0);
    MEM_free(scrollTable);
}


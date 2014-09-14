#include "effect_axelay.h"

void EFFECT_axelay(int sens, int speed, int length)
{
    u16* scrollTable;

    
    u16 curY;
    u16 ttta=0;
    int vscroll;

    u16 paletteTest[16][16];
    u16 paletteTestBack[16][16];

    void initTable()
    {
        int h = 180;
        scrollTable = (u16*)MEM_alloc(h*sizeof(u16));
        vscroll=0x840; 
        int k;
        int p = (h/2)/8;
        
        int sub = 0;
        int subb[h];
        for (k=0 ; k<h ; ++k)
        {
            int m = k;
            if (m%p==0)
                sub += p*(m/p);
            subb[k] = sub;
        }

        for (k=0 ; k<h ; ++k)
        {
            if (k<h/2)
            {
                int m = sinFix16(k*255/(h/2))*(h/2)/64;
                vscroll = m*(7-m/p)+subb[m];
                
                //vscroll = k*(4-k/p)-subb[h-k-1];
            }
            else
            {
                //vscroll = 0;
                vscroll --;
            }
            
            scrollTable[k] = vscroll;
        }
        
        for (k=2 ; k<h-2 ; ++k)
        {
            scrollTable[k] = (scrollTable[k-2]+scrollTable[k-1]*2+scrollTable[k]*3+scrollTable[k+1]*2+scrollTable[k+2])/9;
        }
        
        for (h=0 ; h<16 ; ++h)
        {
            for (k=0 ; k<16 ; ++k)
            {
                int r = ((u16*)&tile_sky_up[2])[k]&15;
                int g = (((u16*)&tile_sky_up[2])[k]>>4)&15;
                int b = (((u16*)&tile_sky_up[2])[k]>>8)&15;
                r += (15-h); if (r>15) r=15;
                //g += (15-h); if (g>15) g=15;
                //b += (15-h); if (b>15) b=15;
                //r -= (15-h); if (r<0) r=0;
                g -= (15-h); if (g<0) g=0;
                b -= (15-h); if (b<0) b=0;
                int va = 15;
                /*
                if (r<va) { r+=(15-h)/2; if (r>va) r = va; }
                if (r>va) { r-=(15-h)/2; if (r<va) r = va; }
                if (g<va) { g+=(15-h)/2; if (g>va) g = va; }
                if (g>va) { g-=(15-h)/2; if (g<va) g = va; }
                if (b<va) { b+=(15-h)/2; if (b>va) b = va; }
                if (b>va) { b-=(15-h)/2; if (b<va) b = va; }
                */
                paletteTest[h][k] = r|(g<<4)|(b<<8);
                
                r = ((u16*)&tile_sky[2])[k]&15;
                g = (((u16*)&tile_sky[2])[k]>>4)&15;
                b = (((u16*)&tile_sky[2])[k]>>8)&15;
                r += (15-h); if (r>15) r=15;
                //g += (15-h); if (g>15) g=15;
                //b += (15-h); if (b>15) b=15;
                //r -= (15-h); if (r<0) r=0;
                g -= (15-h); if (g<0) g=0;
                b -= (15-h); if (b<0) b=0;
                /*
                if (r<va) { r+=(15-h)/2; if (r>va) r = va; }
                if (r>va) { r-=(15-h)/2; if (r<va) r = va; }
                if (g<va) { g+=(15-h)/2; if (g>va) g = va; }
                if (g>va) { g-=(15-h)/2; if (g<va) g = va; }
                if (b<va) { b+=(15-h)/2; if (b>va) b = va; }
                if (b>va) { b-=(15-h)/2; if (b<va) b = va; }*/
                
                
                
                paletteTestBack[h][k] = r|(g<<4)|(b<<8);
            }
        }
    }

    int posY = 0;
    int incPosY = speed;

    void vblank()
    {
        ++ttta;
        curY = 0;
        posY += incPosY;
        VDP_setPalette(PAL1, paletteTest[0]);
        VDP_setPalette(PAL2, paletteTestBack[0]);
    } 

    void hblank()
    {
        if (curY<32)
        {
            if (curY%4==0) VDP_setPalette(PAL1, paletteTest[curY/2]);
            else if (curY%4==2) VDP_setPalette(PAL2, paletteTestBack[curY/2]);
        }
        else if (curY==32)
        {
            VDP_setPalette(PAL1, &tile_sky_up[2]);
        }
        else if (curY==34)
        {
            VDP_setPalette(PAL2, &tile_sky[2]);
        }
        
        VDP_setVerticalScroll(APLAN, 0, scrollTable[curY]-posY-ttta/4);
        VDP_setVerticalScroll(BPLAN, 0, scrollTable[curY]-(posY+ttta/4)/2);
        
        curY++;
    } 

    int incPosX = sens*speed;
    int posX = 0;    
    
    GSKE_setScrollMode(GSKE_HSCROLL_Plane, GSKE_VSCROLL_Plane);
    
    initTable();   
    
    u32 start = SND_getTime_PCM();
    
    int xs=0, ys=0;
    u16 w = tile_sky[0];
    u16 h = tile_sky[1];
    
    VDP_setPalette(PAL2, &tile_sky[2]);
    VDP_loadBMPTileData((u32*) &tile_sky[18], 257, w / 8, h / 8, w/8 );
    for (ys=0 ; ys<VDP_getPlanHeight()/(h/8); ++ys)
    for (xs=0 ; xs<VDP_getPlanWidth()/(w/8); ++xs)
        VDP_fillTileMapRectInc(BPLAN, TILE_ATTR_FULL(PAL2, 0, 0, 0, 257), xs*(w/8), ys*(h/8), w / 8, h / 8);
       
    w = tile_sky_up[0];
    h = tile_sky_up[1];
        
    VDP_setPalette(PAL1, &tile_sky_up[2]);
    VDP_loadBMPTileData((u32*) &tile_sky_up[18], 1, w / 8, h / 8, w/8 );
    for (ys=0 ; ys<VDP_getPlanHeight()/(h/8); ++ys)
    for (xs=0 ; xs<VDP_getPlanWidth()/(w/8); ++xs)
        VDP_fillTileMapRectInc(APLAN, TILE_ATTR_FULL(PAL1, 0, 0, 0, 1), xs*(w/8), ys*(h/8), w / 8, h / 8);
    
    SYS_setVIntCallback(vblank);
    SYS_setHIntCallback(hblank);
    VDP_setHIntCounter(1);
    VDP_setHInterrupt(1); 
    
    curY = 0;
    
    u32 t=0;
    do
    {
        u32 ct = SND_getTime_PCM();
        if (ct>start) t = ct-start;
        
        posX = t*incPosX/8;
        
        VDP_setHorizontalScroll(APLAN, 0, posX);
        VDP_setHorizontalScroll(BPLAN, 0, posX*3/4);
    }
    while(t<length);
    
    SYS_setVIntCallback(0);
    SYS_setHIntCallback(0); 
    MEM_free(scrollTable);
}


#include "config.h"
#include "types.h"

#include "vdp.h"
#include "vdp_bg.h"

#include "vdp_dma.h"
#include "vdp_tile.h"

#include "tab_vram.h"

inline void VDP_setHorizontalScroll(u16 plan, u16 line, u16 value)
{
    vu16 *pw;
    vu32 *pl;
    u16 addr;

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    addr = HSCRL + ((line & 0xFF) * 4);
    if (plan == BPLAN) addr += 2;

    *pl = GFX_WRITE_VRAM_ADDR(addr);
    *pw = value;
}

inline void VDP_setVerticalScroll(u16 plan, u16 cell, u16 value)
{
    vu16 *pw;
    vu32 *pl;
    u16 addr;

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    addr = (cell & 0x1F) * 4;
    if (plan == BPLAN) addr += 2;

    *pl = GFX_WRITE_VSRAM_ADDR(addr);
    *pw = value;
}


void VDP_clearPlan(u16 plan, u8 use_dma)
{
    if (use_dma)
    {
        // wait for previous DMA completion
        VDP_waitDMACompletion();
        // then do DMA
        VDP_doVRamDMAFill(plan, VDP_getPlanWidth() * VDP_getPlanHeight() * 2, 0);
    }
    else
    {
        vu32 *plctrl;
        vu32 *pldata;
        u16 i;

        /* point to vdp port */
        plctrl = (u32 *) GFX_CTRL_PORT;
        pldata = (u32 *) GFX_DATA_PORT;

        *plctrl = GFX_WRITE_VRAM_ADDR(plan);

        // unroll a bit
        i = VDP_getPlanWidth() * VDP_getPlanHeight() / (2 * 8);
        while (i--)
        {
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
            *pldata = 0;
        }
    }
}

#include "config.h"
#include "types.h"

#include "vdp.h"
#include "vdp_pal.h"

#include "base.h"

// we don't want to share them
extern u32 VIntProcess;
extern u32 HBlankProcess;


u16 VDP_getPaletteColor(u16 numpal, u16 numcol)
{
    vu16 *pw;
    vu32 *pl;
    u16 addr;

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    addr = (numpal * 32) + (numcol * 2);
    *pl = GFX_READ_CRAM_ADDR(addr);

    return *pw;
}

void VDP_getPalette(u16 num, u16 *pal)
{
    vu16 *pw;
    vu32 *pl;
    u16 *dest;
    u16 i;
    u16 addr;

    VDP_setAutoInc(2);

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    dest = pal;
    addr = num * 32;
    *pl = GFX_READ_CRAM_ADDR(addr);

    i = 16;
    while(i--) *dest++ = *pw;
}


void VDP_setPaletteColor(u16 numpal, u16 numcol, u16 value)
{
    vu16 *pw;
    vu32 *pl;
    u16 addr;

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    addr = (numpal * 32) + (numcol * 2);
    *pl = GFX_WRITE_CRAM_ADDR(addr);

    *pw = value;
}

inline void VDP_setPalette(u16 num, const u16 *pal)
{
    vu16 *pw;
    vu32 *pl;
    const u16 *src;
    u16 i;
    u16 addr;

    //VDP_setAutoInc(2);

    /* Point to vdp port */
    pw = (u16 *) GFX_DATA_PORT;
    pl = (u32 *) GFX_CTRL_PORT;

    src = pal;
    addr = num * 32;
    *pl = GFX_WRITE_CRAM_ADDR(addr);

    i = 16;
    while(i--) *pw = *src++;
}



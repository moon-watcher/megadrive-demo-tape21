#include "config.h"
#include "types.h"

#include "bmp_cmn.h"
#include "bmp_intr.h"
#include "bmp.h"

#include "base.h"
#include "memory.h"
#include "maths3D.h"

#include "vdp.h"
#include "vdp_tile.h"
#include "vdp_pal.h"
#include "vdp_bg.h"

#include "tab_vram.h"


// we don't want to share them
extern u32 VIntProcess;
extern u32 HBlankProcess;

static void internalBufferFlip();
static void initTilemap(u16 num);
static u16 doBlitNorm();
static u16 doBlitBlank();
static u16 doBlitBlankExt();
static void clearBuffer(u8 *bmp_buffer);


void BMP_init(u16 flags)
{
    // common bmp init tasks and memory allocation
    _bmp_init();

    // do some init process
    BMP_setFlags(0);

    // prepare tilemap
    initTilemap(0);
    initTilemap(1);

    // first init, clear and flip
    BMP_clear();
    BMP_flip();
    // second init, clear and flip for correct init (double buffer)
    BMP_clear();
    BMP_flip();

    BMP_setFlags(flags);
}

void BMP_end()
{
    // end some stuff
    BMP_setFlags(0);

    // release others stuff
    _bmp_end();
}

void BMP_reset()
{
    BMP_init(bmp_flags);
}


void BMP_setFlags(u16 value)
{
    const u16 oldf = bmp_flags;

    // common setFlags tasks (also handle flags constraints)
    _bmp_setFlags(value);

    // if internals flags hasn't changed --> exit
    if (bmp_flags == oldf) return;

    // re enabled VDP if it was disabled because of extended blank
    if (oldf & BMP_ENABLE_EXTENDEDBLANK)
        VDP_setEnable(1);

    // async blit (H Int processing)
    if (HAS_FLAG(BMP_ENABLE_ASYNCFLIP))
    {
        const u16 scrh = VDP_getScreenHeight();

        if (HAS_FLAG(BMP_ENABLE_EXTENDEDBLANK))
        {
            VDP_setHIntCounter(scrh - (((scrh - BMP_HEIGHT) >> 1) + 1));
            // blit method
            doBlit = &doBlitBlankExt;
        }
        else
        {
            VDP_setHIntCounter(scrh - 1);
            // blit method
            if (HAS_FLAG(BMP_ENABLE_BLITONBLANK)) doBlit = &doBlitBlank;
            else doBlit = &doBlitNorm;
        }
        // enabled bitmap H Int processing
        HBlankProcess |= PROCESS_BITMAP_TASK;
        VDP_setHInterrupt(1);
    }
    else
    {
        // normal blit
        doBlit = &doBlitNorm;
        // disabled bitmap H Int processing
        VDP_setHInterrupt(0);
        HBlankProcess &= ~PROCESS_BITMAP_TASK;
    }
}

void BMP_flip()
{
    // wait for vsync ?
    if (HAS_FLAG(BMP_ENABLE_WAITVSYNC))
    {
        // async flip ?
        if (HAS_FLAG(BMP_ENABLE_ASYNCFLIP))
        {
            // wait for previous async flip to complete
            BMP_waitAsyncFlipComplete();
            // flip bitmap buffer
            internalBufferFlip();
            // request a flip (will be processed in blank period --> BMP_doBlankProcess)
            bmp_state |= BMP_STAT_FLIPWAITING;
        }
        else
        {
            VDP_waitVSync();
            // flip bitmap buffer
            internalBufferFlip();
            // blit buffer to VRAM and flip vdp display
            _bmp_doFlip();
        }
    }
    else
    {
         // flip bitmap buffer
         internalBufferFlip();
         // blit buffer to VRAM and flip vdp display
         _bmp_doFlip();
    }
}

static void internalBufferFlip()
{
    if (READ_IS_FB0)
    {
        bmp_buffer_read = bmp_buffer_1;
        bmp_buffer_write = bmp_buffer_0;
    }
    else
    {
        bmp_buffer_read = bmp_buffer_0;
        bmp_buffer_write = bmp_buffer_1;
    }
}


static void initTilemap(u16 num)
{
    vu32 *plctrl;
    vu16 *pwdata;
    u16 tile_ind;
    u32 addr_tilemap;
    u16 i, j;

    VDP_setAutoInc(2);

    // calculated
    const u32 offset = BMP_FBTILEMAP_OFFSET;

    if (num == 0)
    {
        addr_tilemap = BMP_FB0TILEMAP_BASE + offset;
        tile_ind = BMP_FB0TILEINDEX;
    }
    else
    {
        addr_tilemap = BMP_FB1TILEMAP_BASE + offset;
        tile_ind = BMP_FB1TILEINDEX;
    }

    // point to vdp port
    plctrl = (u32 *) GFX_CTRL_PORT;
    pwdata = (u16 *) GFX_DATA_PORT;

    i = BMP_CELLHEIGHT;
    while(i--)
    {
        // set destination address for tilemap
        *plctrl = GFX_WRITE_VRAM_ADDR(addr_tilemap);

        // write tilemap line to VDP
        j = BMP_CELLWIDTH >> 3;
        while(j--)
        {
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
            *pwdata = tile_ind++;
        }

        addr_tilemap += BMP_PLANWIDTH * 2;
    }
}

static u16 doBlitNorm()
{
    vu32 *plctrl;
    vu32 *pldata;
    u32 *src;
    u16 i, j;

    VDP_setAutoInc(2);

    src = (u32 *) bmp_buffer_read;

    // point to vdp port
    plctrl = (u32 *) GFX_CTRL_PORT;
    pldata = (u32 *) GFX_DATA_PORT;

    // set destination address for tile
    if (READ_IS_FB0)
        *plctrl = GFX_WRITE_VRAM_ADDR(BMP_FB0TILE);
    else
        *plctrl = GFX_WRITE_VRAM_ADDR(BMP_FB1TILE);

    u32 pitch = BMP_PITCH>>2;
    i = BMP_CELLHEIGHT;
    while(i--)
    {
        j = BMP_CELLWIDTH;
        while(j--)
        {
            // send it to VRAM
            *pldata = src[0];
            *pldata = src[pitch];
            *pldata = src[pitch<<1];
            *pldata = src[pitch*3];
            *pldata = src[pitch<<2];
            *pldata = src[pitch*5];
            *pldata = src[pitch<<2];
            *pldata = src[pitch*7];
            ++src;
        }
        src += pitch*7;
    }
    return 1;
}

static u16 doBlitBlank()
{
    vu32 *plctrl;
    vu32 *pldata;
    u32 *src;
    u32 addr_tile;
    u16 i, j;

    static u16 save_i, save_j;

    VDP_setAutoInc(2);

    src = (u32 *) bmp_buffer_read;

    if (READ_IS_FB0)
        addr_tile = BMP_FB0TILE;
    else
        addr_tile = BMP_FB1TILE;

    // point to vdp port
    plctrl = (u32 *) GFX_CTRL_PORT;
    pldata = (u32 *) GFX_DATA_PORT;

    // previous blit not completed ?
    if (bmp_state & BMP_STAT_BLITTING)
    {
        const u16 done_i = BMP_CELLHEIGHT - save_i;
        const u16 done_j = BMP_CELLWIDTH - save_j;

        // adjust tile address
        addr_tile += ((done_i * BMP_CELLWIDTH) + done_j) * 32;
        // adjust src pointer
        src += (done_i * (BMP_YPIXPERTILE * (BMP_PITCH / 4))) + done_j;

        // set destination address for tile
        *plctrl = GFX_WRITE_VRAM_ADDR(addr_tile);

        // restore j position
        j = save_j;

        while(j--)
        {
            // send it to VRAM
            *pldata = src[(BMP_PITCH * 0) / 4];
            *pldata = src[(BMP_PITCH * 1) / 4];
            *pldata = src[(BMP_PITCH * 2) / 4];
            *pldata = src[(BMP_PITCH * 3) / 4];
            *pldata = src[(BMP_PITCH * 4) / 4];
            *pldata = src[(BMP_PITCH * 5) / 4];
            *pldata = src[(BMP_PITCH * 6) / 4];
            *pldata = src[(BMP_PITCH * 7) / 4];
            addr_tile += 32;
            ++src;
        }

        src += (7 * (BMP_PITCH / 4));

        // restore i position
        i = save_i - 1;
    }
    else
    {
        // start blit
        bmp_state |= BMP_STAT_BLITTING;
        i = BMP_CELLHEIGHT;

        // set destination address for tile
        *plctrl = GFX_WRITE_VRAM_ADDR(addr_tile);
    }

    while(i--)
    {
        j = BMP_CELLWIDTH;
        while(j--)
        {
            // blank period finished ?
            if (!GET_VDPSTATUS(VDP_VBLANK_FLAG))
            {
                // save current position and exit
                save_i = i + 1;
                save_j = j + 1;
                return 0;
            }

            // send it to VRAM
            *pldata = src[(BMP_PITCH * 0) / 4];
            *pldata = src[(BMP_PITCH * 1) / 4];
            *pldata = src[(BMP_PITCH * 2) / 4];
            *pldata = src[(BMP_PITCH * 3) / 4];
            *pldata = src[(BMP_PITCH * 4) / 4];
            *pldata = src[(BMP_PITCH * 5) / 4];
            *pldata = src[(BMP_PITCH * 6) / 4];
            *pldata = src[(BMP_PITCH * 7) / 4];

            ++src;
        }

        src += (7 * BMP_PITCH) / 4;
    }

    // blit done
    bmp_state &= ~BMP_STAT_BLITTING;

    return 1;
}

static u16 doBlitBlankExt()
{
    vu32 *plctrl;
    vu32 *pldata;
    u32 *src;
    u32 addr_tile;
    u16 i, j;

    static u16 save_i, save_j;

    VDP_setAutoInc(2);

    src = (u32 *) bmp_buffer_read;

    if (READ_IS_FB0)
        addr_tile = BMP_FB0TILE;
    else
        addr_tile = BMP_FB1TILE;

    /* point to vdp port */
    plctrl = (u32 *) GFX_CTRL_PORT;
    pldata = (u32 *) GFX_DATA_PORT;

    // previous blit not completed ?
    if (bmp_state & BMP_STAT_BLITTING)
    {
        const u16 done_i = BMP_CELLHEIGHT - save_i;
        const u16 done_j = BMP_CELLWIDTH - save_j;

        // adjust tile address
        addr_tile += ((done_i * BMP_CELLWIDTH) + done_j) * 32;
        // adjust src pointer
        src += (done_i * (BMP_YPIXPERTILE * (BMP_PITCH / 4))) + done_j;

        // set destination address for tile
        *plctrl = GFX_WRITE_VRAM_ADDR(addr_tile);

        // restore j position
        j = save_j;

        while(j--)
        {
            // send it to VRAM
            *pldata = src[(BMP_PITCH * 0) / 4];
            *pldata = src[(BMP_PITCH * 1) / 4];
            *pldata = src[(BMP_PITCH * 2) / 4];
            *pldata = src[(BMP_PITCH * 3) / 4];
            *pldata = src[(BMP_PITCH * 4) / 4];
            *pldata = src[(BMP_PITCH * 5) / 4];
            *pldata = src[(BMP_PITCH * 6) / 4];
            *pldata = src[(BMP_PITCH * 7) / 4];

            src++;
        }

        src += (7 * (BMP_PITCH / 4));

        // restore i position
        i = save_i - 1;
    }
    else
    {
        // start blit
        bmp_state |= BMP_STAT_BLITTING;
        i = BMP_CELLHEIGHT;

        // set destination address for tile
        *plctrl = GFX_WRITE_VRAM_ADDR(addr_tile);
    }

    // point to V counter
    vu8 *pbvcnt = (u8 *) GFX_HVCOUNTER_PORT;
    // scanline where we have to stop blit (end of H Blank)
    const u8 startLine = ((VDP_getScreenHeight() - BMP_HEIGHT) >> 1) - 2;

    while(i--)
    {
        j = BMP_CELLWIDTH;
        while(j--)
        {
            // (! this loop have to take less than 488 cycles else we can miss the check !)

            // blank period is finish ?
            if (*pbvcnt == startLine)
            {
                // save current position and exit
                save_i = i + 1;
                save_j = j + 1;
                return 0;
            }

            // send it to VRAM
            *pldata = src[(BMP_PITCH * 0) / 4];
            *pldata = src[(BMP_PITCH * 1) / 4];
            *pldata = src[(BMP_PITCH * 2) / 4];
            *pldata = src[(BMP_PITCH * 3) / 4];
            *pldata = src[(BMP_PITCH * 4) / 4];
            *pldata = src[(BMP_PITCH * 5) / 4];
            *pldata = src[(BMP_PITCH * 6) / 4];
            *pldata = src[(BMP_PITCH * 7) / 4];

            src++;
        }

        src += (7 * BMP_PITCH) / 4;
    }

    // blit done
    bmp_state &= ~BMP_STAT_BLITTING;

    return 1;
}

static void clearBuffer(u8 *bmp_buffer)
{
    u32 *src;
    u16 i;
    // prevent compiler to use slow CLR instruction
    const u32 v = getZeroU32();


    src = (u32*) bmp_buffer;

    i = (BMP_WIDTH * BMP_HEIGHT) / (4 * 8);
    while(i--)
    {
        *src++ = v;
        *src++ = v;
        *src++ = v;
        *src++ = v;
        *src++ = v;
        *src++ = v;
        *src++ = v;
        *src++ = v;
    }
}

void BMP_clear()
{
    clearBuffer(bmp_buffer_write);
}

u8* BMP_getWritePointer()
{
    return bmp_buffer_write;
}



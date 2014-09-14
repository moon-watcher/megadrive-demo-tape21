#include "config.h"
#include "types.h"

#include "bmp_cmn.h"
#include "bmp_intr.h"

#include "vdp.h"
#include "vdp_tile.h"
#include "vdp_bg.h"

u8 *bmp_buffer_read;
u8 *bmp_buffer_write;

u16 bmp_flags;
u16 bmp_state;

u16 BMP_getFlags()
{
    return bmp_flags;
}


u16 BMP_hasBlitInProgress()
{
    if (bmp_state & BMP_STAT_BLITTING) return 1;
    else return 0;
}

void BMP_waitBlitComplete()
{
    vu16 *pw;

    // prevent the compiler to cache it
    pw = &bmp_state;

    while (*pw & BMP_STAT_BLITTING);
}

u16 BMP_hasFlipWaiting()
{
    if (bmp_state & BMP_STAT_FLIPWAITING) return 1;
    else return 0;
}

void BMP_waitAsyncFlipComplete()
{
    vu16 *pw;

    // prevent the compiler to cache it
    pw = &bmp_state;

    while (*pw & BMP_STAT_FLIPWAITING);
}

u16 BMP_doBlankProcess()
{
    // use extended blank ?
    if (HAS_FLAG(BMP_ENABLE_EXTENDEDBLANK))
    {
        const u16 vcnt = GET_VCOUNTER;
        const u16 scrh = VDP_getScreenHeight();

        // first part of screen
        if (vcnt < (scrh >> 1))
        {
            // enable VDP
            VDP_setEnable(1);
            // prepare hint to disable VDP and doing blit process
            VDP_setHIntCounter(scrh - (VDP_getHIntCounter() + vcnt + ((scrh - BMP_HEIGHT) >> 1) + 3));
            // nothing more to do here
            return 1;
        }
        else
        {
            // disable VDP
            VDP_setEnable(0);
            // prepare hint to re-enable VDP
            VDP_setHIntCounter(((scrh - BMP_HEIGHT) >> 1) - 1);
        }
    }

    // flip requested or not complete ? --> start / continu flip
    if (bmp_state & BMP_STAT_FLIPWAITING) _bmp_doFlip();

    return 1;
}


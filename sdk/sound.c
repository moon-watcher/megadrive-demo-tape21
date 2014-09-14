#include "config.h"
#include "types.h"

#include "sound.h"

#include "z80_ctrl.h"
#include "smp_null.h"
#include "smp_null_pcm.h"


// Z80_DRIVER_PCM
// single channel 8 bits signed sample driver
///////////////////////////////////////////////////////////////

u8 SND_isPlaying_PCM()
{
    vu8 *pb;
    u8 ret;

    // load the appropried driver if not already done
    Z80_loadDriver(Z80_DRIVER_PCM, 1);

    Z80_requestBus(1);

    // point to Z80 status
    pb = (u8 *) Z80_DRV_STATUS;
    // play status
    ret = *pb & Z80_DRV_STAT_PLAYING;

    Z80_releaseBus();

    return ret;
}

void SND_startPlay_PCM(const u8 *sample, const u32 len, const u8 rate, const u8 pan, const u8 loop)
{
    vu8 *pb;
    u32 addr;

    // load the appropried driver if not already done
    Z80_loadDriver(Z80_DRIVER_PCM, 1);

    Z80_requestBus(1);

    // point to Z80 base parameters
    pb = (u8 *) Z80_DRV_PARAMS;

    addr = (u32) sample;
    // sample address (256 bytes aligned)
    pb[0] = addr >> 8;
    pb[1] = addr >> 16;
    // sample length (256 bytes aligned)
    pb[2] = len >> 8;
    pb[3] = len >> 16;
    // rate
    pb[4] = rate;
    // pan (left / right / center)
    pb[6] = pan;

    // point to Z80 command
    pb = (u8 *) Z80_DRV_COMMAND;
    // play command
    *pb |= Z80_DRV_COM_PLAY;

    // point to Z80 status
    pb = (u8 *) Z80_DRV_STATUS;

    // loop flag in status
    if (loop) pb[1] |= Z80_DRV_STAT_PLAYING;
    else pb[1] &= ~Z80_DRV_STAT_PLAYING;

    Z80_releaseBus();
}

void SND_stopPlay_PCM()
{
    vu8 *pb;
    u32 addr;

    // load the appropried driver if not already done
    Z80_loadDriver(Z80_DRIVER_PCM, 1);

    Z80_requestBus(1);

    // point to Z80 internal parameters
    pb = (u8 *) (Z80_DRV_PARAMS + 0x10);

    addr = (u32) smp_null;
    // sample address (256 bytes aligned)
    pb[0] = addr >> 8;
    pb[1] = addr >> 16;
    // sample length (256 bytes aligned)
    pb[2] = sizeof(smp_null) >> 8;
    pb[3] = sizeof(smp_null) >> 16;

    // point to Z80 status
    pb = (u8 *) Z80_DRV_STATUS;
    // remove play and loop status
    pb[0] &= ~Z80_DRV_STAT_PLAYING;
    pb[1] &= ~Z80_DRV_STAT_PLAYING;

    Z80_releaseBus();
}


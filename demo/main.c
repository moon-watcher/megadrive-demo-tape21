#include "gske.h"
#include "music.h"
#include "sega_logo.h"

#include "effect_nuclear.h"
#include "effect_cylinder.h"
#include "effect_emitter.h"
#include "effect_axelay.h"
#include "effect_mega_axelay.h"
#include "effect_sega.h"

void DoStuff(int sens, int speed, int nuc)
{
    if (nuc)
        EFFECT_sega();
    if (nuc)
        EFFECT_nuclear();
    EFFECT_axelay(sens, speed, 7000);
    EFFECT_cylinder(sens, speed*4, 5000);
    if (nuc)
        EFFECT_nuclear();
    if (!nuc)
    EFFECT_emitter(speed, 5000);
}

int main(u16 hard)
{
    GSKE_init(hard);
    SND_startPlay_PCM(music, sizeof(music), SOUND_RATE_16000, SOUND_PAN_CENTER, 0);    
    
    
    EFFECT_logo();
    DoStuff(1, 2, 1);
    DoStuff(-1, 4, 1);
    GSKE_exit3d();
    DoStuff(1, 2, 1);
    DoStuff(-1, 4, 0);
    DoStuff(1, 2, 0);
    
    EFFECT_megaAxelay();
    
    SND_stopPlay_PCM();
    GSKE_exit();
    return 0;
}

#ifndef _GSKE_H_
#define _GSKE_H_

#include "genesis.h"

u32 SND_getTime_PCM();

void GSKE_init(u16 hard);
void GSKE_exit();

void GSKE_init3d();
void GSKE_exit3d();
void GSKE_update3d();

#define GSKE_HSCROLL_Plane  0
#define GSKE_HSCROLL_Row    2
#define GSKE_HSCROLL_Line   3
#define GSKE_VSCROLL_Plane  0
#define GSKE_VSCROLL_Column 4
void GSKE_setScrollMode(u8 horizontal, u8 vertical);

#include "framebuffer.h"
#include "raster.h"
#include "scene.h"

#endif

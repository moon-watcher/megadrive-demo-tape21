/**
 * \file bmp.h
 * \brief Software bitmap engine
 * \author Stephane Dallongeville
 * \date 08/2011
 *
 * This unit provides methods to simulate bitmap mode on SEGA genesis.
 */

#ifndef _BMP_H_
#define _BMP_H_

#include "bmp_cmn.h"


/**
 * \brief
 *      Initialize the software bitmap engine.<br>
 *
 * \param flags
 *      Bitmap engine flags, see BMP_setFlags() for description.
 *
 * The software bitmap engine permit to simulate a 128x160 pixels bitmap screen with doubled X resolution.<br>
 * It uses a double buffer so you can draw to buffer while other buffer is currently blitting in video memory.<br>
 * Requires ~41 KB of memory which is dynamically allocated.
 */
void BMP_init(u16 flags);
/**
 * \brief
 *      End the software bitmap engine.
 *
 * Release memory used by software bitmap engine (~41 KB).
 */
void BMP_end();
/**
 * \brief
 *      Reset the software bitmap engine.
 *
 * Rebuild tilemap for bitmap engine and clear buffers.
 */
void BMP_reset();

/**
 * \brief
 *      Set bitmap engine flags.
 *
 * \param value
 *      BITMAP engine flags :<br>
 *      <b>BMP_ENABLE_WAITVSYNC</b> = wait VBlank before doing flip operation (see BMP_flip).<br>
 *      <b>BMP_ENABLE_ASYNCFLIP</b> = Asynch flip operation.<br>
 *         When this flag is enabled BMP_flip() will return immediatly even if flip wait for VBlank.<br>
 *         Note that this flag automatically enable BMP_ENABLE_WAITVSYNC.<br>
 *      <b>BMP_ENABLE_BLITONBLANK</b> = Process blit only during VDP blanking.<br>
 *         VRAM access is faster during blanking so this permit to optimize blit processing on best period<br>
 *         and keep the rest of time available for others processing.<br>
 *         By default on NTSC system the blanking period is very short so it takes approximately 15 frames<br>
 *         to blit the entire bitmap screen (blit is done in software).<br>
 *         Note that this flag automatically enable BMP_ENABLE_ASYNCFLIP.<br>
 *      <b>BMP_ENABLE_EXTENDEDBLANK</b> = Extend blanking period to fit bitmap height resolution (160 pixels).<br>
 *         This permit to improve blit process time (reduce 15 frames to approximately 4 frames on NTSC system).<br>
 *         Note that this flag automatically enable BMP_ENABLE_BLITONBLANK.<br>
 */
void BMP_setFlags(u16 value);

/**
 * \brief
 *      Flip bitmap buffer to screen.
 *
 * Blit the current bitmap back buffer to the screen then flip buffers<br>
 * so back buffer becomes front buffer and vice versa.
 */
void BMP_flip();

/**
 * \brief
 *      Clear bitmap buffer.
 */
void BMP_clear();

u8* BMP_getWritePointer();

#endif // _BMP_H_


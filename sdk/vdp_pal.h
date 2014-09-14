/**
 * \file vdp_pal.h
 * \brief VDP Palette support
 * \author Stephane Dallongeville
 * \date 08/2011
 *
 * This unit provides methods to manipulate the VDP Color Palette.<br/>
 * The Sega Genesis VDP has 4 palettes of 16 colors.<br/>
 * Color is defined with 3 bits for each component : 0RRR00GGG00BBB00
 */

#ifndef _VDP_PAL_H_
#define _VDP_PAL_H_


#define VDPPALETTE_REDSFT           9
#define VDPPALETTE_GREENSFT         5
#define VDPPALETTE_BLUESFT          1

#define VDPPALETTE_REDMASK          0x0E00
#define VDPPALETTE_GREENMASK        0x00E0
#define VDPPALETTE_BLUEMASK         0x000E
#define VDPPALETTE_COLORMASK        0x0EEE

/**
 * \def RGB24_TO_VDPCOLOR
 *      Convert a RGB 24 bits color to VDP color
 *
 * \param color
 *      RGB 24 bits color
 */
#define RGB24_TO_VDPCOLOR(color)    (((color >> ((2 * 4) + 4)) & VDPPALETTE_REDMASK) | ((color >> ((1 * 4) + 4)) & VDPPALETTE_GREENMASK) | ((color >> ((0 * 4) + 4)) & VDPPALETTE_BLUEMASK))

/**
 *  \brief
 *      Returns RGB color intensity.
 *
 *  \param numpal
 *      Palette number (0-3).
 *  \param numcol
 *      Color index (0-15).
 *  \return RGB intensity for the specified palette and color index.
 */
u16  VDP_getPaletteColor(u16 numpal, u16 numcol);
/**
 *  \brief
 *      Get palette.
 *
 *  \param num
 *      Palette number (0-3).
 *  \param pal
 *      Destination where to copy palette (should be 16 words long at least)
 */
void VDP_getPalette(u16 num, u16 *pal);

/**
 *  \brief
 *      Set RGB color intensity.
 *
 *  \param numpal
 *      Palette number (0-3).
 *  \param numcol
 *      Color index (0-15).
 *  \param value
 *      RGB intensity to set in the specified palette and color index.
 */
void VDP_setPaletteColor(u16 numpal, u16 numcol, u16 value);
/**
 *  \brief
 *      Set palette.
 *
 *  \param num
 *      Palette number (0-3).
 *  \param pal
 *      Source palette.
 */
inline void VDP_setPalette(u16 num, const u16 *pal);

#endif // _VDP_PAL_H_

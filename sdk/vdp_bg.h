/**
 * \file vdp_bg.h
 * \brief VDP background plan support
 * \author Stephane Dallongeville
 * \date 08/2011
 *
 * This unit provides plan A & plan B facilities :
 * - set scrolling
 * - clear plan
 * - draw text in plan
 */

#ifndef _VDP_BG_H_
#define _VDP_BG_H_


/**
 * \brief
 *      Set plan horizontal scroll.
 *
 * \param plan
 *      Plan we want to set the horizontal scroll.<br/>
 *      Accepted values are:<br/>
 *      - VDP_PLAN_A<br/>
 *      - VDP_PLAN_B<br/>
 * \param line
 *      Line (scanline) we want to set the horizontal scroll if current scroll mode supports it.<br/>
 *      3 horizontal scroll modes are supported:<br/>
 *      - Plain (whole plan)<br/>
 *      - Tile (bloc of 8 pixels)<br/>
 *      - Scanline (per pixel scroll)<br/>
 * \param value
 *      H scroll offset.
 *
 *  See VDP_setReg() function to change scroll mode.
 */
inline void VDP_setHorizontalScroll(u16 plan, u16 line, u16 value);
/**
 * \brief
 *      Set plan vertical scroll.
 *
 * \param plan
 *      Plan we want to set the vertical scroll.<br/>
 *      Accepted values are:<br/>
 *      - VDP_PLAN_A<br/>
 *      - VDP_PLAN_B<br/>
 * \param cell
 *      Cell we want to set the vertical scroll if current scroll mode supports it.
 *      2 vertical scroll modes are supported:<br/>
 *      - Plain (whole plan)<br/>
 *      - Cell (bloc of 16 pixels)<br/>
 * \param value
 *      V scroll offset.
 *
 *  See VDP_setReg() function to change scroll mode.
 */
inline void VDP_setVerticalScroll(u16 plan, u16 cell, u16 value);

/**
 * \brief
 *      Clear specified plan.
 *
 * \param plan
 *      Plan we want to clear.<br/>
 *      Accepted values are:<br/>
 *      - VDP_PLAN_A<br/>
 *      - VDP_PLAN_B<br/>
 * \param use_dma
 *      Use DMA or software clear.
 *
 *  Using DMA permit faster clear operation but can lock Z80 execution.
 */
void VDP_clearPlan(u16 plan, u8 use_dma);

#endif // _VDP_BG_H_

/**
 * \file sound.h
 * \brief Audio / Sound stuff
 * \author Stephane Dallongeville
 * \date 08/2011
 *
 * This unit provides advanced sound playback methods through differents Z80 drivers.
 *
 * <b>Z80_DRIVER_PCM</b><br>
 * Single channel 8 bits signed sample driver.<br>
 * It can play a sample (8 bit signed) from 8 Khz up to 32 Khz rate.<br>
 */

#ifndef _SOUND_H_
#define _SOUND_H_


#define SOUND_PCM_CH_AUTO   0x00

#define SOUND_PCM_CH1       Z80_DRV_CH0_SFT
#define SOUND_PCM_CH2       Z80_DRV_CH1_SFT
#define SOUND_PCM_CH3       Z80_DRV_CH2_SFT
#define SOUND_PCM_CH4       Z80_DRV_CH3_SFT

#define SOUND_PCM_CH1_MSK   Z80_DRV_CH0
#define SOUND_PCM_CH2_MSK   Z80_DRV_CH1
#define SOUND_PCM_CH3_MSK   Z80_DRV_CH2
#define SOUND_PCM_CH4_MSK   Z80_DRV_CH3

#define SOUND_RATE_32000    0
#define SOUND_RATE_22050    1
#define SOUND_RATE_16000    2
#define SOUND_RATE_13400    3
#define SOUND_RATE_11025    4
#define SOUND_RATE_8000     5

#define SOUND_PAN_LEFT      0x80
#define SOUND_PAN_RIGHT     0x40
#define SOUND_PAN_CENTER    0xC0


// Z80_DRIVER_PCM

/**
 * \brief
 *      Return play status (Single channel PCM player driver).
 *
 * \return
 *      Return non zero if PCM player is currently playing a sample
 */
u8   SND_isPlaying_PCM();
/**
 * \brief
 *      Start playing a sample (Single channel PCM player driver).<br>
 *      If a sample was currently playing then it's stopped and the new sample is played instead.
 *
 * \param sample
 *      Sample address, should be 256 bytes boundary aligned<br>
 *      SGDK automatically align resource as needed
 * \param len
 *      Size of sample in bytes, should be a multiple of 256<br>
 *      SGDK automatically adjust resource size as needed
 * \param rate
 *      Playback rate :<br>
 *      <b>SOUND_RATE_32000</b> = 32 Khz (best quality but take lot of rom space)<br>
 *      <b>SOUND_RATE_22050</b> = 22 Khz<br>
 *      <b>SOUND_RATE_16000</b> = 16 Khz<br>
 *      <b>SOUND_RATE_13400</b> = 13.4 Khz<br>
 *      <b>SOUND_RATE_11025</b> = 11 Khz<br>
 *      <b>SOUND_RATE_8000</b>  = 8 Khz (worst quality but take less rom place)<br>
 * \param pan
 *      Panning :<br>
 *      <b>SOUND_PAN_LEFT</b>   = play on left speaker<br>
 *      <b>SOUND_PAN_RIGHT</b>  = play on right speaker<br>
 *      <b>SOUND_PAN_CENTER</b> = play on both speaker<br>
 * \param loop
 *      Loop flag.<br>
 *      If non zero then the sample will be played in loop (else sample is played only once).
 */
void SND_startPlay_PCM(const u8 *sample, const u32 len, const u8 rate, const u8 pan, const u8 loop);
/**
 * \brief
 *      Stop playing (Single channel PCM player driver).<br>
 *      No effect if no sample was currently playing.
 */
void SND_stopPlay_PCM();

#endif // _SOUND_H_

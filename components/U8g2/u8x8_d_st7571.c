/*

  u8x8_d_st7571.c

  Universal 8bit Graphics Library (https://github.com/olikraus/u8g2/)

  Copyright (c) 2020, olikraus@gmail.com
  All rights reserved.

  Redistribution and use in source and binary forms, with or without modification,
  are permitted provided that the following conditions are met:

  * Redistributions of source code must retain the above copyright notice, this list
	of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above copyright notice, this
	list of conditions and the following disclaimer in the documentation and/or other
	materials provided with the distribution.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
  CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
  INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR
  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
  NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
  LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
  STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
  ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

#include "u8x8.h"
#include "esp_log.h"

/* display on */
static const uint8_t u8x8_d_st7571_128x128_powersave0_seq[] = {
	U8X8_START_TRANSFER(),
	U8X8_C(0x11), /* sleep out */
	U8X8_C(0x29), /* Display on */
	U8X8_END_TRANSFER(),
	U8X8_END() /* end of sequence */
};

/* display off */
static const uint8_t u8x8_d_st7571_128x128_powersave1_seq[] = {
	U8X8_START_TRANSFER(),
	U8X8_C(0x10), /* sleep in */
	U8X8_C(0x28), /* Display off */
	U8X8_END_TRANSFER(),
	U8X8_END() /* end of sequence */
};

/* 竖屏 0 */
static const uint8_t u8x8_d_st7571_128x128_flip0_seq[] = {
	U8X8_START_TRANSFER(), /* enable chip, delay is part of the transfer start */
	U8X8_C(0x36),		   /* segment remap a0/a1*/
	U8X8_C(0xC8),		   /* c0: scan dir normal, c8: reverse */
	U8X8_END_TRANSFER(),   /* disable chip */
	U8X8_END()			   /* end of sequence */
};

/* 90 */
static const uint8_t u8x8_d_st7571_128x128_flip1_seq[] = {
	U8X8_START_TRANSFER(), /* enable chip, delay is part of the transfer start */
	U8X8_C(0x36),		   /* segment remap a0/a1*/
	U8X8_C(0xA8),		   /* c0: scan dir normal, c8: reverse */
	U8X8_END_TRANSFER(),   /* disable chip */
	U8X8_END()			   /* end of sequence */
};

/* 180 */
static const uint8_t u8x8_d_st7571_128x128_flip2_seq[] = {
	U8X8_START_TRANSFER(), /* enable chip, delay is part of the transfer start */
	U8X8_C(0x36),		   /* segment remap a0/a1*/
	U8X8_C(0x08),		   /* c0: scan dir normal, c8: reverse */
	U8X8_END_TRANSFER(),   /* disable chip */
	U8X8_END()			   /* end of sequence */
};

/* 270 */
static const uint8_t u8x8_d_st7571_128x128_flip3_seq[] = {
	U8X8_START_TRANSFER(), /* enable chip, delay is part of the transfer start */
	U8X8_C(0x36),		   /* segment remap a0/a1*/
	U8X8_C(0x68),		   /* c0: scan dir normal, c8: reverse */
	U8X8_END_TRANSFER(),   /* disable chip */
	U8X8_END()			   /* end of sequence */
};

static const uint8_t *(st7571_128x128_flip_mode_seq[]) = {
	u8x8_d_st7571_128x128_flip0_seq,
	u8x8_d_st7571_128x128_flip1_seq,
	u8x8_d_st7571_128x128_flip2_seq,
	u8x8_d_st7571_128x128_flip3_seq,
};

/*===================================================*/

static uint8_t u8x8_d_st7571_generic(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
	uint16_t x;
	uint8_t c;
	uint8_t *ptr;
	switch (msg)
	{
	/* handled by the calling function
	case U8X8_MSG_DISPLAY_SETUP_MEMORY:
	  u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st7571_128x128_display_info);
	  break;
	*/
	/* handled by the calling function
	case U8X8_MSG_DISPLAY_INIT:
	  u8x8_d_helper_display_init(u8x8);
	  u8x8_cad_SendSequence(u8x8, u8x8_d_st7571_128x128_init_seq);
	  break;
	*/
	case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
		if (arg_int == 0)
			u8x8_cad_SendSequence(u8x8, u8x8_d_st7571_128x128_powersave0_seq);
		else
			u8x8_cad_SendSequence(u8x8, u8x8_d_st7571_128x128_powersave1_seq);
		break;
	case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
		if (arg_int < 4)
		{
			u8x8_cad_SendSequence(u8x8, st7571_128x128_flip_mode_seq[arg_int]);
			u8x8->x_offset = u8x8->display_info->default_x_offset;
		}
		else
		{
			u8x8_cad_SendSequence(u8x8, u8x8_d_st7571_128x128_flip0_seq);
			u8x8->x_offset = u8x8->display_info->flipmode_x_offset;
		}
		break;
#ifdef U8X8_WITH_SET_CONTRAST
	case U8X8_MSG_DISPLAY_SET_CONTRAST:
		u8x8_cad_StartTransfer(u8x8);
		u8x8_cad_SendCmd(u8x8, 0x081);
		u8x8_cad_SendArg(u8x8, arg_int >> 2); // 6 bit for the ST7571
		u8x8_cad_EndTransfer(u8x8);
		break;
#endif
	case U8X8_MSG_DISPLAY_DRAW_TILE:
		u8x8_cad_StartTransfer(u8x8);

		x = ((u8x8_tile_t *)arg_ptr)->x_pos;
		x *= 8;
		x += u8x8->x_offset;
		u8x8_cad_SendCmd(u8x8, 0x10 | (x >> 4));
		u8x8_cad_SendCmd(u8x8, 0x00 | ((x & 15)));
		u8x8_cad_SendCmd(u8x8, 0xb0 | (((u8x8_tile_t *)arg_ptr)->y_pos));

		ESP_LOGW("st7735s", "U8X8_MSG_DISPLAY_DRAW_TILE, arg_int: %d, cnt: %d, x: %d, y: %d", arg_int, ((u8x8_tile_t *)arg_ptr)->cnt,
							((u8x8_tile_t *)arg_ptr)->x_pos, ((u8x8_tile_t *)arg_ptr)->y_pos);

		do
		{
			c = ((u8x8_tile_t *)arg_ptr)->cnt;
			ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
			u8x8_cad_SendData(u8x8, c * 8, ptr);
			arg_int--;
		} while (arg_int > 0);

		u8x8_cad_EndTransfer(u8x8);
		break;
	default:
		return 0;
	}
	return 1;
}

/*===================================================*/

/* QT-2832TSWUG02/ZJY-2832TSWZG02 */
/* fixed the 0x40 and 0x48 commands, verified with FlipMode example: All ok */
static const uint8_t u8x8_d_st7571_128x128_init_seq[] = {

	U8X8_START_TRANSFER(), /* enable chip, delay is part of the transfer start */

	// LCD Init For 1.44Inch LCD Panel with ST7735R.
	U8X8_C(0x11), // Sleep exit
	U8X8_C(0x28),
	U8X8_DLY(100),

	// ST7735R Frame Rate
	U8X8_C(0xB1),
	U8X8_D1(0x01),
	U8X8_D1(0x2C),
	U8X8_D1(0x2D),

	U8X8_C(0xB2),
	U8X8_D1(0x01),
	U8X8_D1(0x2C),
	U8X8_D1(0x2D),

	U8X8_C(0xB3),
	U8X8_D1(0x01),
	U8X8_D1(0x2C),
	U8X8_D1(0x2D),
	U8X8_D1(0x01),
	U8X8_D1(0x2C),
	U8X8_D1(0x2D),

	U8X8_C(0xB4), // Column inversion
	U8X8_D1(0x07),

	// ST7735R Power Sequence
	U8X8_C(0xC0),
	U8X8_D1(0xA2),
	U8X8_D1(0x02),
	U8X8_D1(0x84),
	U8X8_C(0xC1),
	U8X8_D1(0xC5),

	U8X8_C(0xC2),
	U8X8_D1(0x0A),
	U8X8_D1(0x00),

	U8X8_C(0xC3),
	U8X8_D1(0x8A),
	U8X8_D1(0x2A),
	U8X8_C(0xC4),
	U8X8_D1(0x8A),
	U8X8_D1(0xEE),

	U8X8_C(0xC5), // VCOM
	U8X8_D1(0x0E),

	U8X8_C(0x36), // MX, MY, RGB mode
	U8X8_D1(0xC8),

	// ST7735R Gamma Sequence
	U8X8_C(0xe0),
	U8X8_D1(0x0f),
	U8X8_D1(0x1a),
	U8X8_D1(0x0f),
	U8X8_D1(0x18),
	U8X8_D1(0x2f),
	U8X8_D1(0x28),
	U8X8_D1(0x20),
	U8X8_D1(0x22),
	U8X8_D1(0x1f),
	U8X8_D1(0x1b),
	U8X8_D1(0x23),
	U8X8_D1(0x37),
	U8X8_D1(0x00),
	U8X8_D1(0x07),
	U8X8_D1(0x02),
	U8X8_D1(0x10),

	U8X8_C(0xe1),
	U8X8_D1(0x0f),
	U8X8_D1(0x1b),
	U8X8_D1(0x0f),
	U8X8_D1(0x17),
	U8X8_D1(0x33),
	U8X8_D1(0x2c),
	U8X8_D1(0x29),
	U8X8_D1(0x2e),
	U8X8_D1(0x30),
	U8X8_D1(0x30),
	U8X8_D1(0x39),
	U8X8_D1(0x3f),
	U8X8_D1(0x00),
	U8X8_D1(0x07),
	U8X8_D1(0x03),
	U8X8_D1(0x10),

	U8X8_C(0x2a),
	U8X8_D1(0x00),
	U8X8_D1(0x00),
	U8X8_D1(0x00),
	U8X8_D1(0x7f),

	U8X8_C(0x2b),
	U8X8_D1(0x00),
	U8X8_D1(0x00),
	U8X8_D1(0x00),
	U8X8_D1(0x9f),

	U8X8_C(0xF0), // Enable test command
	U8X8_D1(0x01),
	U8X8_C(0xF6), // Disable ram power save mode
	U8X8_D1(0x00),

	U8X8_C(0x3A), // 65k mode
	U8X8_D1(0x05),

	// U8X8_C(0x29), //Display on
	U8X8_END_TRANSFER(),
	U8X8_END() /* end of sequence */
};

static const u8x8_display_info_t u8x8_st7571_128x128_display_info =
	{
		/* chip_enable_level = */ 0,
		/* chip_disable_level = */ 1,

		/* post_chip_enable_wait_ns = */ 20,
		/* pre_chip_disable_wait_ns = */ 20,
		/* reset_pulse_width_ms = */ 5,
		/* post_reset_wait_ms = */ 5,	/**/
		/* sda_setup_time_ns = */ 20,	/* */
		/* sck_pulse_width_ns = */ 40,	/*  */
		/* sck_clock_hz = */ 1000000UL, /* since Arduino 1.6.0, the SPI bus speed in Hz. Should be  1000000000/sck_pulse_width_ns */
		/* spi_mode = */ 0,				/* active high, rising edge */
		/* i2c_bus_clock_100kHz = */ 4, /* 400KHz */
		/* data_setup_time_ns = */ 15,
		/* write_pulse_width_ns = */ 70,
		/* tile_width = */ 16,
		/* tile_height = */ 16,
		/* default_x_offset = */ 0,
		/* flipmode_x_offset = */ 0,
		/* pixel_width = */ 128,
		/* pixel_height = */ 128};

uint8_t u8x8_d_st7571_128x128(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{

	if (u8x8_d_st7571_generic(u8x8, msg, arg_int, arg_ptr) != 0)
		return 1;

	switch (msg)
	{
	case U8X8_MSG_DISPLAY_INIT:
		u8x8_d_helper_display_init(u8x8);
		u8x8_cad_SendSequence(u8x8, u8x8_d_st7571_128x128_init_seq);
		break;
	case U8X8_MSG_DISPLAY_SETUP_MEMORY:
		ESP_LOGW("st7735", "U8X8_MSG_DISPLAY_SETUP_MEMORY");
		u8x8_d_helper_display_setup_memory(u8x8, &u8x8_st7571_128x128_display_info);
		break;
	default:
		return 0;
	}
	return 1;
}
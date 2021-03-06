/*
 * Copyright (C) 2010 Mans Rullgard <mans@mansr.com>
 *
 * This file is part of FFmpeg.
 *
 * FFmpeg is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * FFmpeg is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with FFmpeg; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#ifndef AVCODEC_ARM_VP56_ARITH_H
#define AVCODEC_ARM_VP56_ARITH_H

#if HAVE_ARMV6 && HAVE_INLINE_ASM

#define vp56_rac_get_prob vp56_rac_get_prob_armv6
static inline int vp56_rac_get_prob_armv6(VP56RangeCoder *c, int pr)
{
	unsigned shift     = ff_vp56_norm_shift[c->high];
	unsigned code_word = c->code_word << shift;
	unsigned high      = c->high << shift;
	unsigned bit;

	__asm__ volatile ("adds    %3,  %3,  %0           \n"
	                  "cmpcs   %7,  %4                \n"
	                  "ldrcsh  %2,  [%4], #2          \n"
	                  "rsb     %0,  %6,  #256         \n"
	                  "smlabb  %0,  %5,  %6,  %0      \n"
	                  "rev16cs %2,  %2                \n"
	                  "orrcs   %1,  %1,  %2,  lsl %3  \n"
	                  "subcs   %3,  %3,  #16          \n"
	                  "lsr     %0,  %0,  #8           \n"
	                  "cmp     %1,  %0,  lsl #16      \n"
	                  "subge   %1,  %1,  %0,  lsl #16 \n"
	                  "subge   %0,  %5,  %0           \n"
	                  "movge   %2,  #1                \n"
	                  "movlt   %2,  #0                \n"
	                  : "=&r"(c->high), "=&r"(c->code_word), "=&r"(bit),
	                  "+&r"(c->bits), "+&r"(c->buffer)
	                  : "r"(high), "r"(pr), "r"(c->end - 1),
	                  "0"(shift), "1"(code_word));

	return bit;
}

#define vp56_rac_get_prob_branchy vp56_rac_get_prob_branchy_armv6
static inline int vp56_rac_get_prob_branchy_armv6(VP56RangeCoder *c, int pr)
{
	unsigned shift     = ff_vp56_norm_shift[c->high];
	unsigned code_word = c->code_word << shift;
	unsigned high      = c->high << shift;
	unsigned low;
	unsigned tmp;

	__asm__ volatile ("adds    %3,  %3,  %0           \n"
	                  "cmpcs   %7,  %4                \n"
	                  "ldrcsh  %2,  [%4], #2          \n"
	                  "rsb     %0,  %6,  #256         \n"
	                  "smlabb  %0,  %5,  %6,  %0      \n"
	                  "rev16cs %2,  %2                \n"
	                  "orrcs   %1,  %1,  %2,  lsl %3  \n"
	                  "subcs   %3,  %3,  #16          \n"
	                  "lsr     %0,  %0,  #8           \n"
	                  "lsl     %2,  %0,  #16          \n"
	                  : "=&r"(low), "+&r"(code_word), "=&r"(tmp),
	                  "+&r"(c->bits), "+&r"(c->buffer)
	                  : "r"(high), "r"(pr), "r"(c->end - 1), "0"(shift));

	if (code_word >= tmp)
	{
		c->high      = high - low;
		c->code_word = code_word - tmp;
		return 1;
	}

	c->high      = low;
	c->code_word = code_word;
	return 0;
}

#endif

#endif

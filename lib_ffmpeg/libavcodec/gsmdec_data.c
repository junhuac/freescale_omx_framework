/*
 * gsm 06.10 decoder data
 * Copyright (c) 2010 Reimar Döffinger <Reimar.Doeffinger@gmx.de>
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

#include <stdint.h>
#include "gsmdec_data.h"

const uint16_t ff_gsm_long_term_gain_tab[4] =
{
	3277, 11469, 21299, 32767
};

const int16_t ff_gsm_dequant_tab[64][8] =
{
	{   -28,    -20,    -12,     -4,      4,     12,     20,     28},
	{   -56,    -40,    -24,     -8,      8,     24,     40,     56},
	{   -84,    -60,    -36,    -12,     12,     36,     60,     84},
	{  -112,    -80,    -48,    -16,     16,     48,     80,    112},
	{  -140,   -100,    -60,    -20,     20,     60,    100,    140},
	{  -168,   -120,    -72,    -24,     24,     72,    120,    168},
	{  -196,   -140,    -84,    -28,     28,     84,    140,    196},
	{  -224,   -160,    -96,    -32,     32,     96,    160,    224},
	{  -252,   -180,   -108,    -36,     36,    108,    180,    252},
	{  -280,   -200,   -120,    -40,     40,    120,    200,    280},
	{  -308,   -220,   -132,    -44,     44,    132,    220,    308},
	{  -336,   -240,   -144,    -48,     48,    144,    240,    336},
	{  -364,   -260,   -156,    -52,     52,    156,    260,    364},
	{  -392,   -280,   -168,    -56,     56,    168,    280,    392},
	{  -420,   -300,   -180,    -60,     60,    180,    300,    420},
	{  -448,   -320,   -192,    -64,     64,    192,    320,    448},
	{  -504,   -360,   -216,    -72,     72,    216,    360,    504},
	{  -560,   -400,   -240,    -80,     80,    240,    400,    560},
	{  -616,   -440,   -264,    -88,     88,    264,    440,    616},
	{  -672,   -480,   -288,    -96,     96,    288,    480,    672},
	{  -728,   -520,   -312,   -104,    104,    312,    520,    728},
	{  -784,   -560,   -336,   -112,    112,    336,    560,    784},
	{  -840,   -600,   -360,   -120,    120,    360,    600,    840},
	{  -896,   -640,   -384,   -128,    128,    384,    640,    896},
	{ -1008,   -720,   -432,   -144,    144,    432,    720,   1008},
	{ -1120,   -800,   -480,   -160,    160,    480,    800,   1120},
	{ -1232,   -880,   -528,   -176,    176,    528,    880,   1232},
	{ -1344,   -960,   -576,   -192,    192,    576,    960,   1344},
	{ -1456,  -1040,   -624,   -208,    208,    624,   1040,   1456},
	{ -1568,  -1120,   -672,   -224,    224,    672,   1120,   1568},
	{ -1680,  -1200,   -720,   -240,    240,    720,   1200,   1680},
	{ -1792,  -1280,   -768,   -256,    256,    768,   1280,   1792},
	{ -2016,  -1440,   -864,   -288,    288,    864,   1440,   2016},
	{ -2240,  -1600,   -960,   -320,    320,    960,   1600,   2240},
	{ -2464,  -1760,  -1056,   -352,    352,   1056,   1760,   2464},
	{ -2688,  -1920,  -1152,   -384,    384,   1152,   1920,   2688},
	{ -2912,  -2080,  -1248,   -416,    416,   1248,   2080,   2912},
	{ -3136,  -2240,  -1344,   -448,    448,   1344,   2240,   3136},
	{ -3360,  -2400,  -1440,   -480,    480,   1440,   2400,   3360},
	{ -3584,  -2560,  -1536,   -512,    512,   1536,   2560,   3584},
	{ -4032,  -2880,  -1728,   -576,    576,   1728,   2880,   4032},
	{ -4480,  -3200,  -1920,   -640,    640,   1920,   3200,   4480},
	{ -4928,  -3520,  -2112,   -704,    704,   2112,   3520,   4928},
	{ -5376,  -3840,  -2304,   -768,    768,   2304,   3840,   5376},
	{ -5824,  -4160,  -2496,   -832,    832,   2496,   4160,   5824},
	{ -6272,  -4480,  -2688,   -896,    896,   2688,   4480,   6272},
	{ -6720,  -4800,  -2880,   -960,    960,   2880,   4800,   6720},
	{ -7168,  -5120,  -3072,  -1024,   1024,   3072,   5120,   7168},
	{ -8063,  -5759,  -3456,  -1152,   1152,   3456,   5760,   8064},
	{ -8959,  -6399,  -3840,  -1280,   1280,   3840,   6400,   8960},
	{ -9855,  -7039,  -4224,  -1408,   1408,   4224,   7040,   9856},
	{-10751,  -7679,  -4608,  -1536,   1536,   4608,   7680,  10752},
	{-11647,  -8319,  -4992,  -1664,   1664,   4992,   8320,  11648},
	{-12543,  -8959,  -5376,  -1792,   1792,   5376,   8960,  12544},
	{-13439,  -9599,  -5760,  -1920,   1920,   5760,   9600,  13440},
	{-14335, -10239,  -6144,  -2048,   2048,   6144,  10240,  14336},
	{-16127, -11519,  -6912,  -2304,   2304,   6912,  11519,  16127},
	{-17919, -12799,  -7680,  -2560,   2560,   7680,  12799,  17919},
	{-19711, -14079,  -8448,  -2816,   2816,   8448,  14079,  19711},
	{-21503, -15359,  -9216,  -3072,   3072,   9216,  15359,  21503},
	{-23295, -16639,  -9984,  -3328,   3328,   9984,  16639,  23295},
	{-25087, -17919, -10752,  -3584,   3584,  10752,  17919,  25087},
	{-26879, -19199, -11520,  -3840,   3840,  11520,  19199,  26879},
	{-28671, -20479, -12288,  -4096,   4096,  12288,  20479,  28671}
};

/*
 * Chinese AVS video (AVS1-P2, JiZhun profile) decoder.
 * Copyright (c) 2006  Stefan Gehrer <stefan.gehrer@gmx.de>
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

#ifndef AVCODEC_CAVSDATA_H
#define AVCODEC_CAVSDATA_H

#include "cavs.h"

const uint8_t ff_cavs_partition_flags[30] =
{
	0,                                 //I_8X8
	0,                                 //P_SKIP
	0,                                 //P_16X16
	SPLITH,        //P_16X8
	SPLITV, //P_8X16
	SPLITH|SPLITV, //P_8X8
	SPLITH|SPLITV, //B_SKIP
	SPLITH|SPLITV, //B_DIRECT
	0,                                 //B_FWD_16X16
	0,                                 //B_BWD_16X16
	0,                                 //B_SYM_16X16
	FWD0|FWD1          |SPLITH,
	FWD0|FWD1                 |SPLITV,
	BWD0|BWD1          |SPLITH,
	BWD0|BWD1                 |SPLITV,
	FWD0|BWD1          |SPLITH,
	FWD0|BWD1                 |SPLITV,
	BWD0|FWD1          |SPLITH,
	BWD0|FWD1                 |SPLITV,
	FWD0|FWD1     |SYM1|SPLITH,
	FWD0|FWD1     |SYM1       |SPLITV,
	BWD0|FWD1     |SYM1|SPLITH,
	BWD0|FWD1     |SYM1       |SPLITV,
	FWD0|FWD1|SYM0     |SPLITH,
	FWD0|FWD1|SYM0            |SPLITV,
	FWD0|BWD1|SYM0     |SPLITH,
	FWD0|BWD1|SYM0            |SPLITV,
	FWD0|FWD1|SYM0|SYM1|SPLITH,
	FWD0|FWD1|SYM0|SYM1       |SPLITV,
	SPLITH|SPLITV, //B_8X8 = 29
};

const uint8_t ff_cavs_scan3x3[4] = {4,5,7,8};

const uint8_t ff_cavs_chroma_qp[64] =
{
	0,  1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15,
	16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,
	32,33,34,35,36,37,38,39,40,41,42,42,43,43,44,44,
	45,45,46,46,47,47,48,48,48,49,49,49,50,50,50,51
};

const uint8_t ff_cavs_dequant_shift[64] =
{
	14,14,14,14,14,14,14,14,
	13,13,13,13,13,13,13,13,
	13,12,12,12,12,12,12,12,
	11,11,11,11,11,11,11,11,
	11,10,10,10,10,10,10,10,
	10, 9, 9, 9, 9, 9, 9, 9,
	9, 8, 8, 8, 8, 8, 8, 8,
	7, 7, 7, 7, 7, 7, 7, 7
};

const uint16_t ff_cavs_dequant_mul[64] =
{
	32768,36061,38968,42495,46341,50535,55437,60424,
	32932,35734,38968,42495,46177,50535,55109,59933,
	65535,35734,38968,42577,46341,50617,55027,60097,
	32809,35734,38968,42454,46382,50576,55109,60056,
	65535,35734,38968,42495,46320,50515,55109,60076,
	65535,35744,38968,42495,46341,50535,55099,60087,
	65535,35734,38973,42500,46341,50535,55109,60097,
	32771,35734,38965,42497,46341,50535,55109,60099
};

/** mark block as unavailable, i.e. out of picture
    or not yet decoded */
const cavs_vector ff_cavs_un_mv    = {0,0,1,NOT_AVAIL};

/** mark block as "no prediction from this direction"
    e.g. forward motion vector in BWD partition */
const cavs_vector ff_cavs_dir_mv   = {0,0,1,REF_DIR};

/** mark block as using intra prediction */
const cavs_vector ff_cavs_intra_mv = {0,0,1,REF_INTRA};

#define EOB 0,0,0

const struct dec_2dvlc ff_cavs_intra_dec[7] =
{
	{
		{
			//level / run / table_inc
			{  1, 1, 1},{ -1, 1, 1},{  1, 2, 1},{ -1, 2, 1},{  1, 3, 1},{ -1, 3, 1},
			{  1, 4, 1},{ -1, 4, 1},{  1, 5, 1},{ -1, 5, 1},{  1, 6, 1},{ -1, 6, 1},
			{  1, 7, 1},{ -1, 7, 1},{  1, 8, 1},{ -1, 8, 1},{  1, 9, 1},{ -1, 9, 1},
			{  1,10, 1},{ -1,10, 1},{  1,11, 1},{ -1,11, 1},{  2, 1, 2},{ -2, 1, 2},
			{  1,12, 1},{ -1,12, 1},{  1,13, 1},{ -1,13, 1},{  1,14, 1},{ -1,14, 1},
			{  1,15, 1},{ -1,15, 1},{  2, 2, 2},{ -2, 2, 2},{  1,16, 1},{ -1,16, 1},
			{  1,17, 1},{ -1,17, 1},{  3, 1, 3},{ -3, 1, 3},{  1,18, 1},{ -1,18, 1},
			{  1,19, 1},{ -1,19, 1},{  2, 3, 2},{ -2, 3, 2},{  1,20, 1},{ -1,20, 1},
			{  1,21, 1},{ -1,21, 1},{  2, 4, 2},{ -2, 4, 2},{  1,22, 1},{ -1,22, 1},
			{  2, 5, 2},{ -2, 5, 2},{  1,23, 1},{ -1,23, 1},{   EOB   }
		},
		//level_add
		{
			0, 4, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2,-1,-1,-1
		},
		2, //golomb_order
		0, //inc_limit
		23, //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  2, 1, 1},{ -2, 1, 1},
			{  1, 3, 0},{ -1, 3, 0},{   EOB   },{  1, 4, 0},{ -1, 4, 0},{  1, 5, 0},
			{ -1, 5, 0},{  1, 6, 0},{ -1, 6, 0},{  3, 1, 2},{ -3, 1, 2},{  2, 2, 1},
			{ -2, 2, 1},{  1, 7, 0},{ -1, 7, 0},{  1, 8, 0},{ -1, 8, 0},{  1, 9, 0},
			{ -1, 9, 0},{  2, 3, 1},{ -2, 3, 1},{  4, 1, 2},{ -4, 1, 2},{  1,10, 0},
			{ -1,10, 0},{  1,11, 0},{ -1,11, 0},{  2, 4, 1},{ -2, 4, 1},{  3, 2, 2},
			{ -3, 2, 2},{  1,12, 0},{ -1,12, 0},{  2, 5, 1},{ -2, 5, 1},{  5, 1, 3},
			{ -5, 1, 3},{  1,13, 0},{ -1,13, 0},{  2, 6, 1},{ -2, 6, 1},{  1,14, 0},
			{ -1,14, 0},{  2, 7, 1},{ -2, 7, 1},{  2, 8, 1},{ -2, 8, 1},{  3, 3, 2},
			{ -3, 3, 2},{  6, 1, 3},{ -6, 1, 3},{  1,15, 0},{ -1,15, 0}
		},
		//level_add
		{
			0, 7, 4, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		1, //inc_limit
		15, //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  1, 2, 0},{ -1, 2, 0},
			{  3, 1, 1},{ -3, 1, 1},{   EOB   },{  1, 3, 0},{ -1, 3, 0},{  2, 2, 0},
			{ -2, 2, 0},{  4, 1, 1},{ -4, 1, 1},{  1, 4, 0},{ -1, 4, 0},{  5, 1, 2},
			{ -5, 1, 2},{  1, 5, 0},{ -1, 5, 0},{  3, 2, 1},{ -3, 2, 1},{  2, 3, 0},
			{ -2, 3, 0},{  1, 6, 0},{ -1, 6, 0},{  6, 1, 2},{ -6, 1, 2},{  2, 4, 0},
			{ -2, 4, 0},{  1, 7, 0},{ -1, 7, 0},{  4, 2, 1},{ -4, 2, 1},{  7, 1, 2},
			{ -7, 1, 2},{  3, 3, 1},{ -3, 3, 1},{  2, 5, 0},{ -2, 5, 0},{  1, 8, 0},
			{ -1, 8, 0},{  2, 6, 0},{ -2, 6, 0},{  8, 1, 3},{ -8, 1, 3},{  1, 9, 0},
			{ -1, 9, 0},{  5, 2, 2},{ -5, 2, 2},{  3, 4, 1},{ -3, 4, 1},{  2, 7, 0},
			{ -2, 7, 0},{  9, 1, 3},{ -9, 1, 3},{  1,10, 0},{ -1,10, 0}
		},
		//level_add
		{
			0,10, 6, 4, 4, 3, 3, 3, 2, 2, 2,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		2, //inc_limit
		10, //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},{ -3, 1, 0},
			{  1, 2, 0},{ -1, 2, 0},{   EOB   },{  4, 1, 0},{ -4, 1, 0},{  5, 1, 1},
			{ -5, 1, 1},{  2, 2, 0},{ -2, 2, 0},{  1, 3, 0},{ -1, 3, 0},{  6, 1, 1},
			{ -6, 1, 1},{  3, 2, 0},{ -3, 2, 0},{  7, 1, 1},{ -7, 1, 1},{  1, 4, 0},
			{ -1, 4, 0},{  8, 1, 2},{ -8, 1, 2},{  2, 3, 0},{ -2, 3, 0},{  4, 2, 0},
			{ -4, 2, 0},{  1, 5, 0},{ -1, 5, 0},{  9, 1, 2},{ -9, 1, 2},{  5, 2, 1},
			{ -5, 2, 1},{  2, 4, 0},{ -2, 4, 0},{ 10, 1, 2},{-10, 1, 2},{  3, 3, 0},
			{ -3, 3, 0},{  1, 6, 0},{ -1, 6, 0},{ 11, 1, 3},{-11, 1, 3},{  6, 2, 1},
			{ -6, 2, 1},{  1, 7, 0},{ -1, 7, 0},{  2, 5, 0},{ -2, 5, 0},{  3, 4, 0},
			{ -3, 4, 0},{ 12, 1, 3},{-12, 1, 3},{  4, 3, 0},{ -4, 3, 0}
		},
		//level_add
		{
			0,13, 7, 5, 4, 3, 2, 2,-1,-1,-1 -1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		4, //inc_limit
		7, //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},{ -3, 1, 0},
			{   EOB   },{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  6, 1, 0},
			{ -6, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  7, 1, 0},{ -7, 1, 0},{  8, 1, 1},
			{ -8, 1, 1},{  2, 2, 0},{ -2, 2, 0},{  9, 1, 1},{ -9, 1, 1},{ 10, 1, 1},
			{-10, 1, 1},{  1, 3, 0},{ -1, 3, 0},{  3, 2, 0},{ -3, 2, 0},{ 11, 1, 2},
			{-11, 1, 2},{  4, 2, 0},{ -4, 2, 0},{ 12, 1, 2},{-12, 1, 2},{ 13, 1, 2},
			{-13, 1, 2},{  5, 2, 0},{ -5, 2, 0},{  1, 4, 0},{ -1, 4, 0},{  2, 3, 0},
			{ -2, 3, 0},{ 14, 1, 2},{-14, 1, 2},{  6, 2, 0},{ -6, 2, 0},{ 15, 1, 2},
			{-15, 1, 2},{ 16, 1, 2},{-16, 1, 2},{  3, 3, 0},{ -3, 3, 0},{  1, 5, 0},
			{ -1, 5, 0},{  7, 2, 0},{ -7, 2, 0},{ 17, 1, 2},{-17, 1, 2}
		},
		//level_add
		{
			0,18, 8, 4, 2, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		7, //inc_limit
		5, //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  6, 1, 0},
			{ -6, 1, 0},{  7, 1, 0},{ -7, 1, 0},{  8, 1, 0},{ -8, 1, 0},{  9, 1, 0},
			{ -9, 1, 0},{ 10, 1, 0},{-10, 1, 0},{  1, 2, 0},{ -1, 2, 0},{ 11, 1, 1},
			{-11, 1, 1},{ 12, 1, 1},{-12, 1, 1},{ 13, 1, 1},{-13, 1, 1},{  2, 2, 0},
			{ -2, 2, 0},{ 14, 1, 1},{-14, 1, 1},{ 15, 1, 1},{-15, 1, 1},{  3, 2, 0},
			{ -3, 2, 0},{ 16, 1, 1},{-16, 1, 1},{  1, 3, 0},{ -1, 3, 0},{ 17, 1, 1},
			{-17, 1, 1},{  4, 2, 0},{ -4, 2, 0},{ 18, 1, 1},{-18, 1, 1},{  5, 2, 0},
			{ -5, 2, 0},{ 19, 1, 1},{-19, 1, 1},{ 20, 1, 1},{-20, 1, 1},{  6, 2, 0},
			{ -6, 2, 0},{ 21, 1, 1},{-21, 1, 1},{  2, 3, 0},{ -2, 3, 0}
		},
		//level_add
		{
			0,22, 7, 3,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		10, //inc_limit
		3, //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  6, 1, 0},
			{ -6, 1, 0},{  7, 1, 0},{ -7, 1, 0},{  8, 1, 0},{ -8, 1, 0},{  9, 1, 0},
			{ -9, 1, 0},{ 10, 1, 0},{-10, 1, 0},{ 11, 1, 0},{-11, 1, 0},{ 12, 1, 0},
			{-12, 1, 0},{ 13, 1, 0},{-13, 1, 0},{ 14, 1, 0},{-14, 1, 0},{ 15, 1, 0},
			{-15, 1, 0},{ 16, 1, 0},{-16, 1, 0},{  1, 2, 0},{ -1, 2, 0},{ 17, 1, 0},
			{-17, 1, 0},{ 18, 1, 0},{-18, 1, 0},{ 19, 1, 0},{-19, 1, 0},{ 20, 1, 0},
			{-20, 1, 0},{ 21, 1, 0},{-21, 1, 0},{  2, 2, 0},{ -2, 2, 0},{ 22, 1, 0},
			{-22, 1, 0},{ 23, 1, 0},{-23, 1, 0},{ 24, 1, 0},{-24, 1, 0},{ 25, 1, 0},
			{-25, 1, 0},{  3, 2, 0},{ -3, 2, 0},{ 26, 1, 0},{-26, 1, 0}
		},
		//level_add
		{
			0,27, 4,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		INT_MAX, //inc_limit
		2, //max_run
	}
};

const struct dec_2dvlc ff_cavs_inter_dec[7] =
{
	{
		{
			//level / run
			{  1, 1, 1},{ -1, 1, 1},{  1, 2, 1},{ -1, 2, 1},{  1, 3, 1},{ -1, 3, 1},
			{  1, 4, 1},{ -1, 4, 1},{  1, 5, 1},{ -1, 5, 1},{  1, 6, 1},{ -1, 6, 1},
			{  1, 7, 1},{ -1, 7, 1},{  1, 8, 1},{ -1, 8, 1},{  1, 9, 1},{ -1, 9, 1},
			{  1,10, 1},{ -1,10, 1},{  1,11, 1},{ -1,11, 1},{  1,12, 1},{ -1,12, 1},
			{  1,13, 1},{ -1,13, 1},{  2, 1, 2},{ -2, 1, 2},{  1,14, 1},{ -1,14, 1},
			{  1,15, 1},{ -1,15, 1},{  1,16, 1},{ -1,16, 1},{  1,17, 1},{ -1,17, 1},
			{  1,18, 1},{ -1,18, 1},{  1,19, 1},{ -1,19, 1},{  3, 1, 3},{ -3, 1, 3},
			{  1,20, 1},{ -1,20, 1},{  1,21, 1},{ -1,21, 1},{  2, 2, 2},{ -2, 2, 2},
			{  1,22, 1},{ -1,22, 1},{  1,23, 1},{ -1,23, 1},{  1,24, 1},{ -1,24, 1},
			{  1,25, 1},{ -1,25, 1},{  1,26, 1},{ -1,26, 1},{   EOB   }
		},
		//level_add
		{
			0, 4, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 2, 2, 2
		},
		3, //golomb_order
		0, //inc_limit
		26 //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{   EOB   },{  1, 2, 0},{ -1, 2, 0},{  1, 3, 0},
			{ -1, 3, 0},{  1, 4, 0},{ -1, 4, 0},{  1, 5, 0},{ -1, 5, 0},{  1, 6, 0},
			{ -1, 6, 0},{  2, 1, 1},{ -2, 1, 1},{  1, 7, 0},{ -1, 7, 0},{  1, 8, 0},
			{ -1, 8, 0},{  1, 9, 0},{ -1, 9, 0},{  1,10, 0},{ -1,10, 0},{  2, 2, 1},
			{ -2, 2, 1},{  1,11, 0},{ -1,11, 0},{  1,12, 0},{ -1,12, 0},{  3, 1, 2},
			{ -3, 1, 2},{  1,13, 0},{ -1,13, 0},{  1,14, 0},{ -1,14, 0},{  2, 3, 1},
			{ -2, 3, 1},{  1,15, 0},{ -1,15, 0},{  2, 4, 1},{ -2, 4, 1},{  1,16, 0},
			{ -1,16, 0},{  2, 5, 1},{ -2, 5, 1},{  1,17, 0},{ -1,17, 0},{  4, 1, 3},
			{ -4, 1, 3},{  2, 6, 1},{ -2, 6, 1},{  1,18, 0},{ -1,18, 0},{  1,19, 0},
			{ -1,19, 0},{  2, 7, 1},{ -2, 7, 1},{  3, 2, 2},{ -3, 2, 2}
		},
		//level_add
		{
			0, 5, 4, 3, 3, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		1, //inc_limit
		19 //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{   EOB   },{  1, 2, 0},{ -1, 2, 0},{  2, 1, 0},
			{ -2, 1, 0},{  1, 3, 0},{ -1, 3, 0},{  1, 4, 0},{ -1, 4, 0},{  3, 1, 1},
			{ -3, 1, 1},{  2, 2, 0},{ -2, 2, 0},{  1, 5, 0},{ -1, 5, 0},{  1, 6, 0},
			{ -1, 6, 0},{  1, 7, 0},{ -1, 7, 0},{  2, 3, 0},{ -2, 3, 0},{  4, 1, 2},
			{ -4, 1, 2},{  1, 8, 0},{ -1, 8, 0},{  3, 2, 1},{ -3, 2, 1},{  2, 4, 0},
			{ -2, 4, 0},{  1, 9, 0},{ -1, 9, 0},{  1,10, 0},{ -1,10, 0},{  5, 1, 2},
			{ -5, 1, 2},{  2, 5, 0},{ -2, 5, 0},{  1,11, 0},{ -1,11, 0},{  2, 6, 0},
			{ -2, 6, 0},{  1,12, 0},{ -1,12, 0},{  3, 3, 1},{ -3, 3, 1},{  6, 1, 2},
			{ -6, 1, 2},{  4, 2, 2},{ -4, 2, 2},{  1,13, 0},{ -1,13, 0},{  2, 7, 0},
			{ -2, 7, 0},{  3, 4, 1},{ -3, 4, 1},{  1,14, 0},{ -1,14, 0}
		},
		//level_add
		{
			0, 7, 5, 4, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		2, //inc_limit
		14 //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{   EOB   },{  2, 1, 0},{ -2, 1, 0},{  1, 2, 0},
			{ -1, 2, 0},{  3, 1, 0},{ -3, 1, 0},{  1, 3, 0},{ -1, 3, 0},{  2, 2, 0},
			{ -2, 2, 0},{  4, 1, 1},{ -4, 1, 1},{  1, 4, 0},{ -1, 4, 0},{  5, 1, 1},
			{ -5, 1, 1},{  1, 5, 0},{ -1, 5, 0},{  3, 2, 0},{ -3, 2, 0},{  2, 3, 0},
			{ -2, 3, 0},{  1, 6, 0},{ -1, 6, 0},{  6, 1, 1},{ -6, 1, 1},{  2, 4, 0},
			{ -2, 4, 0},{  1, 7, 0},{ -1, 7, 0},{  4, 2, 1},{ -4, 2, 1},{  7, 1, 2},
			{ -7, 1, 2},{  3, 3, 0},{ -3, 3, 0},{  1, 8, 0},{ -1, 8, 0},{  2, 5, 0},
			{ -2, 5, 0},{  8, 1, 2},{ -8, 1, 2},{  1, 9, 0},{ -1, 9, 0},{  3, 4, 0},
			{ -3, 4, 0},{  2, 6, 0},{ -2, 6, 0},{  5, 2, 1},{ -5, 2, 1},{  1,10, 0},
			{ -1,10, 0},{  9, 1, 2},{ -9, 1, 2},{  4, 3, 1},{ -4, 3, 1}
		},
		//level_add
		{
			0,10, 6, 5, 4, 3, 3, 2, 2, 2, 2,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		3, //inc_limit
		10 //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{   EOB   },{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},
			{ -5, 1, 0},{  2, 2, 0},{ -2, 2, 0},{  1, 3, 0},{ -1, 3, 0},{  6, 1, 0},
			{ -6, 1, 0},{  3, 2, 0},{ -3, 2, 0},{  7, 1, 1},{ -7, 1, 1},{  1, 4, 0},
			{ -1, 4, 0},{  8, 1, 1},{ -8, 1, 1},{  2, 3, 0},{ -2, 3, 0},{  4, 2, 0},
			{ -4, 2, 0},{  1, 5, 0},{ -1, 5, 0},{  9, 1, 1},{ -9, 1, 1},{  5, 2, 0},
			{ -5, 2, 0},{  2, 4, 0},{ -2, 4, 0},{  1, 6, 0},{ -1, 6, 0},{ 10, 1, 2},
			{-10, 1, 2},{  3, 3, 0},{ -3, 3, 0},{ 11, 1, 2},{-11, 1, 2},{  1, 7, 0},
			{ -1, 7, 0},{  6, 2, 0},{ -6, 2, 0},{  3, 4, 0},{ -3, 4, 0},{  2, 5, 0},
			{ -2, 5, 0},{ 12, 1, 2},{-12, 1, 2},{  4, 3, 0},{ -4, 3, 0}
		},
		//level_add
		{
			0,13, 7, 5, 4, 3, 2, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		6, //inc_limit
		7  //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  1, 2, 0},
			{ -1, 2, 0},{  6, 1, 0},{ -6, 1, 0},{  7, 1, 0},{ -7, 1, 0},{  8, 1, 0},
			{ -8, 1, 0},{  2, 2, 0},{ -2, 2, 0},{  9, 1, 0},{ -9, 1, 0},{  1, 3, 0},
			{ -1, 3, 0},{ 10, 1, 1},{-10, 1, 1},{  3, 2, 0},{ -3, 2, 0},{ 11, 1, 1},
			{-11, 1, 1},{  4, 2, 0},{ -4, 2, 0},{ 12, 1, 1},{-12, 1, 1},{  1, 4, 0},
			{ -1, 4, 0},{  2, 3, 0},{ -2, 3, 0},{ 13, 1, 1},{-13, 1, 1},{  5, 2, 0},
			{ -5, 2, 0},{ 14, 1, 1},{-14, 1, 1},{  6, 2, 0},{ -6, 2, 0},{  1, 5, 0},
			{ -1, 5, 0},{ 15, 1, 1},{-15, 1, 1},{  3, 3, 0},{ -3, 3, 0},{ 16, 1, 1},
			{-16, 1, 1},{  2, 4, 0},{ -2, 4, 0},{  7, 2, 0},{ -7, 2, 0}
		},
		//level_add
		{
			0,17, 8, 4, 3, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		9, //inc_limit
		5  //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  6, 1, 0},
			{ -6, 1, 0},{  7, 1, 0},{ -7, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  8, 1, 0},
			{ -8, 1, 0},{  9, 1, 0},{ -9, 1, 0},{ 10, 1, 0},{-10, 1, 0},{ 11, 1, 0},
			{-11, 1, 0},{ 12, 1, 0},{-12, 1, 0},{  2, 2, 0},{ -2, 2, 0},{ 13, 1, 0},
			{-13, 1, 0},{  1, 3, 0},{ -1, 3, 0},{ 14, 1, 0},{-14, 1, 0},{ 15, 1, 0},
			{-15, 1, 0},{  3, 2, 0},{ -3, 2, 0},{ 16, 1, 0},{-16, 1, 0},{ 17, 1, 0},
			{-17, 1, 0},{ 18, 1, 0},{-18, 1, 0},{  4, 2, 0},{ -4, 2, 0},{ 19, 1, 0},
			{-19, 1, 0},{ 20, 1, 0},{-20, 1, 0},{  2, 3, 0},{ -2, 3, 0},{  1, 4, 0},
			{ -1, 4, 0},{  5, 2, 0},{ -5, 2, 0},{ 21, 1, 0},{-21, 1, 0}
		},
		//level_add
		{
			0,22, 6, 3, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		2, //golomb_order
		INT_MAX, //inc_limit
		4 //max_run
	}
};

const struct dec_2dvlc ff_cavs_chroma_dec[5] =
{
	{
		{
			//level / run
			{  1, 1, 1},{ -1, 1, 1},{  1, 2, 1},{ -1, 2, 1},{  1, 3, 1},{ -1, 3, 1},
			{  1, 4, 1},{ -1, 4, 1},{  1, 5, 1},{ -1, 5, 1},{  1, 6, 1},{ -1, 6, 1},
			{  1, 7, 1},{ -1, 7, 1},{  2, 1, 2},{ -2, 1, 2},{  1, 8, 1},{ -1, 8, 1},
			{  1, 9, 1},{ -1, 9, 1},{  1,10, 1},{ -1,10, 1},{  1,11, 1},{ -1,11, 1},
			{  1,12, 1},{ -1,12, 1},{  1,13, 1},{ -1,13, 1},{  1,14, 1},{ -1,14, 1},
			{  1,15, 1},{ -1,15, 1},{  3, 1, 3},{ -3, 1, 3},{  1,16, 1},{ -1,16, 1},
			{  1,17, 1},{ -1,17, 1},{  1,18, 1},{ -1,18, 1},{  1,19, 1},{ -1,19, 1},
			{  1,20, 1},{ -1,20, 1},{  1,21, 1},{ -1,21, 1},{  1,22, 1},{ -1,22, 1},
			{  2, 2, 2},{ -2, 2, 2},{  1,23, 1},{ -1,23, 1},{  1,24, 1},{ -1,24, 1},
			{  1,25, 1},{ -1,25, 1},{  4, 1, 3},{ -4, 1, 3},{   EOB   }
		},
		//level_add
		{
			0, 5, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2, 2, 2, 2, 2, 2,-1
		},
		2, //golomb_order
		0, //inc_limit
		25 //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  2, 1, 1},
			{ -2, 1, 1},{  1, 3, 0},{ -1, 3, 0},{  1, 4, 0},{ -1, 4, 0},{  1, 5, 0},
			{ -1, 5, 0},{  1, 6, 0},{ -1, 6, 0},{  3, 1, 2},{ -3, 1, 2},{  1, 7, 0},
			{ -1, 7, 0},{  1, 8, 0},{ -1, 8, 0},{  2, 2, 1},{ -2, 2, 1},{  1, 9, 0},
			{ -1, 9, 0},{  1,10, 0},{ -1,10, 0},{  1,11, 0},{ -1,11, 0},{  4, 1, 2},
			{ -4, 1, 2},{  1,12, 0},{ -1,12, 0},{  1,13, 0},{ -1,13, 0},{  1,14, 0},
			{ -1,14, 0},{  2, 3, 1},{ -2, 3, 1},{  1,15, 0},{ -1,15, 0},{  2, 4, 1},
			{ -2, 4, 1},{  5, 1, 3},{ -5, 1, 3},{  3, 2, 2},{ -3, 2, 2},{  1,16, 0},
			{ -1,16, 0},{  1,17, 0},{ -1,17, 0},{  1,18, 0},{ -1,18, 0},{  2, 5, 1},
			{ -2, 5, 1},{  1,19, 0},{ -1,19, 0},{  1,20, 0},{ -1,20, 0}
		},
		//level_add
		{
			0, 6, 4, 3, 3, 3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
			2, 2, 2, 2,-1,-1,-1,-1,-1,-1
		},
		0, //golomb_order
		1, //inc_limit
		20 //max_run
	},{
		{
			//level / run
			{  1, 1, 0},{ -1, 1, 0},{   EOB   },{  2, 1, 0},{ -2, 1, 0},{  1, 2, 0},
			{ -1, 2, 0},{  3, 1, 1},{ -3, 1, 1},{  1, 3, 0},{ -1, 3, 0},{  4, 1, 1},
			{ -4, 1, 1},{  2, 2, 0},{ -2, 2, 0},{  1, 4, 0},{ -1, 4, 0},{  5, 1, 2},
			{ -5, 1, 2},{  1, 5, 0},{ -1, 5, 0},{  3, 2, 1},{ -3, 2, 1},{  2, 3, 0},
			{ -2, 3, 0},{  1, 6, 0},{ -1, 6, 0},{  6, 1, 2},{ -6, 1, 2},{  1, 7, 0},
			{ -1, 7, 0},{  2, 4, 0},{ -2, 4, 0},{  7, 1, 2},{ -7, 1, 2},{  1, 8, 0},
			{ -1, 8, 0},{  4, 2, 1},{ -4, 2, 1},{  1, 9, 0},{ -1, 9, 0},{  3, 3, 1},
			{ -3, 3, 1},{  2, 5, 0},{ -2, 5, 0},{  2, 6, 0},{ -2, 6, 0},{  8, 1, 2},
			{ -8, 1, 2},{  1,10, 0},{ -1,10, 0},{  1,11, 0},{ -1,11, 0},{  9, 1, 2},
			{ -9, 1, 2},{  5, 2, 2},{ -5, 2, 2},{  3, 4, 1},{ -3, 4, 1},
		},
		//level_add
		{
			0,10, 6, 4, 4, 3, 3, 2, 2, 2, 2, 2,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		1, //golomb_order
		2, //inc_limit
		11 //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  1, 2, 0},{ -1, 2, 0},{  5, 1, 1},
			{ -5, 1, 1},{  2, 2, 0},{ -2, 2, 0},{  6, 1, 1},{ -6, 1, 1},{  1, 3, 0},
			{ -1, 3, 0},{  7, 1, 1},{ -7, 1, 1},{  3, 2, 0},{ -3, 2, 0},{  8, 1, 1},
			{ -8, 1, 1},{  1, 4, 0},{ -1, 4, 0},{  2, 3, 0},{ -2, 3, 0},{  9, 1, 1},
			{ -9, 1, 1},{  4, 2, 0},{ -4, 2, 0},{  1, 5, 0},{ -1, 5, 0},{ 10, 1, 1},
			{-10, 1, 1},{  3, 3, 0},{ -3, 3, 0},{  5, 2, 1},{ -5, 2, 1},{  2, 4, 0},
			{ -2, 4, 0},{ 11, 1, 1},{-11, 1, 1},{  1, 6, 0},{ -1, 6, 0},{ 12, 1, 1},
			{-12, 1, 1},{  1, 7, 0},{ -1, 7, 0},{  6, 2, 1},{ -6, 2, 1},{ 13, 1, 1},
			{-13, 1, 1},{  2, 5, 0},{ -2, 5, 0},{  1, 8, 0},{ -1, 8, 0},
		},
		//level_add
		{
			0,14, 7, 4, 3, 3, 2, 2, 2,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		1, //golomb_order
		4, //inc_limit
		8  //max_run
	},{
		{
			//level / run
			{   EOB   },{  1, 1, 0},{ -1, 1, 0},{  2, 1, 0},{ -2, 1, 0},{  3, 1, 0},
			{ -3, 1, 0},{  4, 1, 0},{ -4, 1, 0},{  5, 1, 0},{ -5, 1, 0},{  6, 1, 0},
			{ -6, 1, 0},{  7, 1, 0},{ -7, 1, 0},{  8, 1, 0},{ -8, 1, 0},{  1, 2, 0},
			{ -1, 2, 0},{  9, 1, 0},{ -9, 1, 0},{ 10, 1, 0},{-10, 1, 0},{ 11, 1, 0},
			{-11, 1, 0},{  2, 2, 0},{ -2, 2, 0},{ 12, 1, 0},{-12, 1, 0},{ 13, 1, 0},
			{-13, 1, 0},{  3, 2, 0},{ -3, 2, 0},{ 14, 1, 0},{-14, 1, 0},{  1, 3, 0},
			{ -1, 3, 0},{ 15, 1, 0},{-15, 1, 0},{  4, 2, 0},{ -4, 2, 0},{ 16, 1, 0},
			{-16, 1, 0},{ 17, 1, 0},{-17, 1, 0},{  5, 2, 0},{ -5, 2, 0},{  1, 4, 0},
			{ -1, 4, 0},{  2, 3, 0},{ -2, 3, 0},{ 18, 1, 0},{-18, 1, 0},{  6, 2, 0},
			{ -6, 2, 0},{ 19, 1, 0},{-19, 1, 0},{  1, 5, 0},{ -1, 5, 0},
		},
		//level_add
		{
			0,20, 7, 3, 2, 2,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
			-1,-1,-1,-1,-1,-1,-1,-1,-1,-1
		},
		0, //golomb_order
		INT_MAX, //inc_limit
		5, //max_run
	}
};

#undef EOB

static const uint8_t alpha_tab[64] =
{
	0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  2,  2,  2,  3,  3,
	4,  4,  5,  5,  6,  7,  8,  9, 10, 11, 12, 13, 15, 16, 18, 20,
	22, 24, 26, 28, 30, 33, 33, 35, 35, 36, 37, 37, 39, 39, 42, 44,
	46, 48, 50, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64
};

static const uint8_t beta_tab[64] =
{
	0,  0,  0,  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  2,  2,  2,
	2,  2,  3,  3,  3,  3,  4,  4,  4,  4,  5,  5,  5,  5,  6,  6,
	6,  7,  7,  7,  8,  8,  8,  9,  9, 10, 10, 11, 11, 12, 13, 14,
	15, 16, 17, 18, 19, 20, 21, 22, 23, 23, 24, 24, 25, 25, 26, 27
};

static const uint8_t tc_tab[64] =
{
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2,
	2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 4, 4, 4,
	5, 5, 5, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9
};

const int_fast8_t ff_left_modifier_l[8] = { 0,-1, 6,-1,-1, 7, 6, 7};
const int_fast8_t ff_top_modifier_l[8]  = {-1, 1, 5,-1,-1, 5, 7, 7};
const int_fast8_t ff_left_modifier_c[7] = { 5,-1, 2,-1, 6, 5, 6};
const int_fast8_t ff_top_modifier_c[7]  = { 4, 1,-1,-1, 4, 6, 6};

#endif /* AVCODEC_CAVSDATA_H */

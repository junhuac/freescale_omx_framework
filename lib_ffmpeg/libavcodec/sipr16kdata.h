/*
 * SIPR decoder for the 16k mode
 *
 * Copyright (c) 2008 Vladimir Voroshilov
 * Copyright (c) 2009 Vitor Sessak
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

#ifndef AVCODEC_SIPR16KDATA_H
#define AVCODEC_SIPR16KDATA_H

static const float pred_16k[2] = {0.8, 0.6};
static const float qu[2] = { 0.12, 0.5};

static const float gain_cb_16k[32] =
{
	0.07499,  0.10593,  0.14125,  0.18836,
	0.23714,  0.28184,  0.32734,  0.37584,
	0.42170,  0.47315,  0.53088,  0.59566,
	0.66834,  0.74989,  0.84140,  0.94406,
	1.05925,  1.18850,  1.33352,  1.49624,
	1.67880,  1.88365,  2.11349,  2.37137,
	2.66073,  3.05492,  3.54813,  4.21697,
	5.30884,  7.07946,  9.44061, 13.33521,
};

static const float gain_pitch_cb_16k[16] =
{
	0.00, 0.2, 0.40, 0.5, 0.60, 0.7, 0.75, 0.8,
	0.85, 0.9, 0.95, 1.0, 1.05, 1.1, 1.15, 1.2,
};


static const float mean_lsf_16k[16] =
{
	0.131554,  0.246615,  0.435896,  0.644419,
	0.827810,  1.017876,  1.198910,  1.379159,
	1.562157,  1.736908,  1.940719,  2.131963,
	2.347162,  2.521521,  2.717870,  2.847068
};

/**
 * Hamming windowed sinc function, like in AMR
 */
static const float sinc_win[40] =
{
	0.874475,  0.755101,  0.455962,  0.118807, -0.114223, -0.176778,
	-0.101923,  0.015553,  0.086555,  0.078193,  0.018660, -0.037513,
	-0.052733, -0.027459,  0.009967,  0.030278,  0.024050,  0.003055,
	-0.013862, -0.016162, -0.006725,  0.004212,  0.008634,  0.005721,
	-0.000000, -0.003710, -0.003690, -0.001228,  0.001409,  0.002610,
};

static const float lsf_cb1_16k[128][3] =
{
	{-0.089990, -0.172485, -0.203391}, {-0.094710, -0.178687, -0.134483},
	{-0.056398, -0.131952, -0.154500}, {-0.051362, -0.128138, -0.198549},
	{-0.061700, -0.142830, -0.251623}, {-0.041512, -0.115637, -0.229420},
	{-0.036544, -0.107512, -0.173125}, {-0.024158, -0.088450, -0.204144},
	{-0.038690, -0.103368, -0.132674}, {-0.056954, -0.128472, -0.104669},
	{-0.020963, -0.076785, -0.163199}, {-0.012952, -0.077249, -0.128385},
	{-0.032787, -0.097044, -0.093967}, {-0.035214, -0.053838, -0.111940},
	{-0.013850, -0.036926, -0.139328}, {-0.004956, -0.065092, -0.087709},
	{-0.065354, -0.065595, -0.079064}, {-0.023627, -0.081457, -0.054195},
	{-0.027335, -0.035244, -0.068034}, { 0.016555, -0.047075, -0.128286},
	{ 0.021066, -0.037252, -0.092041}, { 0.014681, -0.043044, -0.057739},
	{-0.008493, -0.008143, -0.102486}, {-0.002303, -0.061540, -0.022952},
	{-0.006061, -0.014278, -0.033652}, {-0.005276,  0.011246, -0.062762},
	{ 0.043411, -0.006303, -0.063730}, { 0.035885, -0.010052, -0.115290},
	{ 0.030628, -0.031538, -0.017807}, { 0.022345,  0.028210, -0.032335},
	{ 0.026535,  0.027536, -0.091150}, {-0.003365, -0.008077,  0.015687},
	{-0.026013,  0.017493, -0.010355}, { 0.059069,  0.010634, -0.007530},
	{ 0.044038, -0.019424,  0.030453}, {-0.036065, -0.034215, -0.007758},
	{ 0.022486,  0.042543,  0.027870}, {-0.049985, -0.016085,  0.021768},
	{-0.021715,  0.021168,  0.052076}, {-0.004243, -0.061228,  0.027640},
	{-0.033950, -0.017287,  0.064656}, { 0.016151,  0.000727,  0.062757},
	{-0.063456, -0.043152,  0.056707}, {-0.067715,  0.006126,  0.058178},
	{-0.038931,  0.051673,  0.030636}, {-0.073017, -0.074716,  0.026387},
	{-0.039893, -0.104629,  0.039616}, {-0.073179, -0.074601,  0.082069},
	{-0.066154, -0.027180,  0.099439}, {-0.075167, -0.121149,  0.071938},
	{-0.030382, -0.092582,  0.091067}, {-0.084519, -0.137542,  0.023626},
	{-0.060956, -0.121259, -0.015264}, {-0.030069, -0.093823, -0.008692},
	{-0.063564, -0.065225, -0.025820}, {-0.052074, -0.117595, -0.059689},
	{-0.091652, -0.165173, -0.045573}, {-0.070167, -0.121342,  0.131707},
	{-0.061024, -0.005833, -0.051035}, { 0.007837, -0.051816,  0.074575},
	{-0.070643, -0.053927,  0.149498}, {-0.014358, -0.066681,  0.139708},
	{-0.058186,  0.029576,  0.092923}, {-0.023371,  0.007058,  0.112484},
	{-0.057969,  0.022786,  0.148420}, { 0.029439, -0.017673,  0.121423},
	{-0.015811,  0.056785,  0.091594}, { 0.004347,  0.056680,  0.137848},
	{-0.004464,  0.002342,  0.184013}, { 0.029660,  0.046870,  0.082654},
	{ 0.059408,  0.001016,  0.086063}, { 0.055263,  0.027574,  0.155037},
	{ 0.062166,  0.064323,  0.117371}, { 0.022967,  0.100050,  0.077227},
	{ 0.041795,  0.096343,  0.170421}, { 0.053189,  0.122931,  0.118549},
	{ 0.094247,  0.094448,  0.078395}, { 0.082407,  0.033408,  0.041085},
	{ 0.096820,  0.115960,  0.149433}, { 0.067804,  0.121849,  0.025336},
	{-0.008421,  0.104316,  0.032314}, { 0.031013,  0.073218, -0.004899},
	{ 0.085079,  0.060323, -0.009687}, { 0.028174,  0.092766, -0.055590},
	{ 0.070133,  0.039160, -0.061035}, {-0.039211,  0.072517, -0.028756},
	{ 0.129686,  0.100233, -0.046998}, { 0.154189,  0.107616,  0.022791},
	{-0.049331,  0.094184,  0.087984}, {-0.013179,  0.126552,  0.125099},
	{-0.058716,  0.098524,  0.150886}, {-0.022753,  0.080011,  0.191127},
	{ 0.013451,  0.164593,  0.153768}, { 0.074818,  0.181214,  0.108211},
	{ 0.091323,  0.169249,  0.168460}, { 0.033885,  0.155516,  0.213745},
	{-0.032128,  0.227238,  0.135815}, {-0.059176,  0.168980,  0.229110},
	{ 0.033917,  0.229753,  0.222264}, { 0.082702,  0.116370,  0.224697},
	{ 0.127737,  0.186658,  0.212783}, { 0.047528,  0.063920,  0.216856},
	{-0.002446,  0.114174,  0.263289}, {-0.077783,  0.082523,  0.249697},
	{ 0.010023,  0.024267,  0.256874}, { 0.053190,  0.111422,  0.310407},
	{-0.078804,  0.004444,  0.224078}, {-0.055253, -0.059180,  0.217892},
	{-0.065371,  0.008124,  0.333405}, {-0.076188, -0.098767,  0.286983},
	{-0.071911, -0.115804,  0.198031}, {-0.062473,  0.183639,  0.370162},
	{-0.042666,  0.255210,  0.262720}, { 0.011999,  0.217530,  0.318291},
	{-0.042144,  0.322087,  0.326387}, { 0.090663,  0.205835,  0.294784},
	{ 0.058218,  0.293649,  0.277927}, { 0.157506,  0.282870,  0.294610},
	{ 0.118248,  0.261007,  0.148614}, { 0.065261,  0.332362,  0.411912},
	{ 0.141269,  0.451850,  0.315726}, { 0.001706,  0.456301,  0.357590},
	{-0.052947,  0.356559,  0.456944}, { 0.247707,  0.263837,  0.152591},
	{ 0.306847,  0.417373,  0.258553}, { 0.166347,  0.149222,  0.118973},
	{ 0.379709,  0.292172,  0.139875}, { 0.010171, -0.055170, -0.174523}
};

static const float lsf_cb2_16k[256][3] =
{
	{-0.213011, -0.293385, -0.330597}, {-0.212582, -0.240992, -0.338239},
	{-0.223373, -0.306214, -0.277192}, {-0.231138, -0.287729, -0.229412},
	{-0.238466, -0.228571, -0.260954}, {-0.140931, -0.247018, -0.258566},
	{-0.136239, -0.249669, -0.350143}, {-0.149738, -0.192970, -0.281475},
	{-0.167058, -0.261052, -0.196301}, {-0.177049, -0.201324, -0.207897},
	{-0.116915, -0.200629, -0.212526}, {-0.162247, -0.143805, -0.245093},
	{-0.082042, -0.191842, -0.266338}, {-0.098846, -0.208511, -0.320481},
	{-0.113510, -0.152470, -0.222474}, {-0.066197, -0.179112, -0.207813},
	{-0.129490, -0.169320, -0.155238}, {-0.078843, -0.190292, -0.155172},
	{-0.087790, -0.147729, -0.169351}, {-0.141037, -0.127207, -0.177910},
	{-0.126525, -0.223961, -0.153639}, {-0.101464, -0.189953, -0.114559},
	{-0.102450, -0.106303, -0.151171}, {-0.103208, -0.144457, -0.105378},
	{-0.170794, -0.140525, -0.136428}, {-0.168641, -0.203064, -0.135368},
	{-0.138193, -0.116042, -0.111905}, {-0.145085, -0.168581, -0.092613},
	{-0.126379, -0.220431, -0.091327}, {-0.212934, -0.184797, -0.101632},
	{-0.193711, -0.140556, -0.078304}, {-0.173674, -0.197276, -0.060140},
	{-0.197897, -0.241907, -0.091997}, {-0.156037, -0.258519, -0.111628},
	{-0.241964, -0.191124, -0.063140}, {-0.261340, -0.240847, -0.103132},
	{-0.221621, -0.242972, -0.041255}, {-0.224166, -0.232742, -0.161568},
	{-0.203591, -0.294470, -0.126035}, {-0.209540, -0.303149, -0.053170},
	{-0.253859, -0.295066, -0.156050}, {-0.278143, -0.331105, -0.085237},
	{-0.300273, -0.198750, -0.094834}, {-0.260477, -0.169713, -0.132476},
	{-0.211889, -0.172454, -0.164281}, {-0.228370, -0.122149, -0.124178},
	{-0.254629, -0.135668, -0.081692}, {-0.263813, -0.154928, -0.213596},
	{-0.308224, -0.106877, -0.084404}, {-0.242644, -0.082862, -0.085835},
	{-0.252084, -0.064888, -0.146498}, {-0.198162, -0.105721, -0.188887},
	{-0.189238, -0.088028, -0.109736}, {-0.197598, -0.099831, -0.044030},
	{-0.269017, -0.105991, -0.021513}, {-0.231349, -0.058825, -0.041407},
	{-0.225589, -0.027501, -0.087160}, {-0.160347, -0.058341, -0.079789},
	{-0.158729, -0.108951, -0.067262}, {-0.170483, -0.053023, -0.017561},
	{-0.175207, -0.013649, -0.049513}, {-0.156004, -0.108378, -0.004052},
	{-0.219958, -0.082362,  0.014950}, {-0.217785, -0.012981, -0.009410},
	{-0.123290, -0.040849, -0.040910}, {-0.119861, -0.095078, -0.060246},
	{-0.117537, -0.065479,  0.002968}, {-0.103231, -0.113298, -0.023282},
	{-0.136365, -0.149524, -0.051387}, {-0.119332, -0.164400, -0.009103},
	{-0.104522, -0.060948, -0.083056}, {-0.071461, -0.070787, -0.037347},
	{-0.081116, -0.149015, -0.056740}, {-0.069561, -0.108099, -0.069167},
	{-0.055624, -0.117369, -0.025091}, {-0.091941, -0.190091, -0.060020},
	{-0.072003, -0.168433, -0.006540}, {-0.033305, -0.154427, -0.054608},
	{-0.062988, -0.127093, -0.108307}, {-0.056690, -0.170813, -0.102834},
	{-0.018273, -0.127863, -0.094998}, {-0.056239, -0.123678, -0.146262},
	{-0.023442, -0.154617, -0.137417}, {-0.051903, -0.078379, -0.093395},
	{-0.014599, -0.104412, -0.135959}, {-0.051582, -0.081280, -0.140643},
	{-0.092727, -0.091930, -0.107816}, {-0.024814, -0.140993, -0.183243},
	{-0.064307, -0.113024, -0.194788}, {-0.000118, -0.098858, -0.195336},
	{-0.028090, -0.048258, -0.164101}, {-0.093414, -0.055969, -0.172743},
	{-0.114445, -0.104336, -0.215204}, {-0.048518, -0.132063, -0.242991},
	{-0.159620, -0.060240, -0.178592}, {-0.135728, -0.067473, -0.131876},
	{-0.078464, -0.038040, -0.125105}, {-0.011061, -0.064011, -0.102496},
	{-0.033887, -0.026485, -0.109493}, {-0.129128, -0.014216, -0.111329},
	{-0.190687, -0.030660, -0.135825}, {-0.082037,  0.010997, -0.100167},
	{-0.183403,  0.001651, -0.098962}, {-0.074775, -0.030335, -0.062217},
	{-0.031759, -0.050551, -0.059420}, {-0.051439,  0.010827, -0.052148},
	{-0.126744,  0.008689, -0.047785}, {-0.145916,  0.042019, -0.077431},
	{-0.093552,  0.054143, -0.060473}, {-0.090660,  0.012868, -0.018195},
	{-0.079783, -0.033071,  0.001482}, {-0.033010, -0.022331, -0.014506},
	{-0.004798, -0.017339, -0.060120}, {-0.025021,  0.026390, -0.003263},
	{-0.001437,  0.025994, -0.040892}, {-0.074821,  0.019005,  0.027549},
	{-0.030811, -0.012114,  0.034284}, { 0.006785,  0.004618,  0.018717},
	{ 0.013392, -0.032597, -0.023731}, { 0.035994,  0.005963, -0.011757},
	{ 0.008071, -0.045750,  0.024889}, { 0.013055,  0.017040,  0.054121},
	{-0.012989,  0.044864,  0.036327}, { 0.025054,  0.047137,  0.009974},
	{ 0.053801,  0.024178,  0.031774}, { 0.056442, -0.030647,  0.021291},
	{ 0.032247,  0.052680,  0.049886}, { 0.035369,  0.090207,  0.031394},
	{ 0.064720,  0.070390,  0.040938}, { 0.022112,  0.054834,  0.091059},
	{ 0.041765,  0.086248,  0.070196}, { 0.070645,  0.060852,  0.078825},
	{ 0.058506,  0.016920,  0.081612}, { 0.000009,  0.086500,  0.059849},
	{ 0.071253,  0.107392,  0.059046}, { 0.094702,  0.096160,  0.090982},
	{ 0.047639,  0.110877,  0.111227}, { 0.122444,  0.090909,  0.057396},
	{ 0.101916,  0.052299,  0.029909}, { 0.076560,  0.086094, -0.007252},
	{ 0.123411,  0.030769,  0.082749}, { 0.135579,  0.103022,  0.009540},
	{ 0.120576,  0.065284, -0.024095}, { 0.077483,  0.028526, -0.012369},
	{ 0.128747,  0.017901, -0.003874}, { 0.158254,  0.046962,  0.029577},
	{ 0.102287, -0.002211,  0.037329}, { 0.089654, -0.021372, -0.006857},
	{ 0.137917,  0.027228, -0.053223}, { 0.098728, -0.012192, -0.048518},
	{ 0.083974,  0.036153, -0.062266}, { 0.048230, -0.010241, -0.052293},
	{ 0.110135,  0.007715, -0.095233}, { 0.068294, -0.014317, -0.104029},
	{ 0.063909, -0.056416, -0.063023}, { 0.059133, -0.044675, -0.023780},
	{ 0.030748,  0.021845, -0.086332}, { 0.023994, -0.045574, -0.076232},
	{ 0.052147, -0.059825, -0.109667}, { 0.013087, -0.020420, -0.121945},
	{ 0.018163, -0.096765, -0.088758}, { 0.020196, -0.076470, -0.048112},
	{ 0.020282, -0.084204, -0.135535}, { 0.040076, -0.053464, -0.161949},
	{-0.017796, -0.103070, -0.059559}, {-0.016484, -0.070138, -0.016866},
	{ 0.004849, -0.112481, -0.017731}, { 0.040160, -0.073873, -0.005327},
	{ 0.002202, -0.094723,  0.045366}, {-0.056918, -0.081578,  0.017875},
	{-0.031099, -0.141708,  0.009186}, {-0.102802, -0.122675,  0.030060},
	{-0.061717, -0.145116,  0.076680}, {-0.073607, -0.050464,  0.072853},
	{-0.117403, -0.194921,  0.040101}, {-0.185236, -0.133620,  0.045939},
	{-0.160174, -0.057226,  0.056641}, {-0.178489, -0.173435, -0.007806},
	{-0.199916, -0.204866,  0.047342}, {-0.152337, -0.249651,  0.034656},
	{-0.185637, -0.230942, -0.002072}, {-0.122548, -0.215209, -0.024552},
	{-0.249578, -0.209714,  0.009470}, {-0.160108, -0.257702, -0.040992},
	{-0.216694, -0.289353,  0.027182}, {-0.226390, -0.147844, -0.022742},
	{-0.288737, -0.272150, -0.013948}, {-0.262554, -0.237035,  0.072473},
	{-0.306267, -0.188335, -0.032894}, {-0.259666, -0.345816,  0.024138},
	{-0.271093, -0.137143,  0.040404}, {-0.201317, -0.286782,  0.107615},
	{-0.235725, -0.163396,  0.113844}, {-0.159988, -0.209788,  0.112140},
	{-0.262985, -0.056741,  0.093506}, {-0.277226, -0.037306,  0.016008},
	{-0.293486, -0.040422, -0.062018}, {-0.214921,  0.022900,  0.055295},
	{-0.253889,  0.058575, -0.000151}, {-0.246689,  0.024242, -0.058488},
	{-0.143790,  0.006767,  0.014061}, {-0.187077,  0.048882, -0.035625},
	{-0.196369,  0.112085,  0.031546}, {-0.124264,  0.086197, -0.020800},
	{-0.126249,  0.016960,  0.095741}, {-0.079816,  0.080398,  0.051038},
	{-0.056269,  0.075380, -0.028262}, {-0.120493,  0.148495,  0.028430},
	{-0.161750,  0.101290,  0.117806}, {-0.003247,  0.083393, -0.017061},
	{-0.034007,  0.142542,  0.007402}, {-0.037618,  0.025871,  0.089496},
	{-0.082819,  0.184435,  0.073224}, { 0.006448,  0.167015,  0.080548},
	{ 0.035315,  0.144022,  0.003218}, {-0.023459,  0.088147,  0.152604},
	{ 0.006247, -0.024099,  0.077792}, { 0.039894,  0.057586, -0.042455},
	{-0.020417,  0.035400, -0.093971}, { 0.075465,  0.052063,  0.145582},
	{ 0.078027,  0.184720,  0.092096}, { 0.107295,  0.148380,  0.022264},
	{ 0.066928, -0.052831,  0.065108}, { 0.093295,  0.118157,  0.149815},
	{ 0.119373,  0.137114,  0.099536}, { 0.138653,  0.075509,  0.121545},
	{ 0.174025,  0.077531,  0.077169}, { 0.165839,  0.150080,  0.133423},
	{ 0.173276,  0.155887,  0.048150}, { 0.162910,  0.095898,  0.171896},
	{ 0.214577,  0.112888,  0.115579}, { 0.204755,  0.106392,  0.032337},
	{ 0.178853,  0.205034,  0.114760}, { 0.177401,  0.070504, -0.013778},
	{ 0.241624,  0.166921,  0.066087}, { 0.219595,  0.183553,  0.172332},
	{ 0.123671,  0.170842,  0.167216}, { 0.177104,  0.240197,  0.186359},
	{ 0.272003,  0.220214,  0.126073}, { 0.093748,  0.235843,  0.160998},
	{ 0.141510,  0.190012,  0.240416}, { 0.046878,  0.168984,  0.190412},
	{ 0.094898,  0.107038,  0.235003}, { 0.108592,  0.269536,  0.262528},
	{-0.027754,  0.234355,  0.134544}, { 0.265127,  0.267540,  0.199041},
	{ 0.199523,  0.291507,  0.265171}, { 0.266177,  0.209339,  0.350369},
	{ 0.322159,  0.344794,  0.270823}, { 0.399957,  0.264065,  0.110387},
	{ 0.277817,  0.127407, -0.035625}, {-0.177038,  0.208155,  0.119077},
	{ 0.049075, -0.076294,  0.145711}, { 0.187246,  0.042865, -0.127097},
	{ 0.117885, -0.023489, -0.138658}, {-0.284256,  0.068153,  0.124259}
};

static const float lsf_cb3_16k[128][3] =
{
	{-0.223412, -0.236300, -0.188067}, {-0.202286, -0.218711, -0.102947},
	{-0.251652, -0.161020, -0.125280}, {-0.169223, -0.138155, -0.140430},
	{-0.176427, -0.146628, -0.222632}, {-0.120584, -0.187276, -0.180164},
	{-0.195559, -0.074225, -0.169109}, {-0.144551, -0.142774, -0.073340},
	{-0.111001, -0.111310, -0.130696}, {-0.095221, -0.174684, -0.111841},
	{-0.112158, -0.103049, -0.195130}, {-0.059989, -0.142170, -0.157850},
	{-0.127598, -0.051759, -0.153109}, {-0.063753, -0.067898, -0.164117},
	{-0.141753, -0.068274, -0.091999}, {-0.060482, -0.101054, -0.099475},
	{-0.104699, -0.104456, -0.066496}, {-0.073649, -0.052614, -0.091612},
	{-0.088268, -0.019072, -0.129956}, {-0.018837, -0.104115, -0.127837},
	{-0.021630, -0.033055, -0.129868}, {-0.083768, -0.047549, -0.041407},
	{-0.055892, -0.108526, -0.043200}, {-0.027816, -0.062499, -0.048190},
	{-0.002248, -0.110428, -0.062868}, { 0.001270, -0.033245, -0.072404},
	{-0.042747, -0.013835, -0.033829}, {-0.037615, -0.147833, -0.083912},
	{-0.045023,  0.006011, -0.092182}, {-0.050411, -0.081832,  0.005787},
	{ 0.000357, -0.104282, -0.009428}, {-0.003893, -0.047892, -0.001506},
	{-0.040077, -0.147110, -0.009065}, {-0.060858, -0.030972,  0.012999},
	{-0.014674,  0.001370,  0.005554}, {-0.101362, -0.126061, -0.001898},
	{-0.102519, -0.000390, -0.015721}, {-0.132687, -0.069608, -0.019928},
	{-0.102227, -0.076131,  0.043306}, {-0.055193,  0.027001,  0.011857},
	{-0.156427, -0.016629,  0.017480}, {-0.078736,  0.002809,  0.057979},
	{-0.157789, -0.016693, -0.055073}, {-0.179397, -0.095520,  0.022065},
	{-0.110219,  0.010408, -0.081927}, {-0.125392,  0.049111,  0.044595},
	{-0.112528,  0.063173, -0.024954}, {-0.185525,  0.053093, -0.032102},
	{-0.176887, -0.019379, -0.115125}, {-0.249706, -0.017664, -0.059188},
	{-0.200243, -0.103311, -0.066846}, {-0.055404,  0.045106, -0.046991},
	{-0.000544,  0.022690, -0.044831}, { 0.022298, -0.016367, -0.022509},
	{ 0.028278,  0.017585, -0.100612}, { 0.061781, -0.020826, -0.068190},
	{ 0.029157, -0.074477, -0.098898}, { 0.043073, -0.067234, -0.032293},
	{ 0.060157,  0.034636, -0.034885}, { 0.071153, -0.013881, -0.009036},
	{ 0.054196, -0.029989, -0.131139}, { 0.030193,  0.024976,  0.009861},
	{ 0.055943, -0.045304,  0.031927}, { 0.033217, -0.002418,  0.038165},
	{ 0.063814,  0.045625,  0.025309}, { 0.033689,  0.038819,  0.049700},
	{ 0.073582,  0.028527,  0.060200}, {-0.007957,  0.022531,  0.043687},
	{-0.000984,  0.054518,  0.018742}, { 0.057004,  0.060916,  0.060573},
	{ 0.009883,  0.015238,  0.080211}, { 0.022742,  0.070832,  0.068855},
	{ 0.053001,  0.029790,  0.091446}, {-0.042447,  0.060379,  0.061462},
	{ 0.076826,  0.062468,  0.089653}, { 0.039065,  0.069768,  0.119128},
	{ 0.064145,  0.095353,  0.071621}, { 0.094411,  0.069527,  0.054197},
	{ 0.042812,  0.093060,  0.027980}, { 0.094791,  0.099189,  0.101112},
	{ 0.117611,  0.048601,  0.093111}, { 0.119951,  0.122758,  0.051546},
	{ 0.103558,  0.085245, -0.010700}, { 0.150126,  0.059766,  0.020280},
	{ 0.108066,  0.017170,  0.008606}, { 0.108422,  0.023253, -0.063942},
	{ 0.019652,  0.072284, -0.030331}, { 0.192719,  0.075624,  0.071156},
	{ 0.221140,  0.069191, -0.035085}, { 0.188367,  0.126200,  0.035225},
	{ 0.185760,  0.043537, -0.101714}, {-0.042518,  0.099646,  0.003244},
	{-0.015308, -0.027521,  0.046006}, { 0.034086, -0.045777,  0.095989},
	{ 0.007174, -0.093358,  0.046459}, {-0.051248, -0.062095,  0.083161},
	{-0.045626, -0.133301,  0.052997}, {-0.037840,  0.024042,  0.131097},
	{-0.020217, -0.115942,  0.126170}, {-0.134550, -0.036291,  0.111322},
	{-0.110576, -0.160024,  0.091841}, {-0.093308, -0.184958,  0.013939},
	{-0.082735, -0.167417, -0.051725}, {-0.169934, -0.173003, -0.007155},
	{-0.128244, -0.213123, -0.053337}, {-0.079852, -0.154116, -0.246546},
	{-0.032242, -0.108756, -0.204133}, {-0.140117, -0.199495, -0.284505},
	{ 0.010842, -0.074979, -0.166333}, {-0.093313,  0.145006,  0.034110},
	{-0.039236,  0.113213,  0.111053}, { 0.040613, -0.031783,  0.174058},
	{-0.164232,  0.131421,  0.149842}, { 0.026893,  0.107281,  0.179297},
	{ 0.047086,  0.158606,  0.103267}, {-0.070567,  0.210459,  0.134734},
	{ 0.094392,  0.137050,  0.166892}, { 0.086039,  0.063657,  0.168825},
	{ 0.159371,  0.120897,  0.154357}, { 0.147101,  0.160684,  0.114882},
	{ 0.120158,  0.199650,  0.180948}, { 0.191417,  0.174500,  0.170734},
	{ 0.159153,  0.142165,  0.233347}, { 0.232002,  0.150181,  0.102736},
	{ 0.188299,  0.221738,  0.228748}, { 0.256786,  0.209685,  0.161534},
	{ 0.257861,  0.247793,  0.250516}, {-0.164461, -0.000143,  0.232461}
};

static const float lsf_cb4_16k[128][3] =
{
	{-0.193369, -0.304643, -0.253777}, {-0.164125, -0.277786, -0.153116},
	{-0.135681, -0.209120, -0.211724}, {-0.121822, -0.215734, -0.292207},
	{-0.198781, -0.161674, -0.242538}, {-0.164147, -0.180570, -0.138070},
	{-0.095915, -0.198695, -0.154309}, {-0.248386, -0.234462, -0.136984},
	{-0.164968, -0.108318, -0.175635}, {-0.124171, -0.111809, -0.224402},
	{-0.067398, -0.157017, -0.195759}, {-0.090132, -0.119174, -0.165253},
	{-0.099460, -0.146895, -0.106799}, {-0.141493, -0.108103, -0.108880},
	{-0.085088, -0.098340, -0.109953}, {-0.105526, -0.054463, -0.154315},
	{-0.040480, -0.144285, -0.124042}, {-0.040969, -0.084039, -0.142880},
	{-0.049082, -0.118553, -0.066686}, {-0.096336, -0.087515, -0.055741},
	{-0.058605, -0.059327, -0.089275}, {-0.121842, -0.058681, -0.086949},
	{-0.053792, -0.022025, -0.124451}, {-0.036744, -0.068891, -0.045865},
	{ 0.003900, -0.098237, -0.091158}, {-0.001664, -0.045089, -0.081353},
	{-0.072829, -0.034087, -0.038416}, {-0.100822, -0.007330, -0.088715},
	{-0.035911, -0.005864, -0.062577}, {-0.020205, -0.026547, -0.019634},
	{ 0.004291, -0.041290, -0.138181}, { 0.023404, -0.010932, -0.044904},
	{ 0.013557,  0.014823, -0.092943}, { 0.059673, -0.031024, -0.095739},
	{ 0.021130, -0.080607, -0.034594}, { 0.024655, -0.035564,  0.003243},
	{ 0.017106,  0.006952, -0.000308}, { 0.075208, -0.030910, -0.031181},
	{ 0.024965,  0.048632, -0.039448}, { 0.057028,  0.021547, -0.009418},
	{-0.018577,  0.023697, -0.009759}, { 0.024077,  0.033053,  0.024324},
	{ 0.037052, -0.003436,  0.044530}, {-0.012871, -0.007179,  0.031795},
	{ 0.077877,  0.021547,  0.023131}, { 0.053365,  0.052078,  0.029433},
	{ 0.011429,  0.070426,  0.028734}, {-0.001827,  0.033115,  0.061505},
	{-0.044870,  0.038568,  0.026239}, { 0.061633,  0.034799,  0.059784},
	{ 0.034261,  0.060342,  0.065185}, { 0.058981,  0.082481,  0.047252},
	{ 0.090008,  0.065942,  0.044470}, { 0.066961,  0.073728, -0.000428},
	{ 0.074763,  0.060293,  0.085632}, { 0.066366,  0.103375,  0.079642},
	{ 0.122297,  0.036558,  0.058745}, { 0.111042,  0.092093,  0.085412},
	{ 0.099243,  0.115476,  0.039254}, { 0.019973,  0.122844,  0.050255},
	{ 0.159571,  0.098965,  0.051740}, { 0.137624,  0.072405, -0.006922},
	{ 0.130240,  0.146091,  0.089698}, { 0.138335,  0.092968,  0.136193},
	{ 0.066031,  0.149304,  0.125476}, { 0.202749,  0.145751,  0.077122},
	{ 0.002224,  0.082811,  0.131200}, { 0.124476,  0.178073,  0.162336},
	{ 0.174722,  0.190298,  0.127106}, { 0.202193,  0.153569,  0.163840},
	{ 0.242604,  0.197796,  0.136929}, { 0.185809,  0.229348,  0.193353},
	{-0.058814,  0.195178,  0.141821}, { 0.253646,  0.247175,  0.205766},
	{ 0.061433, -0.025542,  0.119311}, {-0.057816,  0.082445,  0.073243},
	{-0.069239,  0.148678,  0.031146}, {-0.030217, -0.008503,  0.106194},
	{-0.026708,  0.087469, -0.009589}, {-0.090418,  0.000265,  0.056807},
	{-0.050607, -0.019383,  0.010494}, {-0.079397,  0.008233, -0.011469},
	{-0.072634, -0.061165,  0.046917}, {-0.075741, -0.072343, -0.007557},
	{-0.025162, -0.073363,  0.005173}, {-0.123371, -0.041257, -0.008375},
	{-0.139904,  0.018285,  0.009920}, {-0.143421, -0.104238,  0.033457},
	{-0.100923, -0.134400, -0.023257}, {-0.157791, -0.095042, -0.036959},
	{-0.219890, -0.078637,  0.001815}, {-0.183607, -0.023053, -0.043678},
	{-0.145303, -0.158923, -0.059045}, {-0.197615, -0.165199,  0.028099},
	{-0.225131, -0.167756, -0.056401}, {-0.216572, -0.104751, -0.102964},
	{-0.171336, -0.241967, -0.063404}, {-0.134035, -0.205614,  0.011831},
	{-0.297116, -0.211173, -0.015352}, {-0.086464, -0.200592, -0.070454},
	{-0.217777, -0.278403,  0.030398}, {-0.236248, -0.323694, -0.087588},
	{-0.222074, -0.210785,  0.106210}, {-0.283400, -0.097077,  0.041303},
	{-0.078417, -0.154464,  0.062956}, {-0.214417, -0.100695,  0.121909},
	{-0.178576, -0.028847,  0.061042}, {-0.037999, -0.144233, -0.010546},
	{-0.086695, -0.070996,  0.125282}, { 0.010788, -0.085006,  0.058527},
	{-0.154015,  0.066560,  0.071038}, {-0.143503,  0.033260,  0.154393},
	{-0.134069,  0.032420, -0.056293}, {-0.110851,  0.086908,  0.003920},
	{-0.057254,  0.047674, -0.055571}, {-0.214206,  0.068784, -0.004735},
	{-0.257264,  0.050468,  0.081702}, {-0.291834,  0.004120, -0.022366},
	{-0.173309, -0.029081, -0.115901}, {-0.207622,  0.168664,  0.136030},
	{ 0.090541,  0.032754, -0.057330}, { 0.140219, -0.000735, -0.015633},
	{ 0.136697, -0.017163, -0.100909}, { 0.029838, -0.089515, -0.147130},
	{-0.055367, -0.072683, -0.214015}, { 0.048680, -0.057633, -0.212429},
	{-0.013134, -0.113898, -0.196403}, {-0.071702, -0.159408, -0.254895}
};

static const float lsf_cb5_16k[128][4] =
{
	{-0.201277, -0.278679, -0.173262, -0.198580},
	{-0.214667, -0.151922, -0.117551, -0.192713},
	{-0.160962, -0.207728, -0.124750, -0.129749},
	{-0.131043, -0.137818, -0.155281, -0.166308},
	{-0.179134, -0.169602, -0.165223, -0.066293},
	{-0.136474, -0.177035, -0.250127, -0.134370},
	{-0.066970, -0.146274, -0.170638, -0.134436},
	{-0.083288, -0.165860, -0.103437, -0.140361},
	{-0.130474, -0.119317, -0.124393, -0.086408},
	{-0.127609, -0.134415, -0.073592, -0.116103},
	{-0.113027, -0.091756, -0.107786, -0.131935},
	{-0.125530, -0.182152, -0.093796, -0.045088},
	{-0.077122, -0.138052, -0.166271, -0.038886},
	{-0.073027, -0.106845, -0.067073, -0.113910},
	{-0.049146, -0.107019, -0.112531, -0.063388},
	{-0.101539, -0.119586, -0.050297, -0.040670},
	{-0.107784, -0.066913, -0.080993, -0.052352},
	{-0.152155, -0.103010, -0.090461, -0.015526},
	{-0.153087, -0.087656, -0.029889, -0.037367},
	{-0.215281, -0.138062, -0.089162, -0.050839},
	{-0.053350, -0.060169, -0.063459, -0.024499},
	{-0.051674, -0.076355, -0.033733, -0.077211},
	{-0.045047, -0.107006, -0.020880, -0.024525},
	{-0.083003, -0.063672, -0.013243, -0.028324},
	{-0.104104, -0.075450, -0.032746,  0.024480},
	{-0.085695, -0.019502, -0.045121, -0.025016},
	{-0.123120, -0.030844, -0.003533, -0.016224},
	{-0.025568, -0.049172, -0.003911, -0.027522},
	{-0.039029, -0.019857, -0.043211, -0.058087},
	{-0.040122, -0.023067, -0.001356,  0.008607},
	{-0.063351, -0.001776,  0.016015, -0.027088},
	{-0.068110, -0.038838,  0.042525,  0.001076},
	{-0.043623, -0.020736, -0.047862,  0.037710},
	{-0.041052,  0.021954, -0.025660,  0.000758},
	{-0.013035,  0.002583, -0.008233, -0.037300},
	{-0.005523, -0.014670,  0.019651, -0.012667},
	{-0.004409, -0.014437, -0.059412, -0.019701},
	{ 0.024946, -0.011663, -0.014351, -0.028762},
	{ 0.012660,  0.018489, -0.010205,  0.012695},
	{-0.004423,  0.017827,  0.040544,  0.003629},
	{ 0.020684,  0.026743,  0.007752, -0.025595},
	{ 0.032071,  0.000043,  0.026188, -0.006444},
	{ 0.058793,  0.015820, -0.001119, -0.017415},
	{ 0.020156, -0.047590,  0.004227,  0.008670},
	{ 0.054770,  0.032135,  0.029770, -0.009767},
	{ 0.030884,  0.047757,  0.033068,  0.006866},
	{ 0.062039,  0.011646,  0.056037,  0.016859},
	{ 0.013798, -0.028196,  0.060710,  0.014299},
	{ 0.100043,  0.041445,  0.023379, -0.014889},
	{ 0.062728, -0.042821,  0.002180, -0.055380},
	{ 0.061663,  0.018767, -0.015571, -0.074095},
	{ 0.062980,  0.080497,  0.011808, -0.031787},
	{ 0.084964,  0.043100, -0.025877,  0.020309},
	{ 0.014707,  0.035421, -0.041440, -0.053373},
	{ 0.081268,  0.005791, -0.066290, -0.039825},
	{ 0.017691, -0.020401, -0.040513, -0.083960},
	{ 0.120874,  0.055753, -0.025988, -0.059552},
	{ 0.079912,  0.007894, -0.085380, -0.114587},
	{ 0.036856, -0.039331, -0.104237, -0.069116},
	{ 0.008526, -0.064273, -0.048312, -0.038595},
	{ 0.033461, -0.028956, -0.066505,  0.038722},
	{-0.042064, -0.043989, -0.100653, -0.071550},
	{-0.015342, -0.064850, -0.065675, -0.122769},
	{-0.006581, -0.004919, -0.113564, -0.145753},
	{ 0.008273, -0.070702, -0.164998, -0.095541},
	{-0.001698, -0.063744, -0.129971, -0.011162},
	{-0.048471, -0.087500, -0.111006, -0.161823},
	{-0.032193, -0.091955, -0.080642,  0.012288},
	{-0.095873, -0.015986, -0.072722, -0.101745},
	{-0.079477, -0.082060, -0.203008, -0.100297},
	{-0.023883, -0.064022, -0.168341, -0.211739},
	{-0.070530, -0.103547, -0.123858,  0.055049},
	{-0.033503, -0.076812, -0.016287,  0.044159},
	{-0.088427, -0.161682, -0.058579,  0.013873},
	{-0.083068, -0.168222, -0.016773, -0.080209},
	{-0.080548, -0.139090,  0.030544,  0.007171},
	{-0.117482, -0.083718,  0.027074, -0.003674},
	{-0.163085, -0.156856, -0.012618, -0.022329},
	{-0.176540, -0.113042, -0.020148,  0.051770},
	{-0.153891, -0.199293, -0.043244,  0.028331},
	{-0.107822, -0.150615,  0.016430,  0.092919},
	{-0.137676, -0.183224,  0.066026,  0.029343},
	{-0.191106, -0.099250,  0.045370,  0.004084},
	{-0.237042, -0.130815, -0.022543, -0.029428},
	{-0.201014, -0.053591, -0.007305, -0.033547},
	{-0.249286, -0.228408,  0.005002,  0.007146},
	{-0.206509, -0.211998, -0.061352, -0.047233},
	{-0.255702, -0.135114,  0.076375,  0.036630},
	{-0.296271, -0.073946, -0.007273, -0.019601},
	{-0.302917, -0.175111, -0.070024, -0.043905},
	{-0.239275, -0.043962, -0.084982, -0.067446},
	{-0.254583, -0.294720, -0.088762, -0.070451},
	{-0.205583, -0.238996, -0.124753,  0.033076},
	{-0.205583, -0.215882, -0.028472,  0.118679},
	{-0.153640, -0.204464, -0.039654, -0.134441},
	{-0.145929, -0.191970, -0.175308,  0.021366},
	{-0.149348, -0.212569, -0.118324,  0.103812},
	{-0.166397, -0.220581, -0.265260, -0.029113},
	{-0.164171, -0.231262, -0.258828,  0.061427},
	{-0.200198, -0.263453, -0.212016,  0.115359},
	{-0.130088, -0.212168, -0.202368,  0.118563},
	{-0.206387, -0.078075, -0.227856, -0.111165},
	{-0.129605, -0.176848, -0.241584, -0.259900},
	{-0.176826, -0.045901, -0.141712, -0.209345},
	{-0.351173, -0.031097, -0.133935, -0.182412},
	{-0.164232,  0.027006, -0.014039, -0.053567},
	{-0.171037, -0.025924,  0.030972,  0.017329},
	{-0.080862, -0.021577,  0.007652,  0.063968},
	{-0.061788,  0.042024, -0.018783, -0.057979},
	{-0.110311,  0.054760,  0.031446, -0.006710},
	{-0.136637,  0.022171,  0.084991,  0.028039},
	{-0.254471, -0.004376,  0.078034,  0.033649},
	{-0.234464,  0.088157,  0.040999,  0.002639},
	{-0.037095,  0.059443,  0.072180,  0.015027},
	{-0.046841, -0.004813,  0.088266,  0.038786},
	{-0.086782,  0.120100,  0.082655,  0.020271},
	{-0.118361, -0.069242,  0.094867,  0.039200},
	{-0.023342, -0.084303,  0.052684,  0.017093},
	{-0.014194,  0.001012,  0.011946,  0.074125},
	{-0.015342,  0.076396,  0.022365, -0.028001},
	{ 0.027706,  0.037047,  0.107573,  0.060815},
	{ 0.030615,  0.040664,  0.010467,  0.074289},
	{ 0.038646,  0.115584,  0.069627,  0.007642},
	{ 0.096463,  0.069818,  0.062494,  0.015413},
	{ 0.054834,  0.065232,  0.054286,  0.110088},
	{ 0.152312,  0.092371,  0.026420, -0.013184},
	{ 0.144264,  0.123438,  0.080131,  0.023233},
	{ 0.124405,  0.009943, -0.148477, -0.205184}
};

static const float *lsf_codebooks_16k[] =
{
	lsf_cb1_16k[0], lsf_cb2_16k[0], lsf_cb3_16k[0], lsf_cb4_16k[0],
	lsf_cb5_16k[0]
};

#endif /* AVCODEC_SIPR16KDATA_H */

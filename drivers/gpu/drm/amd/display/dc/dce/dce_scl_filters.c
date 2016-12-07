/*
 * Copyright 2012-16 Advanced Micro Devices, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER(S) OR AUTHOR(S) BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * Authors: AMD
 *
 */

#include "transform.h"

const uint16_t filter_2tap_16p[18] = {
	4096, 0,
	3840, 256,
	3584, 512,
	3328, 768,
	3072, 1024,
	2816, 1280,
	2560, 1536,
	2304, 1792,
	2048, 2048
};

const uint16_t filter_3tap_16p_upscale[27] = {
	2048, 2048, 0,
	1708, 2424, 16348,
	1372, 2796, 16308,
	1056, 3148, 16272,
	768, 3464, 16244,
	512, 3728, 16236,
	296, 3928, 16252,
	124, 4052, 16296,
	0, 4096, 0
};

const uint16_t filter_3tap_16p_117[27] = {
	2048, 2048, 0,
	1824, 2276, 16376,
	1600, 2496, 16380,
	1376, 2700, 16,
	1156, 2880, 52,
	948, 3032, 108,
	756, 3144, 192,
	580, 3212, 296,
	428, 3236, 428
};

const uint16_t filter_3tap_16p_150[27] = {
	2048, 2048, 0,
	1872, 2184, 36,
	1692, 2308, 88,
	1516, 2420, 156,
	1340, 2516, 236,
	1168, 2592, 328,
	1004, 2648, 440,
	844, 2684, 560,
	696, 2696, 696
};

const uint16_t filter_3tap_16p_183[27] = {
	2048, 2048, 0,
	1892, 2104, 92,
	1744, 2152, 196,
	1592, 2196, 300,
	1448, 2232, 412,
	1304, 2256, 528,
	1168, 2276, 648,
	1032, 2288, 772,
	900, 2292, 900
};

const uint16_t filter_4tap_16p_upscale[36] = {
	0, 4096, 0, 0,
	16240, 4056, 180, 16380,
	16136, 3952, 404, 16364,
	16072, 3780, 664, 16344,
	16040, 3556, 952, 16312,
	16036, 3284, 1268, 16272,
	16052, 2980, 1604, 16224,
	16084, 2648, 1952, 16176,
	16128, 2304, 2304, 16128
};

const uint16_t filter_4tap_16p_117[36] = {
	428, 3236, 428, 0,
	276, 3232, 604, 16364,
	148, 3184, 800, 16340,
	44, 3104, 1016, 16312,
	16344, 2984, 1244, 16284,
	16284, 2832, 1488, 16256,
	16244, 2648, 1732, 16236,
	16220, 2440, 1976, 16220,
	16212, 2216, 2216, 16212
};

const uint16_t filter_4tap_16p_150[36] = {
	696, 2700, 696, 0,
	560, 2700, 848, 16364,
	436, 2676, 1008, 16348,
	328, 2628, 1180, 16336,
	232, 2556, 1356, 16328,
	152, 2460, 1536, 16328,
	84, 2344, 1716, 16332,
	28, 2208, 1888, 16348,
	16376, 2052, 2052, 16376
};

const uint16_t filter_4tap_16p_183[36] = {
	940, 2208, 940, 0,
	832, 2200, 1052, 4,
	728, 2180, 1164, 16,
	628, 2148, 1280, 36,
	536, 2100, 1392, 60,
	448, 2044, 1504, 92,
	368, 1976, 1612, 132,
	296, 1900, 1716, 176,
	232, 1812, 1812, 232
};

const uint16_t filter_2tap_64p[66] = {
	4096, 0,
	4032, 64,
	3968, 128,
	3904, 192,
	3840, 256,
	3776, 320,
	3712, 384,
	3648, 448,
	3584, 512,
	3520, 576,
	3456, 640,
	3392, 704,
	3328, 768,
	3264, 832,
	3200, 896,
	3136, 960,
	3072, 1024,
	3008, 1088,
	2944, 1152,
	2880, 1216,
	2816, 1280,
	2752, 1344,
	2688, 1408,
	2624, 1472,
	2560, 1536,
	2496, 1600,
	2432, 1664,
	2368, 1728,
	2304, 1792,
	2240, 1856,
	2176, 1920,
	2112, 1984,
	2048, 2048 };

const uint16_t filter_3tap_64p_upscale[99] = {
	2048, 2048, 0,
	1960, 2140, 16376,
	1876, 2236, 16364,
	1792, 2328, 16356,
	1708, 2424, 16348,
	1620, 2516, 16336,
	1540, 2612, 16328,
	1456, 2704, 16316,
	1372, 2796, 16308,
	1292, 2884, 16296,
	1212, 2976, 16288,
	1136, 3060, 16280,
	1056, 3148, 16272,
	984, 3228, 16264,
	908, 3312, 16256,
	836, 3388, 16248,
	768, 3464, 16244,
	700, 3536, 16240,
	636, 3604, 16236,
	572, 3668, 16236,
	512, 3728, 16236,
	456, 3784, 16236,
	400, 3836, 16240,
	348, 3884, 16244,
	296, 3928, 16252,
	252, 3964, 16260,
	204, 4000, 16268,
	164, 4028, 16284,
	124, 4052, 16296,
	88, 4072, 16316,
	56, 4084, 16336,
	24, 4092, 16356,
	0, 4096, 0
};

const uint16_t filter_3tap_64p_117[99] = {
	2048, 2048, 0,
	1992, 2104, 16380,
	1936, 2160, 16380,
	1880, 2220, 16376,
	1824, 2276, 16376,
	1768, 2332, 16376,
	1712, 2388, 16376,
	1656, 2444, 16376,
	1600, 2496, 16380,
	1544, 2548, 0,
	1488, 2600, 4,
	1432, 2652, 8,
	1376, 2700, 16,
	1320, 2748, 20,
	1264, 2796, 32,
	1212, 2840, 40,
	1156, 2880, 52,
	1104, 2920, 64,
	1052, 2960, 80,
	1000, 2996, 92,
	948, 3032, 108,
	900, 3060, 128,
	852, 3092, 148,
	804, 3120, 168,
	756, 3144, 192,
	712, 3164, 216,
	668, 3184, 240,
	624, 3200, 268,
	580, 3212, 296,
	540, 3220, 328,
	500, 3228, 360,
	464, 3232, 392,
	428, 3236, 428
};

const uint16_t filter_3tap_64p_150[99] = {
	2048, 2048, 0,
	2004, 2080, 8,
	1960, 2116, 16,
	1916, 2148, 28,
	1872, 2184, 36,
	1824, 2216, 48,
	1780, 2248, 60,
	1736, 2280, 76,
	1692, 2308, 88,
	1648, 2336, 104,
	1604, 2368, 120,
	1560, 2392, 136,
	1516, 2420, 156,
	1472, 2444, 172,
	1428, 2472, 192,
	1384, 2492, 212,
	1340, 2516, 236,
	1296, 2536, 256,
	1252, 2556, 280,
	1212, 2576, 304,
	1168, 2592, 328,
	1124, 2608, 356,
	1084, 2624, 384,
	1044, 2636, 412,
	1004, 2648, 440,
	964, 2660, 468,
	924, 2668, 500,
	884, 2676, 528,
	844, 2684, 560,
	808, 2688, 596,
	768, 2692, 628,
	732, 2696, 664,
	696, 2696, 696
};

const uint16_t filter_3tap_64p_183[99] = {
	2048, 2048, 0,
	2008, 2060, 20,
	1968, 2076, 44,
	1932, 2088, 68,
	1892, 2104, 92,
	1856, 2116, 120,
	1816, 2128, 144,
	1780, 2140, 168,
	1744, 2152, 196,
	1704, 2164, 220,
	1668, 2176, 248,
	1632, 2188, 272,
	1592, 2196, 300,
	1556, 2204, 328,
	1520, 2216, 356,
	1484, 2224, 384,
	1448, 2232, 412,
	1412, 2240, 440,
	1376, 2244, 468,
	1340, 2252, 496,
	1304, 2256, 528,
	1272, 2264, 556,
	1236, 2268, 584,
	1200, 2272, 616,
	1168, 2276, 648,
	1132, 2280, 676,
	1100, 2284, 708,
	1064, 2288, 740,
	1032, 2288, 772,
	996, 2292, 800,
	964, 2292, 832,
	932, 2292, 868,
	900, 2292, 900
};

const uint16_t filter_4tap_64p_upscale[132] = {
	0, 4096, 0, 0,
	16344, 4092, 40, 0,
	16308, 4084, 84, 16380,
	16272, 4072, 132, 16380,
	16240, 4056, 180, 16380,
	16212, 4036, 232, 16376,
	16184, 4012, 288, 16372,
	16160, 3984, 344, 16368,
	16136, 3952, 404, 16364,
	16116, 3916, 464, 16360,
	16100, 3872, 528, 16356,
	16084, 3828, 596, 16348,
	16072, 3780, 664, 16344,
	16060, 3728, 732, 16336,
	16052, 3676, 804, 16328,
	16044, 3616, 876, 16320,
	16040, 3556, 952, 16312,
	16036, 3492, 1028, 16300,
	16032, 3424, 1108, 16292,
	16032, 3356, 1188, 16280,
	16036, 3284, 1268, 16272,
	16036, 3212, 1352, 16260,
	16040, 3136, 1436, 16248,
	16044, 3056, 1520, 16236,
	16052, 2980, 1604, 16224,
	16060, 2896, 1688, 16212,
	16064, 2816, 1776, 16200,
	16076, 2732, 1864, 16188,
	16084, 2648, 1952, 16176,
	16092, 2564, 2040, 16164,
	16104, 2476, 2128, 16152,
	16116, 2388, 2216, 16140,
	16128, 2304, 2304, 16128 };

const uint16_t filter_4tap_64p_117[132] = {
	420, 3248, 420, 0,
	380, 3248, 464, 16380,
	344, 3248, 508, 16372,
	308, 3248, 552, 16368,
	272, 3240, 596, 16364,
	236, 3236, 644, 16356,
	204, 3224, 692, 16352,
	172, 3212, 744, 16344,
	144, 3196, 796, 16340,
	116, 3180, 848, 16332,
	88, 3160, 900, 16324,
	60, 3136, 956, 16320,
	36, 3112, 1012, 16312,
	16, 3084, 1068, 16304,
	16380, 3056, 1124, 16296,
	16360, 3024, 1184, 16292,
	16340, 2992, 1244, 16284,
	16324, 2956, 1304, 16276,
	16308, 2920, 1364, 16268,
	16292, 2880, 1424, 16264,
	16280, 2836, 1484, 16256,
	16268, 2792, 1548, 16252,
	16256, 2748, 1608, 16244,
	16248, 2700, 1668, 16240,
	16240, 2652, 1732, 16232,
	16232, 2604, 1792, 16228,
	16228, 2552, 1856, 16224,
	16220, 2500, 1916, 16220,
	16216, 2444, 1980, 16216,
	16216, 2388, 2040, 16216,
	16212, 2332, 2100, 16212,
	16212, 2276, 2160, 16212,
	16212, 2220, 2220, 16212 };

const uint16_t filter_4tap_64p_150[132] = {
	696, 2700, 696, 0,
	660, 2704, 732, 16380,
	628, 2704, 768, 16376,
	596, 2704, 804, 16372,
	564, 2700, 844, 16364,
	532, 2696, 884, 16360,
	500, 2692, 924, 16356,
	472, 2684, 964, 16352,
	440, 2676, 1004, 16352,
	412, 2668, 1044, 16348,
	384, 2656, 1088, 16344,
	360, 2644, 1128, 16340,
	332, 2632, 1172, 16336,
	308, 2616, 1216, 16336,
	284, 2600, 1260, 16332,
	260, 2580, 1304, 16332,
	236, 2560, 1348, 16328,
	216, 2540, 1392, 16328,
	196, 2516, 1436, 16328,
	176, 2492, 1480, 16324,
	156, 2468, 1524, 16324,
	136, 2440, 1568, 16328,
	120, 2412, 1612, 16328,
	104, 2384, 1656, 16328,
	88, 2352, 1700, 16332,
	72, 2324, 1744, 16332,
	60, 2288, 1788, 16336,
	48, 2256, 1828, 16340,
	36, 2220, 1872, 16344,
	24, 2184, 1912, 16352,
	12, 2148, 1952, 16356,
	4, 2112, 1996, 16364,
	16380, 2072, 2036, 16372 };

const uint16_t filter_4tap_64p_183[132] = {
	944, 2204, 944, 0,
	916, 2204, 972, 0,
	888, 2200, 996, 0,
	860, 2200, 1024, 4,
	832, 2196, 1052, 4,
	808, 2192, 1080, 8,
	780, 2188, 1108, 12,
	756, 2180, 1140, 12,
	728, 2176, 1168, 16,
	704, 2168, 1196, 20,
	680, 2160, 1224, 24,
	656, 2152, 1252, 28,
	632, 2144, 1280, 36,
	608, 2132, 1308, 40,
	584, 2120, 1336, 48,
	560, 2112, 1364, 52,
	536, 2096, 1392, 60,
	516, 2084, 1420, 68,
	492, 2072, 1448, 76,
	472, 2056, 1476, 84,
	452, 2040, 1504, 92,
	428, 2024, 1532, 100,
	408, 2008, 1560, 112,
	392, 1992, 1584, 120,
	372, 1972, 1612, 132,
	352, 1956, 1636, 144,
	336, 1936, 1664, 156,
	316, 1916, 1688, 168,
	300, 1896, 1712, 180,
	284, 1876, 1736, 192,
	268, 1852, 1760, 208,
	252, 1832, 1784, 220,
	236, 1808, 1808, 236 };

const uint16_t *get_filter_3tap_16p(struct fixed31_32 ratio)
{
	if (ratio.value < dal_fixed31_32_one.value)
		return filter_3tap_16p_upscale;
	else if (ratio.value < dal_fixed31_32_from_fraction(4, 3).value)
		return filter_3tap_16p_117;
	else if (ratio.value < dal_fixed31_32_from_fraction(5, 3).value)
		return filter_3tap_16p_150;
	else
		return filter_3tap_16p_183;
}

const uint16_t *get_filter_3tap_64p(struct fixed31_32 ratio)
{
	if (ratio.value < dal_fixed31_32_one.value)
		return filter_3tap_64p_upscale;
	else if (ratio.value < dal_fixed31_32_from_fraction(4, 3).value)
		return filter_3tap_64p_117;
	else if (ratio.value < dal_fixed31_32_from_fraction(5, 3).value)
		return filter_3tap_64p_150;
	else
		return filter_3tap_64p_183;
}

const uint16_t *get_filter_4tap_16p(struct fixed31_32 ratio)
{
	if (ratio.value < dal_fixed31_32_one.value)
		return filter_4tap_16p_upscale;
	else if (ratio.value < dal_fixed31_32_from_fraction(4, 3).value)
		return filter_4tap_16p_117;
	else if (ratio.value < dal_fixed31_32_from_fraction(5, 3).value)
		return filter_4tap_16p_150;
	else
		return filter_4tap_16p_183;
}

const uint16_t *get_filter_4tap_64p(struct fixed31_32 ratio)
{
	if (ratio.value < dal_fixed31_32_one.value)
		return filter_4tap_64p_upscale;
	else if (ratio.value < dal_fixed31_32_from_fraction(4, 3).value)
		return filter_4tap_64p_117;
	else if (ratio.value < dal_fixed31_32_from_fraction(5, 3).value)
		return filter_4tap_64p_150;
	else
		return filter_4tap_64p_183;
}
/*
 * Copyright 2024 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
/*******************************************************************************
 * Size: 24 px
 * Bpp: 4
 * Opts: --user-data-dir=C:\Users\admin\AppData\Roaming\gui-guider --app-path=D:\NXP\GUI-Guider-1.6.1-GA\resources\app.asar --no-sandbox --no-zygote --lang=zh-CN --device-scale-factor=1 --num-raster-threads=4 --enable-main-frame-before-activation --renderer-client-id=5 --time-ticks-at-unix-epoch=-1715050152048656 --launch-time-ticks=26679337691 --mojo-platform-channel-handle=2872 --field-trial-handle=1684,i,12458795301999191956,10128619225379072684,131072 --disable-features=SpareRendererForSitePerProcess,WinRetrieveSuggestionsOnlyOnDemand /prefetch:1
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_24
#define LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_24 1
#endif

#if LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_24

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0025 "%" */
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9f,
    0x60, 0x0, 0x0, 0x0, 0x5c, 0xfd, 0x90, 0x0,
    0x0, 0x2, 0xfd, 0x0, 0x0, 0x0, 0x6, 0xff,
    0xce, 0xfd, 0x0, 0x0, 0xa, 0xf5, 0x0, 0x0,
    0x0, 0xf, 0xf7, 0x1, 0xff, 0x60, 0x0, 0x2f,
    0xc0, 0x0, 0x0, 0x0, 0x3f, 0xf2, 0x0, 0xcf,
    0xa0, 0x0, 0xbf, 0x40, 0x0, 0x0, 0x0, 0x4f,
    0xf1, 0x0, 0xaf, 0xb0, 0x3, 0xfb, 0x0, 0x0,
    0x0, 0x0, 0x2f, 0xf4, 0x0, 0xdf, 0x90, 0xc,
    0xf3, 0x0, 0x0, 0x0, 0x0, 0xd, 0xfa, 0x15,
    0xff, 0x30, 0x4f, 0xa0, 0x0, 0x0, 0x0, 0x0,
    0x3, 0xef, 0xff, 0xf8, 0x0, 0xdf, 0x20, 0x1a,
    0xee, 0xb2, 0x0, 0x0, 0x16, 0x98, 0x40, 0x5,
    0xf9, 0x1, 0xdf, 0xdc, 0xfe, 0x20, 0x0, 0x0,
    0x0, 0x0, 0xe, 0xf1, 0x7, 0xfd, 0x0, 0xcf,
    0x90, 0x0, 0x0, 0x0, 0x0, 0x6f, 0x80, 0xc,
    0xf8, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0x0, 0x0,
    0xee, 0x0, 0xe, 0xf6, 0x0, 0x5f, 0xf0, 0x0,
    0x0, 0x0, 0x8, 0xf7, 0x0, 0xe, 0xf6, 0x0,
    0x5f, 0xf0, 0x0, 0x0, 0x0, 0x1f, 0xe0, 0x0,
    0xc, 0xf8, 0x0, 0x7f, 0xe0, 0x0, 0x0, 0x0,
    0x9f, 0x60, 0x0, 0x7, 0xfd, 0x0, 0xcf, 0x90,
    0x0, 0x0, 0x2, 0xfd, 0x0, 0x0, 0x1, 0xef,
    0xdd, 0xfe, 0x20, 0x0, 0x0, 0xa, 0xf4, 0x0,
    0x0, 0x0, 0x1a, 0xee, 0xb2, 0x0,

    /* U+002F "/" */
    0x0, 0x0, 0x0, 0x0, 0x7, 0x71, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xe0, 0x0, 0x0, 0x0, 0x0,
    0xaf, 0x80, 0x0, 0x0, 0x0, 0x0, 0xff, 0x20,
    0x0, 0x0, 0x0, 0x6, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0xc, 0xf6, 0x0, 0x0, 0x0, 0x0, 0x2f,
    0xf1, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xb0, 0x0,
    0x0, 0x0, 0x0, 0xef, 0x50, 0x0, 0x0, 0x0,
    0x4, 0xfe, 0x0, 0x0, 0x0, 0x0, 0xa, 0xf9,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xf3, 0x0, 0x0,
    0x0, 0x0, 0x6f, 0xd0, 0x0, 0x0, 0x0, 0x0,
    0xcf, 0x70, 0x0, 0x0, 0x0, 0x2, 0xff, 0x10,
    0x0, 0x0, 0x0, 0x8, 0xfb, 0x0, 0x0, 0x0,
    0x0, 0xd, 0xf5, 0x0, 0x0, 0x0, 0x0, 0x3f,
    0xe0, 0x0, 0x0, 0x0, 0x0, 0x9f, 0x90, 0x0,
    0x0, 0x0, 0x0, 0xff, 0x30, 0x0, 0x0, 0x0,
    0x5, 0xfd, 0x0, 0x0, 0x0, 0x0, 0xb, 0xf7,
    0x0, 0x0, 0x0, 0x0, 0x1f, 0xf1, 0x0, 0x0,
    0x0, 0x0,

    /* U+0030 "0" */
    0x0, 0x5, 0xbe, 0xfd, 0x81, 0x0, 0x0, 0xa,
    0xff, 0xff, 0xff, 0xe2, 0x0, 0x7, 0xff, 0xc5,
    0x48, 0xff, 0xd0, 0x0, 0xef, 0xb0, 0x0, 0x6,
    0xff, 0x50, 0x5f, 0xf3, 0x0, 0x0, 0xd, 0xfc,
    0xa, 0xfe, 0x0, 0x0, 0x0, 0x8f, 0xf0, 0xcf,
    0xb0, 0x0, 0x0, 0x5, 0xff, 0x2e, 0xfa, 0x0,
    0x0, 0x0, 0x4f, 0xf4, 0xff, 0x90, 0x0, 0x0,
    0x3, 0xff, 0x5d, 0xfa, 0x0, 0x0, 0x0, 0x4f,
    0xf4, 0xcf, 0xb0, 0x0, 0x0, 0x5, 0xff, 0x2a,
    0xfe, 0x0, 0x0, 0x0, 0x8f, 0xf0, 0x5f, 0xf3,
    0x0, 0x0, 0xd, 0xfc, 0x0, 0xef, 0xb0, 0x0,
    0x6, 0xff, 0x50, 0x7, 0xff, 0xc5, 0x48, 0xff,
    0xd0, 0x0, 0xa, 0xff, 0xff, 0xff, 0xe2, 0x0,
    0x0, 0x5, 0xbe, 0xfd, 0x81, 0x0, 0x0,

    /* U+0031 "1" */
    0x0, 0x0, 0x9f, 0xf0, 0x2, 0xcf, 0xff, 0x3b,
    0xff, 0xff, 0xf8, 0xff, 0xcb, 0xff, 0x8d, 0x60,
    0x9f, 0xf1, 0x0, 0x9, 0xff, 0x0, 0x0, 0x9f,
    0xf0, 0x0, 0x9, 0xff, 0x0, 0x0, 0x9f, 0xf0,
    0x0, 0x9, 0xff, 0x0, 0x0, 0x9f, 0xf0, 0x0,
    0x9, 0xff, 0x0, 0x0, 0x9f, 0xf0, 0x0, 0x9,
    0xff, 0x0, 0x0, 0x9f, 0xf0, 0x0, 0x9, 0xff,
    0x0, 0x0, 0x9f, 0xf0,

    /* U+0032 "2" */
    0x0, 0x3, 0xad, 0xfd, 0xa3, 0x0, 0x0, 0x8,
    0xff, 0xff, 0xff, 0xf8, 0x0, 0x6, 0xff, 0xd6,
    0x46, 0xdf, 0xf5, 0x1, 0xef, 0xd0, 0x0, 0x0,
    0xef, 0xc0, 0x4f, 0xf5, 0x0, 0x0, 0x9, 0xff,
    0x7, 0xff, 0x20, 0x0, 0x0, 0x9f, 0xf0, 0x24,
    0x40, 0x0, 0x0, 0xd, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x8, 0xff, 0x40, 0x0, 0x0, 0x0, 0x8,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x2c, 0xff, 0x90,
    0x0, 0x0, 0x0, 0x6f, 0xff, 0x60, 0x0, 0x0,
    0x0, 0xaf, 0xfb, 0x10, 0x0, 0x0, 0x0, 0xcf,
    0xf7, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x2f, 0xfd, 0x55, 0x55, 0x55,
    0x55, 0x6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf1,
    0x9f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x10,

    /* U+0033 "3" */
    0x0, 0x5, 0xbd, 0xfd, 0xb5, 0x0, 0x0, 0xc,
    0xff, 0xff, 0xff, 0xfc, 0x0, 0xa, 0xff, 0xb6,
    0x56, 0xcf, 0xf9, 0x3, 0xff, 0x80, 0x0, 0x0,
    0xdf, 0xd0, 0x7f, 0xf1, 0x0, 0x0, 0x9, 0xff,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xcf, 0xd0, 0x0,
    0x0, 0x0, 0x2, 0x9f, 0xf5, 0x0, 0x0, 0x0,
    0xff, 0xff, 0xc4, 0x0, 0x0, 0x0, 0xf, 0xff,
    0xfe, 0x80, 0x0, 0x0, 0x0, 0x0, 0x28, 0xff,
    0xa0, 0x0, 0x0, 0x0, 0x0, 0x8, 0xff, 0x28,
    0x96, 0x0, 0x0, 0x0, 0x4f, 0xf5, 0xbf, 0xe0,
    0x0, 0x0, 0x5, 0xff, 0x37, 0xff, 0x70, 0x0,
    0x0, 0xdf, 0xf0, 0xd, 0xff, 0xa5, 0x47, 0xef,
    0xf7, 0x0, 0x2e, 0xff, 0xff, 0xff, 0xfa, 0x0,
    0x0, 0x7, 0xce, 0xfd, 0xa3, 0x0, 0x0,

    /* U+0034 "4" */
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf5, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0x2e, 0xff, 0xf5, 0x0, 0x0, 0x0, 0x0,
    0xdf, 0xbf, 0xf5, 0x0, 0x0, 0x0, 0xa, 0xfb,
    0x2f, 0xf5, 0x0, 0x0, 0x0, 0x7f, 0xe1, 0x2f,
    0xf5, 0x0, 0x0, 0x4, 0xff, 0x30, 0x2f, 0xf5,
    0x0, 0x0, 0x1e, 0xf6, 0x0, 0x2f, 0xf5, 0x0,
    0x0, 0xcf, 0x90, 0x0, 0x2f, 0xf5, 0x0, 0x9,
    0xfc, 0x0, 0x0, 0x2f, 0xf5, 0x0, 0x5f, 0xe1,
    0x0, 0x0, 0x2f, 0xf5, 0x0, 0x8f, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x8f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xfe, 0x11, 0x11, 0x11, 0x11, 0x4f,
    0xf6, 0x11, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xf5,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xf5, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2f, 0xf5, 0x0,

    /* U+0035 "5" */
    0xc, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0, 0xef,
    0xff, 0xff, 0xff, 0xff, 0x90, 0xf, 0xf9, 0x55,
    0x55, 0x55, 0x53, 0x1, 0xff, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x3f, 0xf2, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0x6, 0xbe, 0xeb, 0x40, 0x0, 0x6f,
    0xfc, 0xff, 0xff, 0xff, 0x90, 0x8, 0xff, 0xf8,
    0x53, 0x6e, 0xff, 0x50, 0x9f, 0xf4, 0x0, 0x0,
    0x1e, 0xfe, 0x0, 0x0, 0x0, 0x0, 0x0, 0x7f,
    0xf2, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x42,
    0x21, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0xcf, 0xc0,
    0x0, 0x0, 0x8, 0xff, 0x18, 0xff, 0x40, 0x0,
    0x3, 0xff, 0xc0, 0x1e, 0xff, 0x85, 0x59, 0xff,
    0xf2, 0x0, 0x2e, 0xff, 0xff, 0xff, 0xe4, 0x0,
    0x0, 0x7, 0xce, 0xec, 0x80, 0x0, 0x0,

    /* U+0036 "6" */
    0x0, 0x3, 0xae, 0xfe, 0xc6, 0x0, 0x0, 0x6,
    0xff, 0xff, 0xff, 0xfc, 0x0, 0x3, 0xff, 0xb6,
    0x35, 0xbf, 0xf8, 0x0, 0xbf, 0x90, 0x0, 0x0,
    0xbf, 0xd0, 0x2f, 0xe0, 0x0, 0x0, 0x0, 0x0,
    0x8, 0xfb, 0x6, 0xcf, 0xeb, 0x50, 0x0, 0xaf,
    0x9b, 0xff, 0xff, 0xff, 0xa0, 0xc, 0xff, 0xfb,
    0x43, 0x6d, 0xff, 0x60, 0xef, 0xfa, 0x0, 0x0,
    0xe, 0xfe, 0xe, 0xff, 0x10, 0x0, 0x0, 0x6f,
    0xf2, 0xcf, 0xe0, 0x0, 0x0, 0x3, 0xff, 0x5a,
    0xfe, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x7f, 0xf2,
    0x0, 0x0, 0x7, 0xff, 0x11, 0xff, 0xb0, 0x0,
    0x2, 0xff, 0xd0, 0x8, 0xff, 0xc5, 0x47, 0xef,
    0xf3, 0x0, 0xb, 0xff, 0xff, 0xff, 0xf5, 0x0,
    0x0, 0x5, 0xbe, 0xfc, 0x91, 0x0, 0x0,

    /* U+0037 "7" */
    0x8f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff,
    0xff, 0xff, 0xff, 0xff, 0x36, 0x66, 0x66, 0x66,
    0x6e, 0xfc, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xf6,
    0x0, 0x0, 0x0, 0x0, 0x9f, 0xf0, 0x0, 0x0,
    0x0, 0x0, 0xff, 0x90, 0x0, 0x0, 0x0, 0x6,
    0xff, 0x20, 0x0, 0x0, 0x0, 0xd, 0xfc, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xe0, 0x0, 0x0, 0x0, 0x2, 0xff,
    0x80, 0x0, 0x0, 0x0, 0x8, 0xff, 0x20, 0x0,
    0x0, 0x0, 0xe, 0xfb, 0x0, 0x0, 0x0, 0x0,
    0x6f, 0xf5, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xe0,
    0x0, 0x0, 0x0, 0x3, 0xff, 0x80, 0x0, 0x0,
    0x0, 0xa, 0xff, 0x10, 0x0, 0x0,

    /* U+0038 "8" */
    0x0, 0x1, 0x8c, 0xef, 0xda, 0x30, 0x0, 0x0,
    0x4e, 0xff, 0xff, 0xff, 0xf9, 0x0, 0x1, 0xef,
    0xe7, 0x32, 0x5c, 0xff, 0x60, 0x6, 0xff, 0x30,
    0x0, 0x0, 0xcf, 0xc0, 0x8, 0xfe, 0x0, 0x0,
    0x0, 0x8f, 0xf0, 0x6, 0xff, 0x10, 0x0, 0x0,
    0xbf, 0xc0, 0x0, 0xdf, 0xd4, 0x10, 0x29, 0xff,
    0x40, 0x0, 0x19, 0xff, 0xff, 0xff, 0xd4, 0x0,
    0x0, 0x5e, 0xff, 0xff, 0xff, 0xfa, 0x0, 0x4,
    0xff, 0xc4, 0x10, 0x29, 0xff, 0xb0, 0xd, 0xfd,
    0x0, 0x0, 0x0, 0x7f, 0xf4, 0x1f, 0xf8, 0x0,
    0x0, 0x0, 0x1f, 0xf7, 0x1f, 0xf8, 0x0, 0x0,
    0x0, 0x1f, 0xf7, 0xe, 0xfd, 0x10, 0x0, 0x0,
    0x8f, 0xf4, 0x6, 0xff, 0xe6, 0x33, 0x5a, 0xff,
    0xc0, 0x0, 0x8f, 0xff, 0xff, 0xff, 0xfd, 0x10,
    0x0, 0x2, 0x9c, 0xef, 0xdb, 0x50, 0x0,

    /* U+0039 "9" */
    0x0, 0x7, 0xbe, 0xfd, 0x81, 0x0, 0x0, 0x3d,
    0xff, 0xff, 0xff, 0xe3, 0x0, 0xd, 0xff, 0x94,
    0x47, 0xff, 0xe0, 0x8, 0xff, 0x50, 0x0, 0x2,
    0xff, 0x60, 0xcf, 0xc0, 0x0, 0x0, 0xa, 0xfd,
    0xe, 0xfa, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0xdf,
    0xc0, 0x0, 0x0, 0x9, 0xff, 0x3a, 0xff, 0x40,
    0x0, 0x2, 0xff, 0xf5, 0x2f, 0xff, 0x73, 0x36,
    0xef, 0xff, 0x50, 0x6f, 0xff, 0xff, 0xfe, 0x5f,
    0xf3, 0x0, 0x2a, 0xdf, 0xe9, 0x14, 0xff, 0x10,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf0, 0x58, 0x80,
    0x0, 0x0, 0xe, 0xf9, 0x5, 0xff, 0x50, 0x0,
    0x8, 0xff, 0x20, 0xe, 0xff, 0x84, 0x5a, 0xff,
    0xa0, 0x0, 0x3f, 0xff, 0xff, 0xff, 0xb0, 0x0,
    0x0, 0x19, 0xcf, 0xfc, 0x60, 0x0, 0x0,

    /* U+003A ":" */
    0xc, 0xf7, 0x5, 0xff, 0xf0, 0x2f, 0xfd, 0x0,
    0x46, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x47,
    0x10, 0x3f, 0xfd, 0x5, 0xff, 0xf0, 0xc, 0xe6,
    0x0,

    /* U+0041 "A" */
    0x0, 0x0, 0x0, 0x9f, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xf, 0xff, 0xf2, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x6, 0xff, 0xef, 0x80, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xcf, 0xb8, 0xfe, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x2f, 0xf5, 0x2f, 0xf5,
    0x0, 0x0, 0x0, 0x0, 0x8, 0xfe, 0x0, 0xcf,
    0xb0, 0x0, 0x0, 0x0, 0x0, 0xef, 0x80, 0x6,
    0xff, 0x10, 0x0, 0x0, 0x0, 0x5f, 0xf2, 0x0,
    0xf, 0xf7, 0x0, 0x0, 0x0, 0xb, 0xfc, 0x0,
    0x0, 0x9f, 0xd0, 0x0, 0x0, 0x1, 0xff, 0x60,
    0x0, 0x3, 0xff, 0x40, 0x0, 0x0, 0x7f, 0xff,
    0xff, 0xff, 0xff, 0xfa, 0x0, 0x0, 0xd, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf1, 0x0, 0x4, 0xff,
    0x63, 0x33, 0x33, 0x34, 0xff, 0x60, 0x0, 0xaf,
    0xe0, 0x0, 0x0, 0x0, 0xc, 0xfc, 0x0, 0x1f,
    0xf9, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf3, 0x6,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x2, 0xff, 0x90,
    0xcf, 0xe0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xff,
    0x0,

    /* U+0042 "B" */
    0x4f, 0xff, 0xff, 0xff, 0xfd, 0xb5, 0x0, 0x4,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xfa, 0x0, 0x4f,
    0xf7, 0x33, 0x33, 0x46, 0xdf, 0xf6, 0x4, 0xff,
    0x40, 0x0, 0x0, 0x1, 0xff, 0xa0, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0xd, 0xfc, 0x4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xff, 0x90, 0x4f, 0xf4, 0x0,
    0x0, 0x13, 0xbf, 0xe2, 0x4, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xb2, 0x0, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xfe, 0x80, 0x4, 0xff, 0x62, 0x22, 0x23,
    0x5a, 0xff, 0xb0, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x8, 0xff, 0x34, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x3f, 0xf6, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x3,
    0xff, 0x74, 0xff, 0x40, 0x0, 0x0, 0x0, 0x9f,
    0xf4, 0x4f, 0xf7, 0x33, 0x33, 0x35, 0xaf, 0xfe,
    0x4, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x30,
    0x4f, 0xff, 0xff, 0xff, 0xfe, 0xc8, 0x10, 0x0,

    /* U+0043 "C" */
    0x0, 0x0, 0x5, 0xad, 0xff, 0xca, 0x40, 0x0,
    0x0, 0x0, 0x1c, 0xff, 0xff, 0xff, 0xff, 0xc2,
    0x0, 0x0, 0x1e, 0xff, 0xea, 0x76, 0x8d, 0xff,
    0xd1, 0x0, 0xa, 0xff, 0xa0, 0x0, 0x0, 0x7,
    0xff, 0xa0, 0x2, 0xff, 0xb0, 0x0, 0x0, 0x0,
    0xa, 0xff, 0x0, 0x9f, 0xf2, 0x0, 0x0, 0x0,
    0x0, 0x27, 0x72, 0xc, 0xfd, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xef, 0xb0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xef, 0xb0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xc, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xaf, 0xf2,
    0x0, 0x0, 0x0, 0x0, 0x3f, 0xf5, 0x3, 0xff,
    0xa0, 0x0, 0x0, 0x0, 0xa, 0xff, 0x0, 0xb,
    0xff, 0x90, 0x0, 0x0, 0x8, 0xff, 0x90, 0x0,
    0x2e, 0xff, 0xd9, 0x76, 0x8d, 0xff, 0xb0, 0x0,
    0x0, 0x2d, 0xff, 0xff, 0xff, 0xff, 0xa0, 0x0,
    0x0, 0x0, 0x5, 0xad, 0xff, 0xca, 0x30, 0x0,
    0x0,

    /* U+0044 "D" */
    0x4f, 0xff, 0xff, 0xff, 0xeb, 0x60, 0x0, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x0,
    0x4f, 0xf7, 0x44, 0x46, 0x8c, 0xff, 0xf5, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x6e, 0xff, 0x10,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x6, 0xff, 0x80,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xd0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xf0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf2,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf3,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf2,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x9f, 0xf0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xd0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x6, 0xff, 0x80,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x6f, 0xfe, 0x10,
    0x4f, 0xf7, 0x44, 0x46, 0x9d, 0xff, 0xf5, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0x40, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0xea, 0x60, 0x0, 0x0,

    /* U+0045 "E" */
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x4f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x4f, 0xf7,
    0x44, 0x44, 0x44, 0x44, 0x40, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x60, 0x4f,
    0xf7, 0x44, 0x44, 0x44, 0x44, 0x10, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xf7, 0x44, 0x44, 0x44, 0x44,
    0x41, 0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6,

    /* U+0046 "F" */
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0x44, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xf4, 0x4f, 0xf7, 0x44,
    0x44, 0x44, 0x44, 0x14, 0xff, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xc0, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xfc, 0x4, 0xff, 0x74, 0x44, 0x44, 0x44,
    0x30, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x4,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+0047 "G" */
    0x0, 0x0, 0x4, 0x9d, 0xff, 0xdb, 0x70, 0x0,
    0x0, 0x0, 0xb, 0xff, 0xff, 0xff, 0xff, 0xe5,
    0x0, 0x0, 0xc, 0xff, 0xe9, 0x76, 0x7c, 0xff,
    0xf4, 0x0, 0xa, 0xff, 0xa1, 0x0, 0x0, 0x4,
    0xff, 0xe0, 0x3, 0xff, 0xc0, 0x0, 0x0, 0x0,
    0x7, 0xff, 0x40, 0x9f, 0xf3, 0x0, 0x0, 0x0,
    0x0, 0x6, 0x63, 0xd, 0xfe, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0xb0, 0x0, 0x0,
    0x34, 0x44, 0x44, 0x42, 0xf, 0xf9, 0x0, 0x0,
    0xb, 0xff, 0xff, 0xff, 0x90, 0xff, 0xb0, 0x0,
    0x0, 0xbf, 0xff, 0xff, 0xf9, 0xd, 0xfd, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xff, 0x90, 0x9f, 0xf2,
    0x0, 0x0, 0x0, 0x0, 0xf, 0xf9, 0x3, 0xff,
    0xb0, 0x0, 0x0, 0x0, 0x0, 0xff, 0x90, 0xa,
    0xff, 0xa1, 0x0, 0x0, 0x0, 0x3f, 0xf9, 0x0,
    0x1d, 0xff, 0xea, 0x85, 0x68, 0xcf, 0xff, 0x90,
    0x0, 0x1b, 0xff, 0xff, 0xff, 0xff, 0xff, 0x80,
    0x0, 0x0, 0x3, 0x9d, 0xef, 0xed, 0xa6, 0x0,
    0x0,

    /* U+0048 "H" */
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xe4,
    0xff, 0x40, 0x0, 0x0, 0x0, 0xb, 0xfe, 0x4f,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xe4, 0xff,
    0x40, 0x0, 0x0, 0x0, 0xb, 0xfe, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0xe4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xb, 0xfe, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0xbf, 0xe4, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xfe, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xe4, 0xff, 0x74, 0x44, 0x44,
    0x44, 0x4c, 0xfe, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0xbf, 0xe4, 0xff, 0x40, 0x0, 0x0, 0x0,
    0xb, 0xfe, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0xbf, 0xe4, 0xff, 0x40, 0x0, 0x0, 0x0, 0xb,
    0xfe, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xbf,
    0xe4, 0xff, 0x40, 0x0, 0x0, 0x0, 0xb, 0xfe,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xbf, 0xe0,

    /* U+0049 "I" */
    0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4,
    0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4,
    0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4,
    0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4, 0x4f, 0xf4,
    0x4f, 0xf4,

    /* U+004A "J" */
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1,
    0x0, 0x0, 0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x7f, 0xf1, 0x0, 0x0, 0x0, 0x0,
    0x7f, 0xf1, 0x8d, 0xd0, 0x0, 0x0, 0x8f, 0xf1,
    0x8f, 0xf1, 0x0, 0x0, 0xaf, 0xf0, 0x5f, 0xf6,
    0x0, 0x1, 0xff, 0xd0, 0xe, 0xff, 0x96, 0x7e,
    0xff, 0x60, 0x4, 0xff, 0xff, 0xff, 0xfc, 0x0,
    0x0, 0x2a, 0xdf, 0xdb, 0x60, 0x0,

    /* U+004B "K" */
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x1d, 0xff, 0x60,
    0x4f, 0xf4, 0x0, 0x0, 0x1, 0xdf, 0xf5, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x1d, 0xff, 0x50, 0x0,
    0x4f, 0xf4, 0x0, 0x1, 0xdf, 0xf4, 0x0, 0x0,
    0x4f, 0xf4, 0x0, 0x1d, 0xff, 0x40, 0x0, 0x0,
    0x4f, 0xf4, 0x1, 0xdf, 0xf3, 0x0, 0x0, 0x0,
    0x4f, 0xf4, 0x1d, 0xfe, 0x30, 0x0, 0x0, 0x0,
    0x4f, 0xf6, 0xdf, 0xf8, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xff, 0xff, 0x50, 0x0, 0x0, 0x0,
    0x4f, 0xff, 0xd4, 0xef, 0xf4, 0x0, 0x0, 0x0,
    0x4f, 0xfd, 0x10, 0x3f, 0xff, 0x30, 0x0, 0x0,
    0x4f, 0xf4, 0x0, 0x4, 0xff, 0xe2, 0x0, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x6f, 0xfd, 0x10, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x8, 0xff, 0xc0, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0xaf, 0xfb, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0xc, 0xff, 0xa0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x1, 0xdf, 0xf8,

    /* U+004C "L" */
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff,
    0x40, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x4f,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0x40, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x4,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0x4, 0xff, 0x40, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf7, 0x44, 0x44, 0x44,
    0x44, 0x34, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfb,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb0,

    /* U+004D "M" */
    0x4f, 0xff, 0x0, 0x0, 0x0, 0x0, 0x0, 0x6,
    0xff, 0xd4, 0xff, 0xf6, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xdf, 0xfd, 0x4f, 0xff, 0xd0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xff, 0xd4, 0xff, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xb, 0xff, 0xfd, 0x4f, 0xff,
    0xfb, 0x0, 0x0, 0x0, 0x3, 0xff, 0xff, 0xd4,
    0xff, 0xaf, 0xf3, 0x0, 0x0, 0x0, 0x9f, 0xdc,
    0xfd, 0x4f, 0xf5, 0xef, 0xa0, 0x0, 0x0, 0x1f,
    0xf7, 0xbf, 0xd4, 0xff, 0x47, 0xff, 0x10, 0x0,
    0x7, 0xff, 0xb, 0xfd, 0x4f, 0xf4, 0x1f, 0xf8,
    0x0, 0x0, 0xef, 0x90, 0xbf, 0xd4, 0xff, 0x40,
    0x9f, 0xe0, 0x0, 0x5f, 0xf2, 0xb, 0xfd, 0x4f,
    0xf4, 0x2, 0xff, 0x60, 0xc, 0xfb, 0x0, 0xbf,
    0xd4, 0xff, 0x40, 0xb, 0xfd, 0x3, 0xff, 0x40,
    0xb, 0xfd, 0x4f, 0xf4, 0x0, 0x4f, 0xf4, 0xaf,
    0xd0, 0x0, 0xbf, 0xd4, 0xff, 0x40, 0x0, 0xdf,
    0xcf, 0xf6, 0x0, 0xb, 0xfd, 0x4f, 0xf4, 0x0,
    0x7, 0xff, 0xff, 0x0, 0x0, 0xbf, 0xd4, 0xff,
    0x40, 0x0, 0xf, 0xff, 0x80, 0x0, 0xb, 0xfd,
    0x4f, 0xf4, 0x0, 0x0, 0x9f, 0xf2, 0x0, 0x0,
    0xbf, 0xd0,

    /* U+004E "N" */
    0x4f, 0xfa, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xc4,
    0xff, 0xf5, 0x0, 0x0, 0x0, 0xd, 0xfc, 0x4f,
    0xff, 0xe1, 0x0, 0x0, 0x0, 0xdf, 0xc4, 0xff,
    0xff, 0xb0, 0x0, 0x0, 0xd, 0xfc, 0x4f, 0xfb,
    0xff, 0x60, 0x0, 0x0, 0xdf, 0xc4, 0xff, 0x4b,
    0xff, 0x20, 0x0, 0xd, 0xfc, 0x4f, 0xf4, 0x1e,
    0xfc, 0x0, 0x0, 0xdf, 0xc4, 0xff, 0x40, 0x5f,
    0xf8, 0x0, 0xd, 0xfc, 0x4f, 0xf4, 0x0, 0xaf,
    0xf3, 0x0, 0xdf, 0xc4, 0xff, 0x40, 0x1, 0xef,
    0xd0, 0xd, 0xfc, 0x4f, 0xf4, 0x0, 0x4, 0xff,
    0x90, 0xdf, 0xc4, 0xff, 0x40, 0x0, 0x9, 0xff,
    0x4d, 0xfc, 0x4f, 0xf4, 0x0, 0x0, 0xd, 0xfe,
    0xef, 0xc4, 0xff, 0x40, 0x0, 0x0, 0x3f, 0xff,
    0xfc, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x7f, 0xff,
    0xc4, 0xff, 0x40, 0x0, 0x0, 0x0, 0xcf, 0xfc,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x2, 0xff, 0xc0,

    /* U+004F "O" */
    0x0, 0x0, 0x4, 0x9d, 0xef, 0xeb, 0x71, 0x0,
    0x0, 0x0, 0x1, 0xbf, 0xff, 0xff, 0xff, 0xfe,
    0x50, 0x0, 0x0, 0x1d, 0xff, 0xea, 0x76, 0x8c,
    0xff, 0xf7, 0x0, 0x0, 0xaf, 0xfb, 0x10, 0x0,
    0x0, 0x5e, 0xff, 0x30, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xc0, 0x9, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0xaf, 0xf2, 0xd, 0xfd,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xf6, 0xf,
    0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xf8,
    0xf, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xf9, 0xf, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3f, 0xf8, 0xd, 0xfd, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x5f, 0xf6, 0x9, 0xff, 0x30, 0x0, 0x0,
    0x0, 0x0, 0xaf, 0xf2, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xc0, 0x0, 0xbf, 0xfb,
    0x10, 0x0, 0x0, 0x5e, 0xff, 0x40, 0x0, 0x1d,
    0xff, 0xea, 0x76, 0x8c, 0xff, 0xf7, 0x0, 0x0,
    0x1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0x60, 0x0,
    0x0, 0x0, 0x4, 0x9d, 0xff, 0xeb, 0x71, 0x0,
    0x0,

    /* U+0050 "P" */
    0x4f, 0xff, 0xff, 0xff, 0xec, 0x92, 0x0, 0x4f,
    0xff, 0xff, 0xff, 0xff, 0xff, 0x70, 0x4f, 0xf7,
    0x44, 0x44, 0x59, 0xff, 0xf3, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x3f, 0xf9, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0xd, 0xfc, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0xc, 0xfd, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x1f,
    0xfa, 0x4f, 0xf4, 0x0, 0x0, 0x14, 0xcf, 0xf6,
    0x4f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xb0, 0x4f,
    0xff, 0xff, 0xff, 0xff, 0xe6, 0x0, 0x4f, 0xf7,
    0x44, 0x44, 0x31, 0x0, 0x0, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0x0,

    /* U+0051 "Q" */
    0x0, 0x0, 0x4, 0x9d, 0xef, 0xeb, 0x71, 0x0,
    0x0, 0x0, 0x1, 0xbf, 0xff, 0xff, 0xff, 0xff,
    0x60, 0x0, 0x0, 0x1d, 0xff, 0xea, 0x76, 0x8c,
    0xff, 0xf7, 0x0, 0x0, 0xaf, 0xfb, 0x10, 0x0,
    0x0, 0x5e, 0xff, 0x40, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xc0, 0x9, 0xff, 0x30,
    0x0, 0x0, 0x0, 0x0, 0xaf, 0xf2, 0xd, 0xfd,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x5f, 0xf6, 0xf,
    0xfb, 0x0, 0x0, 0x0, 0x0, 0x0, 0x3f, 0xf8,
    0xf, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x0, 0x1f,
    0xf9, 0xf, 0xfb, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x2f, 0xf8, 0xd, 0xfd, 0x0, 0x0, 0x0, 0x7d,
    0x10, 0x4f, 0xf6, 0x9, 0xff, 0x30, 0x0, 0x0,
    0xdf, 0xd1, 0xaf, 0xf1, 0x3, 0xff, 0xc0, 0x0,
    0x0, 0x1e, 0xfd, 0xff, 0xb0, 0x0, 0xbf, 0xfb,
    0x10, 0x0, 0x2, 0xef, 0xff, 0x20, 0x0, 0x1d,
    0xff, 0xea, 0x76, 0x7b, 0xff, 0xfb, 0x0, 0x0,
    0x1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0x40,
    0x0, 0x0, 0x4, 0x9d, 0xff, 0xdb, 0x60, 0xbf,
    0xe1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1e, 0xc1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x3, 0x0,

    /* U+0052 "R" */
    0x4f, 0xff, 0xff, 0xff, 0xfd, 0xb4, 0x0, 0x4,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xf9, 0x0, 0x4f,
    0xf7, 0x44, 0x44, 0x57, 0xef, 0xf6, 0x4, 0xff,
    0x40, 0x0, 0x0, 0x1, 0xff, 0xb0, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0xb, 0xfe, 0x4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xbf, 0xd0, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x2f, 0xf9, 0x4, 0xff, 0x74, 0x44,
    0x45, 0x8e, 0xfd, 0x10, 0x4f, 0xff, 0xff, 0xff,
    0xff, 0xf9, 0x10, 0x4, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xf7, 0x0, 0x4f, 0xf4, 0x0, 0x0, 0x14,
    0xdf, 0xf3, 0x4, 0xff, 0x40, 0x0, 0x0, 0x3,
    0xff, 0x80, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0xf,
    0xfa, 0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0xdf,
    0xc0, 0x4f, 0xf4, 0x0, 0x0, 0x0, 0xb, 0xfe,
    0x4, 0xff, 0x40, 0x0, 0x0, 0x0, 0x8f, 0xf1,
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x3, 0xff, 0x90,

    /* U+0053 "S" */
    0x0, 0x0, 0x6b, 0xdf, 0xec, 0x92, 0x0, 0x0,
    0x3, 0xff, 0xff, 0xff, 0xff, 0xf8, 0x0, 0x2,
    0xff, 0xf9, 0x65, 0x69, 0xff, 0xf7, 0x0, 0x8f,
    0xf3, 0x0, 0x0, 0x2, 0xef, 0xe0, 0xa, 0xfe,
    0x0, 0x0, 0x0, 0x7, 0xff, 0x30, 0x7f, 0xf4,
    0x0, 0x0, 0x0, 0x3, 0x31, 0x2, 0xff, 0xf9,
    0x30, 0x0, 0x0, 0x0, 0x0, 0x3, 0xdf, 0xff,
    0xe9, 0x40, 0x0, 0x0, 0x0, 0x0, 0x39, 0xef,
    0xff, 0xf9, 0x20, 0x0, 0x0, 0x0, 0x0, 0x37,
    0xcf, 0xff, 0x60, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x3d, 0xff, 0x42, 0xcc, 0x50, 0x0, 0x0, 0x0,
    0x1f, 0xfa, 0xf, 0xfb, 0x0, 0x0, 0x0, 0x0,
    0xef, 0xb0, 0xbf, 0xf6, 0x0, 0x0, 0x0, 0x6f,
    0xf8, 0x2, 0xef, 0xfc, 0x76, 0x68, 0xcf, 0xff,
    0x20, 0x3, 0xef, 0xff, 0xff, 0xff, 0xfe, 0x40,
    0x0, 0x0, 0x6b, 0xdf, 0xfd, 0xb6, 0x0, 0x0,

    /* U+0054 "T" */
    0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x6a,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf6, 0x24,
    0x44, 0x44, 0xef, 0xc4, 0x44, 0x44, 0x10, 0x0,
    0x0, 0xe, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0xef, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xe, 0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0xef, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe,
    0xfa, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xef,
    0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xfa,
    0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0xef, 0xa0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xe, 0xfa, 0x0,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xef, 0xa0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xe, 0xfa, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xef, 0xa0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xe, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xef, 0xa0, 0x0, 0x0, 0x0,

    /* U+0055 "U" */
    0x4f, 0xf4, 0x0, 0x0, 0x0, 0x0, 0xcf, 0xc4,
    0xff, 0x40, 0x0, 0x0, 0x0, 0xc, 0xfc, 0x4f,
    0xf4, 0x0, 0x0, 0x0, 0x0, 0xcf, 0xc4, 0xff,
    0x40, 0x0, 0x0, 0x0, 0xc, 0xfc, 0x4f, 0xf4,
    0x0, 0x0, 0x0, 0x0, 0xcf, 0xc4, 0xff, 0x40,
    0x0, 0x0, 0x0, 0xc, 0xfc, 0x4f, 0xf4, 0x0,
    0x0, 0x0, 0x0, 0xcf, 0xc4, 0xff, 0x40, 0x0,
    0x0, 0x0, 0xc, 0xfc, 0x4f, 0xf4, 0x0, 0x0,
    0x0, 0x0, 0xcf, 0xc4, 0xff, 0x40, 0x0, 0x0,
    0x0, 0xc, 0xfc, 0x4f, 0xf5, 0x0, 0x0, 0x0,
    0x0, 0xdf, 0xc1, 0xff, 0x70, 0x0, 0x0, 0x0,
    0xf, 0xf9, 0xf, 0xfb, 0x0, 0x0, 0x0, 0x3,
    0xff, 0x70, 0xaf, 0xf6, 0x0, 0x0, 0x1, 0xcf,
    0xf2, 0x1, 0xef, 0xfc, 0x75, 0x69, 0xff, 0xf7,
    0x0, 0x3, 0xdf, 0xff, 0xff, 0xff, 0xf9, 0x0,
    0x0, 0x0, 0x6a, 0xdf, 0xec, 0x92, 0x0, 0x0,

    /* U+0056 "V" */
    0xbf, 0xf2, 0x0, 0x0, 0x0, 0x0, 0x6f, 0xf6,
    0x5f, 0xf7, 0x0, 0x0, 0x0, 0x0, 0xcf, 0xf1,
    0xf, 0xfd, 0x0, 0x0, 0x0, 0x1, 0xff, 0xa0,
    0x9, 0xff, 0x20, 0x0, 0x0, 0x7, 0xff, 0x40,
    0x4, 0xff, 0x80, 0x0, 0x0, 0xc, 0xfe, 0x0,
    0x0, 0xef, 0xd0, 0x0, 0x0, 0x2f, 0xf9, 0x0,
    0x0, 0x8f, 0xf3, 0x0, 0x0, 0x7f, 0xf3, 0x0,
    0x0, 0x2f, 0xf8, 0x0, 0x0, 0xdf, 0xd0, 0x0,
    0x0, 0xc, 0xfe, 0x0, 0x2, 0xff, 0x80, 0x0,
    0x0, 0x7, 0xff, 0x30, 0x8, 0xff, 0x20, 0x0,
    0x0, 0x1, 0xff, 0x90, 0xd, 0xfc, 0x0, 0x0,
    0x0, 0x0, 0xbf, 0xe0, 0x3f, 0xf6, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xf4, 0x8f, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0xf, 0xfa, 0xef, 0xb0, 0x0, 0x0,
    0x0, 0x0, 0xa, 0xff, 0xff, 0x50, 0x0, 0x0,
    0x0, 0x0, 0x4, 0xff, 0xff, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xef, 0xf9, 0x0, 0x0, 0x0,

    /* U+0057 "W" */
    0xbf, 0xf3, 0x0, 0x0, 0x1, 0xff, 0xe0, 0x0,
    0x0, 0x7, 0xff, 0x77, 0xff, 0x70, 0x0, 0x0,
    0x6f, 0xff, 0x20, 0x0, 0x0, 0xbf, 0xf2, 0x2f,
    0xfb, 0x0, 0x0, 0xa, 0xff, 0xf6, 0x0, 0x0,
    0xe, 0xfe, 0x0, 0xdf, 0xf0, 0x0, 0x0, 0xef,
    0xff, 0xa0, 0x0, 0x3, 0xff, 0x90, 0x9, 0xff,
    0x30, 0x0, 0x2f, 0xf9, 0xfe, 0x0, 0x0, 0x7f,
    0xf5, 0x0, 0x4f, 0xf7, 0x0, 0x7, 0xfe, 0x2f,
    0xf3, 0x0, 0xb, 0xff, 0x0, 0x0, 0xff, 0xb0,
    0x0, 0xbf, 0xa0, 0xef, 0x70, 0x0, 0xff, 0xb0,
    0x0, 0xb, 0xff, 0x0, 0xf, 0xf5, 0x9, 0xfb,
    0x0, 0x3f, 0xf7, 0x0, 0x0, 0x6f, 0xf3, 0x3,
    0xff, 0x10, 0x5f, 0xf0, 0x7, 0xff, 0x20, 0x0,
    0x2, 0xff, 0x70, 0x8f, 0xd0, 0x1, 0xff, 0x40,
    0xbf, 0xd0, 0x0, 0x0, 0xd, 0xfb, 0xc, 0xf9,
    0x0, 0xd, 0xf8, 0xf, 0xf9, 0x0, 0x0, 0x0,
    0x8f, 0xf1, 0xff, 0x40, 0x0, 0x8f, 0xc3, 0xff,
    0x40, 0x0, 0x0, 0x4, 0xff, 0x8f, 0xf0, 0x0,
    0x4, 0xff, 0x8f, 0xf0, 0x0, 0x0, 0x0, 0xf,
    0xff, 0xfc, 0x0, 0x0, 0xf, 0xff, 0xfb, 0x0,
    0x0, 0x0, 0x0, 0xaf, 0xff, 0x80, 0x0, 0x0,
    0xcf, 0xff, 0x60, 0x0, 0x0, 0x0, 0x6, 0xff,
    0xf3, 0x0, 0x0, 0x7, 0xff, 0xf1, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xff, 0x0, 0x0, 0x0, 0x3f,
    0xfd, 0x0, 0x0, 0x0,

    /* U+0058 "X" */
    0x2f, 0xff, 0x10, 0x0, 0x0, 0x4, 0xff, 0xd0,
    0x6, 0xff, 0xb0, 0x0, 0x0, 0xe, 0xff, 0x30,
    0x0, 0xbf, 0xf6, 0x0, 0x0, 0xaf, 0xf7, 0x0,
    0x0, 0x1e, 0xff, 0x20, 0x4, 0xff, 0xc0, 0x0,
    0x0, 0x5, 0xff, 0xc0, 0x1e, 0xff, 0x20, 0x0,
    0x0, 0x0, 0x9f, 0xf7, 0xaf, 0xf5, 0x0, 0x0,
    0x0, 0x0, 0xd, 0xff, 0xff, 0xa0, 0x0, 0x0,
    0x0, 0x0, 0x3, 0xff, 0xfe, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x0, 0xef, 0xfa, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x9, 0xff, 0xff, 0x50, 0x0, 0x0,
    0x0, 0x0, 0x5f, 0xfb, 0xef, 0xf1, 0x0, 0x0,
    0x0, 0x1, 0xef, 0xf1, 0x4f, 0xfc, 0x0, 0x0,
    0x0, 0xb, 0xff, 0x50, 0x9, 0xff, 0x70, 0x0,
    0x0, 0x6f, 0xfb, 0x0, 0x0, 0xdf, 0xf3, 0x0,
    0x2, 0xff, 0xe1, 0x0, 0x0, 0x3f, 0xfd, 0x0,
    0xc, 0xff, 0x50, 0x0, 0x0, 0x8, 0xff, 0x90,
    0x8f, 0xfa, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xf5,

    /* U+0059 "Y" */
    0x8f, 0xf9, 0x0, 0x0, 0x0, 0x0, 0x2f, 0xfe,
    0x10, 0xdf, 0xf3, 0x0, 0x0, 0x0, 0xc, 0xff,
    0x40, 0x3, 0xff, 0xd0, 0x0, 0x0, 0x6, 0xff,
    0xa0, 0x0, 0x8, 0xff, 0x70, 0x0, 0x1, 0xff,
    0xe1, 0x0, 0x0, 0xd, 0xff, 0x20, 0x0, 0xbf,
    0xf4, 0x0, 0x0, 0x0, 0x3f, 0xfb, 0x0, 0x5f,
    0xfa, 0x0, 0x0, 0x0, 0x0, 0x8f, 0xf6, 0x1e,
    0xfe, 0x10, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xea,
    0xff, 0x40, 0x0, 0x0, 0x0, 0x0, 0x3, 0xff,
    0xff, 0xa0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x9,
    0xff, 0xe1, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1f, 0xf8, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x1, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1f, 0xf7, 0x0, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x1, 0xff, 0x70, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1f, 0xf7, 0x0, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x1, 0xff, 0x70, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x1f, 0xf7, 0x0, 0x0, 0x0,
    0x0,

    /* U+005A "Z" */
    0xa, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0,
    0xaf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf0, 0x2,
    0x44, 0x44, 0x44, 0x44, 0xbf, 0xfb, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x4f, 0xfe, 0x10, 0x0, 0x0,
    0x0, 0x0, 0x2f, 0xff, 0x30, 0x0, 0x0, 0x0,
    0x0, 0xd, 0xff, 0x50, 0x0, 0x0, 0x0, 0x0,
    0xb, 0xff, 0x90, 0x0, 0x0, 0x0, 0x0, 0x7,
    0xff, 0xc0, 0x0, 0x0, 0x0, 0x0, 0x4, 0xff,
    0xe1, 0x0, 0x0, 0x0, 0x0, 0x2, 0xff, 0xf3,
    0x0, 0x0, 0x0, 0x0, 0x0, 0xdf, 0xf6, 0x0,
    0x0, 0x0, 0x0, 0x0, 0xbf, 0xf9, 0x0, 0x0,
    0x0, 0x0, 0x0, 0x7f, 0xfc, 0x0, 0x0, 0x0,
    0x0, 0x0, 0x4f, 0xfe, 0x10, 0x0, 0x0, 0x0,
    0x0, 0x2f, 0xff, 0x74, 0x44, 0x44, 0x44, 0x44,
    0x26, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfa,
    0x6f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xa0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 380, .box_w = 22, .box_h = 18, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 192, .box_w = 12, .box_h = 23, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 336, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 230, .box_w = 7, .box_h = 17, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 507, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 618, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 729, .adv_w = 230, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 848, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 959, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1070, .adv_w = 230, .box_w = 12, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1172, .adv_w = 230, .box_w = 14, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1291, .adv_w = 230, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1402, .adv_w = 104, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1435, .adv_w = 259, .box_w = 17, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1580, .adv_w = 264, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1708, .adv_w = 281, .box_w = 17, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1853, .adv_w = 275, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1989, .adv_w = 246, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2108, .adv_w = 223, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2219, .adv_w = 290, .box_w = 17, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2364, .adv_w = 281, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2492, .adv_w = 97, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2526, .adv_w = 205, .box_w = 12, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2628, .adv_w = 272, .box_w = 16, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2764, .adv_w = 227, .box_w = 13, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2875, .adv_w = 345, .box_w = 19, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3037, .adv_w = 280, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3165, .adv_w = 297, .box_w = 18, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3318, .adv_w = 250, .box_w = 14, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3437, .adv_w = 297, .box_w = 18, .box_h = 19, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 3608, .adv_w = 266, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3736, .adv_w = 248, .box_w = 15, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3864, .adv_w = 237, .box_w = 15, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 3992, .adv_w = 280, .box_w = 15, .box_h = 17, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 4120, .adv_w = 251, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4256, .adv_w = 364, .box_w = 23, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4452, .adv_w = 253, .box_w = 16, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4588, .adv_w = 263, .box_w = 17, .box_h = 17, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 4733, .adv_w = 244, .box_w = 15, .box_h = 17, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 37, .range_length = 1, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 47, .range_length = 12, .glyph_id_start = 2,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 65, .range_length = 26, .glyph_id_start = 14,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 3,
    .bpp = 4,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_customer_font_pingfangheiti_bold_24 = {
#else
lv_font_t lv_customer_font_pingfangheiti_bold_24 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 24,          /*The maximum line height required by the font  default: (f.src.ascent - f.src.descent)*/
    .base_line = 3.5999999999999996,                          /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_CUSTOMER_FONT_PINGFANGHEITI_BOLD_24*/


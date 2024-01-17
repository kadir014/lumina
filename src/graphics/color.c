/*

  This file is a part of the Lumina Game Engine
  project and distributed under the MIT license.

  Copyright © Kadir Aksoy
  https://github.com/kadir014/lumina

*/

#include "lumina/graphics/color.h"


/**
 * @file color.c
 * 
 * @brief Color.
 */


lmColor lmColor_from_hsv(lmColor rgb_color) {
    // https://stackoverflow.com/a/6930407

    float h = (float)rgb_color.r * (360.0 / 255.0);
    float s = (float)rgb_color.g / 255.0;
    float v = (float)rgb_color.b / 255.0;

    float hh, p, q, t, ff;
    long i;
    lmColor out;
    out.a = rgb_color.a;

    if (s <= 0.0) {
        out.r = v * 255;
        out.g = v * 255;
        out.b = v * 255;
        return out;
    }

    hh = h;
    if(hh >= 360.0) hh = 0.0;
    hh /= 60.0;
    i = (long)hh;
    ff = hh - i;
    p = v * (1.0 - s);
    q = v * (1.0 - (s * ff));
    t = v * (1.0 - (s * (1.0 - ff)));

    switch(i) {
        case 0:
            out.r = v * 255;
            out.g = t * 255;
            out.b = p * 255;
            break;

        case 1:
            out.r = q * 255;
            out.g = v * 255;
            out.b = p * 255;
            break;

        case 2:
            out.r = p * 255;
            out.g = v * 255;
            out.b = t * 255;
            break;

        case 3:
            out.r = p * 255;
            out.g = q * 255;
            out.b = v * 255;
            break;

        case 4:
            out.r = t * 255;
            out.g = p * 255;
            out.b = v * 255;
            break;
            
        case 5:
        default:
            out.r = v * 255;
            out.g = p * 255;
            out.b = q * 255;
            break;
    }

    return out; 
}
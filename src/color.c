#include "color.h"

Color Color_add(Color a, Color b) {
    Color res;
    res.r = a.r + b.r <= 255 ? a.r + b.r : 255;
    res.g = a.g + b.g <= 255 ? a.g + b.g : 255;
    res.b = a.b + b.b <= 255 ? a.b + b.b : 255;
    return res;
}


Color Color_mul(Color color, double scalar) {
    Color res;
    res.r = color.r * scalar <= 255 ? color.r * scalar : 255;
    res.g = color.g * scalar <= 255 ? color.g * scalar : 255;
    res.b = color.b * scalar <= 255 ? color.b * scalar : 255;
    return res;
}
#ifndef COLOR_H
#define COLOR_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

Color Color_add(Color a, Color b);

Color Color_mul(Color color, double scalar);

#endif
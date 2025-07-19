#ifndef COLOR_H
#define COLOR_H

typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
} Color;

#define COLOR_BLACK ((Color){0, 0, 0})
#define COLOR_BLUE ((Color){0, 0, 255})
#define COLOR_GREEN ((Color){0, 255, 0})
#define COLOR_CYAN ((Color){0, 255, 255})
#define COLOR_RED ((Color){255, 0, 0})
#define COLOR_MAGENTA ((Color){255, 0, 255})
#define COLOR_YELLOW ((Color){255, 255, 0})
#define COLOR_WHITE ((Color){255, 255, 255})

Color Color_add(Color a, Color b);

Color Color_mul(Color color, double scalar);

#endif
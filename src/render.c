#include "sdl_wrapper.h"
#include <stdio.h>


static int abs(int number) {
    return number > 0 ? number : -number;
}


void draw_line(Context *ctx, int x0, int y0, int x1, int y1, int r, int g, int b) {
    int dx = x1 - x0;
    int dy = y1 - y0;

    if (abs(dx) > abs(dy)) {
        double k = (double)dy / dx;
        double y = y0;

        if (x0 > x1) {
            int tmp = x0;
            x0 = x1;
            x1 = tmp;
        }

        for (int x = 0; x <= x1; x++) {
            set_pixel(ctx, x, y, r, g, b);
            y += k;
        }
    } else {
        double k = (double)dx / dy;
        double x = x0;

        if (y0 > y1) {
            int tmp = y0;
            y0 = y1;
            y1 = tmp;
        }

        for (int y = 0; y <= y1; y++) {
            set_pixel(ctx, x, y, r, g, b);
            x += k;
        }
    }
}
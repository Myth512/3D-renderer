#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "context.h"

int Init(Context *ctx);

void Term(Context *ctx);

void clear(Context *ctx);

void render(Context *ctx);

void set_pixel(Context *ctx, int x, int y, int r, int g, int b);

#endif
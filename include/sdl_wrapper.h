#ifndef SDL_WRAPPER_H
#define SDL_WRAPPER_H

#include "context.h"
#include "color.h"
#include "input.h"

int Init(Context *ctx);

void Term(Context *ctx);

void process_events(InputState *input);

void clear(Context *ctx);

void render(Context *ctx);

void draw_pixel(Context *ctx, double x, double y, Color c);

#endif
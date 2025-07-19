#include "sdl_wrapper.h"
#include <stdio.h>


int Init(Context *ctx) {
    int ret = SDL_Init(SDL_INIT_VIDEO);
    if (ret < 0) {
        SDL_Log("SDL_Init() Error: %s", SDL_GetError());
        return 0;
    }

    ctx->width = 640;
    ctx->height = 480;
    
    ctx->window = SDL_CreateWindow("HelloWorld SDL3", ctx->width, ctx->height, 0);
    if (!ctx->window) {
        SDL_Log("SDL_CreateWindow() Error: ", SDL_GetError());
        return 0;
    }

    ctx->renderer = SDL_CreateRenderer(ctx->window, NULL);
    if (!ctx->renderer) {
        SDL_Log("SDL_CreateRenderer() Error: ", SDL_GetError());
        return 0;
    }
    return 1;
}


void Term(Context *ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}


void clear(Context *ctx) {
    SDL_SetRenderDrawColor(ctx->renderer, 0, 0, 0, 255);
    SDL_RenderClear(ctx->renderer);
}


void set_pixel(Context *ctx, double x, double y, Color c) {
    SDL_SetRenderDrawColor(ctx->renderer, c.r, c.g, c.b, 255);
    SDL_RenderPoint(ctx->renderer, x, y);
}


void render(Context *ctx) {
    SDL_RenderPresent(ctx->renderer);
}


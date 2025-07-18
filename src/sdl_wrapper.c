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

    ctx->texture = SDL_CreateTexture(ctx->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_STREAMING, ctx->width, ctx->height);
    if (!ctx->texture) {
        SDL_Log("SDL_CreateTexture() Error: ", SDL_GetError());
        return 0;
    }
    return 1;
}


void Term(Context *ctx) {
    SDL_DestroyRenderer(ctx->renderer);
    SDL_DestroyWindow(ctx->window);
    SDL_Quit();
}


void set_pixel(Context *ctx, int x, int y, int r, int g, int b) {
    int offset = (y * ctx->width + x) * 4;
    char *data = (char*)ctx->pixels;
    *(data + offset) = r;
    *(data + offset + 1) = g;
    *(data + offset + 2) = b;
    *(data + offset + 3) = 255;
}


void lock(Context *ctx) {
    SDL_LockTexture(ctx->texture, NULL, &ctx->pixels, &ctx->pitch);
}


void unlock(Context *ctx) {
    SDL_UnlockTexture(ctx->texture);
}


void render(Context *ctx) {
    SDL_RenderTexture(ctx->renderer, ctx->texture, NULL, NULL);
    SDL_RenderPresent(ctx->renderer);
}


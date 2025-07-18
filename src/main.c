#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <stdio.h>

#include "sdl_wrapper.h"
#include "render.h"


int main(int argc, char* argv[]) {
    Context ctx;
    Init(&ctx);
    lock(&ctx);
    draw_line(&ctx, 200, 300, 100, 100, 255, 0, 0);
    unlock(&ctx);
    render(&ctx);

    getchar();

    return 0;
}
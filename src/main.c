#include <stdio.h>

#include "sdl_wrapper.h"
#include "input.h"
#include "render.h"
#include "vec.h"

Vertex vertices[] = {
    {.position = (Vec3){-1, -1, -1}, .color = COLOR_RED},
    {.position = (Vec3){-1, -1,  1}, .color = COLOR_GREEN},
    {.position = (Vec3){-1,  1,  1}, .color = COLOR_BLUE},
    {.position = (Vec3){-1,  1, -1}, .color = COLOR_BLUE},
    {.position = (Vec3){ 1, -1, -1}, .color = COLOR_GREEN},
    {.position = (Vec3){ 1, -1,  1}, .color = COLOR_BLUE},
    {.position = (Vec3){ 1,  1,  1}, .color = COLOR_GREEN},
    {.position = (Vec3){ 1,  1, -1}, .color = COLOR_GREEN}
};

Face faces[] = {
    {0, 1, 2},
    {0, 2, 3},
    {0, 1, 5},
    {0, 4, 5},
    {1, 5, 6},
    {1, 2, 6},
    {0, 4, 7},
    {0, 3, 7},
    {2, 3, 7},
    {2, 6, 7},
    {4, 5, 6},
    {4, 6, 7}
};

int main(int argc, char* argv[]) {
    Context ctx;
    Init(&ctx);

    Camera camera = {.fov = 90, .position = (Vec3){-5, 0, 0}};
    Object object = {.posistion = (Vec3){0, 0, 0}, .scale = (Vec3){1, 1, 1}};
    init_mesh(&object.mesh, vertices, faces, sizeof(faces) / sizeof(Face));

    InputState input = {0};

    while (!input.quit_requested) {
        process_events(&input);

        process_input(&input, &camera);

        clear(&ctx);

        draw_object(&camera, &ctx, &object);

        render(&ctx);

        SDL_Delay(16);
    }

    Term(&ctx);
    return 0;
}
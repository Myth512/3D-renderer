#include "input.h"

#include <stdio.h>
#include <math.h>
#include <string.h>

void process_input(InputState *input, Camera *camera) {
    if (input->mouse_left) {
        camera->position = rotate_y(camera->position, input->mouse_x_rel / 50);
        camera->rotation.x = atan2(camera->position.z, camera->position.x) + 3.14;
        input->mouse_x_rel = 0;
    }
    if (input->mouse_scroll) {
        camera->position.x += cos(camera->rotation.x) * input->mouse_scroll;
        camera->position.z += sin(camera->rotation.x) * input->mouse_scroll;
        printf("here %f %f\n", camera->rotation.y, sin(camera->rotation.y));
        camera->position.y -= sin(camera->rotation.y) * input->mouse_scroll;
        input->mouse_scroll = 0;
    }
    if (input->mouse_middle) {
        printf("rel %f %f %f\n", camera->rotation.x * 180 / 3.14, sin(camera->rotation.x), cos(camera->rotation.x));
        camera->position.x += sin(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->position.z -= cos(camera->rotation.x) * input->mouse_x_rel / 10;
        camera->position.y -= input->mouse_y_rel / 10;
    }
    if (input->mouse_right) {
        camera->rotation.x += input->mouse_x_rel / 100;
        camera->rotation.y -= input->mouse_y_rel / 100;
    }
    input->mouse_x_rel = 0;
    input->mouse_y_rel = 0;
}
#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

#include "camera.h"

typedef struct {
    bool quit_requested;
    bool mouse_left;
    bool mouse_middle;
    bool mouse_right;
    double mouse_x_rel;
    double mouse_y_rel;
    double mouse_scroll;
} InputState;

void process_input(InputState *input, Camera *camera);

#endif
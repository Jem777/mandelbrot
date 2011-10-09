#include <stdio.h>
#include <complex.h>
#include <unistd.h>

#include "mandelbrot.h"

int main(void){
    unsigned int length = 100;

    rendering_t start_render;
    start_render.origin = - 0.743643887037151 + 0.131825904205330*I; 
    start_render.zoomfactor = 30000;
    start_render.iteration_depth = 500;
    start_render.counter = 0;

    rendering_t *rendering_list = create_rendering(start_render, length, 1.01, 2);

    targets_t target_list;
    target_list.x = 200;
    target_list.y = 200;
    target_list.data = rendering_list;
    target_list.length = length;

    run_rendering(target_list);
    destroy_rendering(rendering_list);
    return 0;
}

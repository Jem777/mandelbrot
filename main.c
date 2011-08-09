#include <stdio.h>
#include <complex.h>
#include <unistd.h>

#include "threading.h"

int main(void){

    unsigned int length = 100000;
    long numCPU = sysconf( _SC_NPROCESSORS_ONLN );

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
    target_list.thread_number = 0;
    target_list.thread_max = (unsigned int)numCPU;

    create_threads(target_list);
    destroy_rendering(rendering_list);
    /*rendering_t target_b[3];
    target_b[0] = rendering_t{origin, zoomfactor*1.3, iteration_depth, 3};
    target_b[1] = {origin, zoomfactor*1.4, iteration_depth, 4};
    target_b[2] = {origin, zoomfactor*1.5, iteration_depth, 5};
    */
    return 0;
}

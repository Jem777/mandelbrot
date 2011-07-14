#include <stdio.h>
#include <complex.h>
#include <unistd.h>
#include <math.h>

#include "threading.h"
#include <gmp.h>

int main(void){

  // set gmp precision
  mpf_set_default_prec(128);
  long unsigned int precision = mpf_get_default_prec();
  printf("precision used: %ld bits\n", precision);

    unsigned int length = 1;
    long numCPU = sysconf( _SC_NPROCESSORS_ONLN );
    if(numCPU > 10){
      numCPU = numCPU + (int)floor(numCPU/10);
    }
    printf("Using %ld threads (%d over-allocated)\n", numCPU, (int)floor(numCPU/10));

    rendering_t start_render;
    start_render.origin = - 0.743643887037151 + 0.131825904205330*I; 
    start_render.zoomfactor = 300000000000;
    start_render.iteration_depth = 4000;
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

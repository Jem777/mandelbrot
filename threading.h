#ifndef THREADING_H_
#define THREADING_H_

#include "mandelbrot.h"
#include <pthread.h>
#include <errno.h>

typedef struct{
    pthread_t thread_id;
    int status;
} threading_t;

void create_threads(targets_t target_list);
void *worker(void *input);
void report_error(int status);

rendering_t *create_rendering(rendering_t target, unsigned int length, double zfactor, double ifactor);
void destroy_rendering(rendering_t *rendering_list);
#endif

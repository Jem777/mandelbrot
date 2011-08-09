#include "threading.h"

void create_threads(targets_t target_list) {
    threading_t *threads = malloc(sizeof(threading_t) * target_list.thread_max);
    for (unsigned int i = 0; i < target_list.thread_max; i++) {
        target_list.thread_number = i;
        targets_t *thread_input = malloc(sizeof(targets_t));
        *thread_input = target_list;
        threads[i].status = pthread_create(&(threads[i].thread_id), NULL, worker, (void*)thread_input);
    }
    for (unsigned int i = 0; i < target_list.thread_max; i++) {
        if (threads[i].status == 0) {
            pthread_join(threads[i].thread_id, NULL);
        }
        else {
            report_error(threads[i].status);
        }
    }
    //run_renderingp(x, y, target_a, 3);
    /*int status;
    targets_t *thread_input = malloc(sizeof(targets_t));
    *thread_input = target_list;
    if ((status = pthread_create(&thread, NULL, worker, (void*)thread_input)) == 0) {
        pthread_join(thread, NULL);
    }
    else {
        report_error(status);
    }*/
}

void *worker(void *input) {
    targets_t target_list = *(targets_t*)input;
    free(input);
    printf("thread number %d spawned \n", target_list.thread_number);
    run_renderingp(target_list);
    return NULL;
}

void report_error(int status){
    // Report why thread creation failed. Error messages are taken from pthread_create manual.
    // this function could probably replaced with errstr() or something.
    if(status == EAGAIN){
        fprintf(stderr, 
        "Error creating thread: The system lacked the necessary resources to create another thread, or the system-imposed limit on the total number of threads in a process {PTHREAD_THREADS_MAX} would be exceeded.\n");
    }
    else if(status == EINVAL){
        fprintf(stderr, "The value specified by 'attr' is invalid.\n");
    }
    else if(status == EPERM){
        fprintf(stderr, 
        "The caller does not have appropriate permission to set the required scheduling parameters or scheduling policy.\n");
    }
    else {
        fprintf(stderr, "Error creating thread: An unknown error occurred.\n");
    }
}

rendering_t *create_rendering(rendering_t target, unsigned int length, real zfactor, real ifactor) {
    rendering_t *rendering_list = malloc(sizeof(rendering_t) * length);
    real current_zoom = target.zoomfactor;
    real current_depth = target.iteration_depth;
    for (unsigned int i = 0; i < length; i++) {
        rendering_list[i].origin = target.origin;
        rendering_list[i].zoomfactor = current_zoom;
        rendering_list[i].iteration_depth = current_depth;
        rendering_list[i].counter = i;
        current_zoom *= zfactor;
        current_depth += ifactor;
    }
    return rendering_list;
}

void destroy_rendering(rendering_t *rendering_list) {
    free(rendering_list);
}

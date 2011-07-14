#include "mandelbrot.h"
#include <stdio.h>
#include <errno.h>
#include <gmp.h>

/* void test_rendering(surface_t* surface){ */
/*     real zoomfactor = 300; */
/*     complexreal origin = - 0.743643887037151 + 0.131825904205330*I;  */
/*     render_frame(surface, zoomfactor, origin, 100); */
/*     write_bmp(surface, "foobar.bmp"); */
/* } */

void run_renderingp(targets_t target_list) {
    surface_t *surface = create_surface(target_list.x, target_list.y);
    char output_file[100];
    rendering_t *data = target_list.data;
    for (unsigned int i = target_list.thread_number; i < target_list.length; i += target_list.thread_max) {
        printf("rendering target %d\n", data[i].counter);
        render_frame(surface, data[i].zoomfactor, creal(data[i].origin), cimag(data[i].origin), data[i].iteration_depth);
        snprintf(output_file, 100, "out_%04d.bmp", data[i].counter);
        write_bmp(surface, output_file);
	move_file(output_file, "output");
    }
    destroy_surface(surface);
}

void render_frame(surface_t* surface, real zoomfactor, real origin_r, real origin_i, real iteration_depth){
  for(unsigned int x=0;  x < surface->w; x++) {
    for(unsigned int y=0;  y < surface->h; y++) {
      real testpoint_r = ((int)x - (int)surface->w / 2);
      real testpoint_i = ((int)y - (int)surface->h / 2);
      real scale = iterate_complex(origin_r + testpoint_r/zoomfactor, origin_i + testpoint_i/zoomfactor, iteration_depth);
      pixel_t p = colorize(scale);
      set_pixel(surface, x, y, p);
    }
  }
}

real iterate_complex(real in_c_r, real in_c_i, int max_iteration) {
    int iteration_step = 0;
    mpf_t z_r;
    mpf_t z_i;
    mpf_t c_r;
    mpf_t c_i;
    mpf_t tmp_a;
    mpf_t tmp_b;
    mpf_t tmp_c;
    mpf_init(z_r);
    mpf_init(z_i);
    mpf_init(c_r);
    mpf_init(c_i);
    mpf_init(tmp_a);
    mpf_init(tmp_b);
    mpf_init(tmp_c);
    mpf_set_d(z_r, 0.0);
    mpf_set_d(z_i, 0.0);
    mpf_set_d(c_r, in_c_r); // these should probably be passed in directly as mpf_t.
    mpf_set_d(c_i, in_c_i);
    /* real z_r = 0.0; */
    /* real z_i = 0.0; */
    
    while(iteration_step < max_iteration){
      //real xtemp = z_r*z_r - z_i*z_i + c_r;
      mpf_mul(tmp_a, z_r, z_r); // we should really save the results from z_r^2 and z_i^2, since we re-use them
      mpf_mul(tmp_b, z_i, z_i);
      mpf_sub(tmp_c, tmp_a, tmp_b);
      mpf_add(tmp_a, tmp_c, c_r);
      // result is now in tmp_a.

      mpf_mul(tmp_b, z_r, z_i);
      mpf_mul_ui(tmp_c, tmp_b, 2);
      mpf_add(z_i, tmp_c, c_i);
      //z_i = 2*z_r*z_i + c_i;
      //z_r = xtemp;
      mpf_set(z_r, tmp_a);
      // tmp_a and tmp_b can now be used freely again.

      iteration_step++;
      
      // abort condition
      //real magsquared = z_r*z_r + z_i*z_i;
      mpf_mul(tmp_a, z_r, z_r);
      mpf_mul(tmp_b, z_i, z_i);
      mpf_add(tmp_a, tmp_a, tmp_b);
      // convert to real...?
      real magsquared = mpf_get_d(tmp_a);
      //      gmp_printf("magsquared: %.50ff vs %.50Ff\n", magsquared, tmp_a);
      if(magsquared >= 4){
	break;
      }
    }

    mpf_clear(z_r);
    mpf_clear(z_i);
    mpf_clear(c_r);
    mpf_clear(c_i);
    mpf_clear(tmp_a);
    mpf_clear(tmp_b);

    real scale = (real)iteration_step / max_iteration;
    return scale;
}

pixel_t colorize(real scale) {
    pixel_t p;
    p.r = (unsigned char)(255*scale);
    p.g = (unsigned char)(255*scale);
    p.b = (unsigned char)(255*scale);
    return p;
}

void move_file(char *file, char *dirname){
  char newname[256];
  snprintf(newname, 256, "%s/%s", dirname, file);
  if(rename(file, newname) == -1){
    char errormessage[256];
    snprintf(errormessage, 256, "Error moving '%s' to '%s/'", file, dirname);
    perror(errormessage);
  }
}

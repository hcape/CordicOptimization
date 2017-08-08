#include <stdio.h>
#include <math.h>
#include "cordic.h"
#define SHIFT_SCALE 32768
#define K_CONSTANT 0.607252935

int main( void) {
    printf( "Vectoring CORDIC:\n\n");
    int i;
    for(i = 0; i < 1000000; i++){
        arctan_xy_original(5,9);
        arctan_x_original(5);
        cos_theta_original(30);
        sin_theta_original(30);
        // printf("arctanxy of 5 9: %f rad\n", ((float)arctan_xy_original(5,9) / SHIFT_SCALE));
        // printf("arctanx of 5: %f rad\n", ((float)arctan_x_original(5) / SHIFT_SCALE));
        // printf("cos of 30 deg: %f\n", ((float) cos_theta_original(30) / SHIFT_SCALE) * K_CONSTANT);
        // printf("sin of 30 deg: %f\n", ((float)sin_theta_original(30) / SHIFT_SCALE) * K_CONSTANT );
    }
    return 0;
} /*** END of main() function ***/
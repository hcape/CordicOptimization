#include <stdio.h>
#include <math.h>
#include "cordic.h"
#define SHIFT_SCALE 32768
#define K_CONSTANT 0.607252935
void verify( int x_i_init, int y_i_init, int z_i_init, int x_i, int y_i, int z_i) {
    double x_d_init, y_d_init, z_d_init, x_d, y_d, z_d;
    x_d_init = (double)x_i_init / SHIFT_SCALE; /* float image of x_i_init */
    y_d_init = (double)y_i_init / SHIFT_SCALE; /* float image of y_i_init */
    z_d_init = (double)z_i_init / SHIFT_SCALE; /* float image of z_i_init */
    x_d = ((double)x_i / SHIFT_SCALE) * K_CONSTANT; /* float image of x_i */
    y_d = ((double)y_i / SHIFT_SCALE) * K_CONSTANT; /* float image of y_i */
    z_d = ((double)z_i / SHIFT_SCALE); /* float image of z_i */
    printf( "x_i_init = %5i\tx_d_init = %f\n", x_i_init, x_d_init);
    printf( "y_i_init = %5i\ty_d_init = %f\n", y_i_init, y_d_init);
    printf( "z_i_init = %5i\tz_d_init = %f (rad)\n\n", z_i_init, z_d_init);
    printf( "x_i_calc = %5i\tx_d_calc = %f\n", x_i, x_d);
    printf( "y_i_calc = %5i\ty_d_calc = %f\n", y_i, y_d);
    printf( "z_i_calc = %5i\tz_d_calc = %f (rad)\n\n", z_i, z_d);
    //printf( "Modulus = SQRT(x_d_init^2 + y_d_init^2) = %f\n",
    //sqrt(x_d_init*x_d_init+y_d_init*y_d_init));
} /*** END of verify() function ***/

int main( void) {
    printf( "Vectoring CORDIC:\n\n");

    printf("arctanxy of 5 9: %f rad\n", ((float)arctan_xy_optimized(5,9) / SHIFT_SCALE));
    printf("arctanx of 5: %f rad\n", ((float)arctan_x_optimized(5) / SHIFT_SCALE));
    printf("cos of 30 deg: %f\n", ((float)cos_theta_optimized(30) / SHIFT_SCALE) * K_CONSTANT);
    printf("sin of 30 deg: %f\n", ((float)sin_theta_optimized(30) / SHIFT_SCALE) * K_CONSTANT );

    return 0;
} /*** END of main() function ***/
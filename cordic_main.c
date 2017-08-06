#include <stdio.h>
#include <math.h>
#include "cordic.h"

void verify( int x_i_init, int y_i_init, int z_i_init, int x_i, int y_i, int z_i) {
    double x_d_init, y_d_init, z_d_init, x_d, y_d, z_d;
    x_d_init = (double)x_i_init / ( 1 << 15); /* float image of x_i_init */
    y_d_init = (double)y_i_init / ( 1 << 15); /* float image of y_i_init */
    z_d_init = (double)z_i_init / ( 1 << 15); /* float image of z_i_init */
    x_d = ((double)x_i / ( 1 << 15)) * 0.607252935; /* float image of x_i */
    y_d = ((double)y_i / ( 1 << 15)) * 0.607252935; /* float image of y_i */
    z_d = ((double)z_i / ( 1 << 15)); /* float image of z_i */
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
    int x_i_init, y_i_init, z_i_init; /* initial values */
    int x_i, y_i, z_i; /* integer (fixed-point) variables */
    x_i = (x_i_init = 27852);
    y_i = (y_i_init = 24903);
    z_i_init = 23906;
    printf( "Vectoring CORDIC:\n\n");
    z_i = cordic_V_fixed_point( &x_i, &y_i);
    verify( x_i_init, y_i_init, z_i_init, x_i, y_i, z_i);
    return 0;
} /*** END of main() function ***/
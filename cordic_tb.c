#include <stdio.h>
#include <math.h>
int main( void) {
    double x_d, y_d, arctan_xy, arctan_x, cos_d, sin_d, theta_d; /* 64-bit floating-point precision */
    int x_i, y_i, arctan_xyi, arctan_xi, i, cos_i, sin_i;  /* integer (fixed-point) variables */
    x_d = 0.85;
    y_d = 0.76;
    theta_d = 30;
    cos_d = cos(theta_d);
    sin_d = sin(theta_d);
    arctan_xy = atan( y_d / x_d); /* call to std-C math routine */
    arctan_x = atan( x_d); /* call to std-C math routine */
    x_i = x_d * (1 << 15); /* convert to 16-bit integers */
    y_i = y_d * (1 << 15); /* convert to 16-bit integers */
    arctan_xyi = arctan_xy * (1 << 15); /* convert to 16-bit integers */
    arctan_xi = arctan_x * (1 << 15);
    cos_i = cos_d * (1 << 15);
    sin_i = sin_d * (1 << 15);

    printf( "x_d = %f\t\t\tx_i = %i\n", x_d, x_i);
    printf( "y_d = %f\t\t\ty_i = %i\n", y_d, y_i);
    printf( "theta_d = %f\n", theta_d);
    printf( "cos = %f\t\t\tcos_i = %i\n", cos_d, cos_i);
    printf( "sin = %f\t\t\tsin_i = %i\n", sin_d, sin_i);
    printf( "arctan_xy = %f\t\tarctan_xyi = %i\n", arctan_xy, arctan_xyi);
    printf( "arctan_x = %f\t\tarctan_xi = %i\n", arctan_x, arctan_xi);
    printf( "\n");
    printf( "The angle table:\n");

    for( i=0; i<15; i++) {
        printf( "z[%2i] = %i\n", i,
        (int)(atan( pow( 2.0, (double)(-i))) * (1 << 15)));
    }
}
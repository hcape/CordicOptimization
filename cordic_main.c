#include <stdio.h>
#include <math.h>

#define ITERATION_COUNT 15
int z_table[15] = { 25735, 15192, 8027, 4074, 2045, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1};

//void cordic_V_fixed_point( register int *restrict x, register int * restrict y, register int * restrict z){
//    register int x_temp_1, y_temp_1, z_temp, z_temp_i;
//    register int x_temp_2, y_temp_2;
//    register int i;
//    register int mu;
//    x_temp_1 = *x;
//    y_temp_1 = *y;
//    z_temp = 0;    
//    for( i^=i; i<ITERATION_COUNT; i++) { /* we want 15 iterations */
//        z_temp_i = z_table[i]; 
//            if(y_temp_1 >0) {
//                x_temp_2 = x_temp_1 + mu*(y_temp_1 >> i);
//                y_temp_2 = y_temp_1 - (x_temp_1 >> i);
//                z_temp += z_temp_i;
//            }
//            else {
//                x_temp_2 = x_temp_1 - (y_temp_1 >> i);
//                y_temp_2 = y_temp_1 + (x_temp_1 >> i);
//                z_temp -= z_temp_i;
//            }
//            x_temp_1 = x_temp_2;
//            y_temp_1 = y_temp_2;
//        }
//    *x = x_temp_1;
//    *y = y_temp_1;
//    *z = z_temp;
//}

void cordic_V_fixed_point( register int *x, register int *y, register int *z) {
    register int x_temp_1, y_temp_1, z_temp_1, z_temp;
    register int x_temp_2, y_temp_2;
    register int i;
    x_temp_1 = *x;
    y_temp_1 = *y;
    z_temp = 0;
    for( i=i^i; i<ITERATION_COUNT; i++) { /* we want 15 iterations */
        if( y_temp_1 > 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += z_table[i];
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -= z_table[i];
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }
    *x = x_temp_1;
    *y = y_temp_1;
    *z = z_temp;
}

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
    cordic_V_fixed_point( &x_i, &y_i, &z_i);
    verify( x_i_init, y_i_init, z_i_init, x_i, y_i, z_i);
    return 0;
} /*** END of main() function ***/
#include <stdio.h>
#include <math.h>

#define ITERATION_COUNT 15
int z_table[15] = { 25735, 15192, 8027, 4074, 2045, 1023, 511, 255, 127, 63, 31, 15, 7, 3, 1};

struct vector {
   int  x;
   int  y;
};

int cordic_V_fixed_point_original( int *x, int *y) {
    int x_temp_1, y_temp_1, z_temp;
    int x_temp_2, y_temp_2;
    int i;
    x_temp_1 = *x;
    y_temp_1 = *y;
    z_temp = 0;
    for( i=0; i<ITERATION_COUNT; i++) { /* we want 15 iterations */
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
    return z_temp;
}

struct vector cordic_R_fixed_point_original( int z_temp) {
    int x_temp_1, y_temp_1;
    int x_temp_2, y_temp_2;
    int i;
    x_temp_1 = 1 << 15;
    y_temp_1 = 0;
    for( i=0; i<ITERATION_COUNT; i++) { /* we want 15 iterations */
        if( z_temp < 0) {
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

    struct vector v;
    v.x = x_temp_1;
    v.y = y_temp_1;
    return v;
}

__int32_t arctan_xy_original(double x, double y) {
    
    if(x<0)
        return -1; //outside domain
    __int32_t newx = (x * (1<<15));
    __int32_t newy = (y * (1<<15));
    
    return cordic_V_fixed_point_original(&newx, &newy); 
}

__int32_t arctan_x_original(double y) {
    if(y<0)
        return -1; //outside domain
    __int32_t x = 32768;
     __int32_t newy = (y * (1<<15));
    return cordic_V_fixed_point_original(&x, &newy); 
}

__int32_t cos_theta_original(float z){
    // Check if outside domain
    // Convert deg to rad
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;
    __int32_t newz = (__int32_t) z << 15;
    newz = newz *3.14158/180;
    // Cast as int

    return cordic_R_fixed_point_original((int) newz).x;
}

__int32_t sin_theta_original(float z){
    // Check if outside domain
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;

    // Convert deg to rad  
          
    __int32_t newz = (__int32_t) z << 15;
    newz = newz *3.14158/180;
    return cordic_R_fixed_point_original((int) newz).y;
}
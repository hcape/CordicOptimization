#include <stdint.h>
#define ITERATION_COUNT 14
#define SHIFT_SCALE 32768
#define BITMASK_FFFF 0xFFFF
uint32_t z_table[7] = {1686584152, 526061546, 134022143, 33489151,8323135,2031631,458755};

struct vector {
   int  x;
   int  y;
};

int cordic_V_fixed_point_optimized( register int x_temp_1, register int y_temp_1) {
    register int z_temp;
    register int x_temp_2, y_temp_2;
    register int i, z_table_temp;
    z_temp = 0;

    for( i=i^i; i!=ITERATION_COUNT; ++i) { /* we want 15 iterations */
        z_table_temp = z_table[i>>1];
        if( y_temp_1 > 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += (z_table_temp >> 16);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -= (z_table_temp >> 16);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
        ++i;
        if( y_temp_1 > 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += (z_table_temp & BITMASK_FFFF);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -=  (z_table_temp & BITMASK_FFFF);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;

    }
    (y_temp_1 > 0) ? ++z_temp : --z_temp;
    
    return z_temp;
}

struct vector cordic_R_fixed_point_optimized(register int z_temp) {
    register int x_temp_1, y_temp_1;
    register int x_temp_2, y_temp_2;
    register int i, z_table_temp;
    x_temp_1 = SHIFT_SCALE;
    y_temp_1 = 0;

    for( i=i^i; i!=ITERATION_COUNT; ++i) { /* we want 15 iterations */
        z_table_temp = z_table[i>>1];
        if( z_temp < 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += (z_table_temp >> 16);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -= (z_table_temp >> 16);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
        ++i;
        if( z_temp < 0) {
            x_temp_2 = x_temp_1 + (y_temp_1 >> i);
            y_temp_2 = y_temp_1 - (x_temp_1 >> i);
            z_temp += (z_table_temp & BITMASK_FFFF);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -=  (z_table_temp & BITMASK_FFFF);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }


    if( z_temp < 0) {
        x_temp_2 = x_temp_1 + (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 - (x_temp_1 >> 14);
    }
    else {
        x_temp_2 = x_temp_1 - (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 + (x_temp_1 >> 14);
    }

    struct vector v;
    v.x = x_temp_2;
    v.y = y_temp_2;
    return v;
}


int32_t arctan_xy_optimized(double x, double y) {
    
    if(x<0)
        return -1; //outside domain

    return cordic_V_fixed_point_optimized((int32_t)(x * SHIFT_SCALE), (int32_t)(y * SHIFT_SCALE)); 
}

int32_t arctan_x_optimized(double y) {
    if(y<0)
        return -1; //outside domain
    return cordic_V_fixed_point_optimized(SHIFT_SCALE, (int32_t)(y * SHIFT_SCALE)); 
}

int32_t cos_theta_optimized(float z){
    // Check if outside domain
    // Convert deg to rad
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;
    z = z*3.14158/180;
    // Cast as int
    return cordic_R_fixed_point_optimized((int32_t) (z *SHIFT_SCALE)).x;
}

int32_t sin_theta_optimized(float z){
    // Check if outside domain
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;

    // Convert deg to rad        
    z = z*3.14158/180;        
    return cordic_R_fixed_point_optimized((int32_t) (z *SHIFT_SCALE)).y;
}


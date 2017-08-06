#define ITERATION_COUNT 14
__uint32_t z_table[7] = {1686584152, 526061546, 134022143, 33489151,8323135,2031631,458755};

struct vector {
   int  x;
   int  y;
};

int cordic_V_fixed_point( register int x, register int y) {
    register int x_temp_1, y_temp_1, z_temp_1, z_temp;
    register int x_temp_2, y_temp_2;
    register int i, z_table_temp;
    x_temp_1 = x;
    y_temp_1 = y;
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
            z_temp += (z_table_temp & 0xFFFF);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -=  (z_table_temp & 0xFFFF);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }


    if( y_temp_1 > 0) {
        x_temp_2 = x_temp_1 + (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 - (x_temp_1 >> 14);
        ++z_temp;
    }
    else {
        x_temp_2 = x_temp_1 - (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 + (x_temp_1 >> 14);
        --z_temp;
    }

   

    x = x_temp_2;
    y = y_temp_2;
    return z_temp;
}

struct vector cordic_R_fixed_point(register int z) {
    register int x_temp_1, y_temp_1, z_temp_1, z_temp;
    register int x_temp_2, y_temp_2;
    register int i, z_table_temp;
    x_temp_1 = 1;
    y_temp_1 = 0;
    z_temp = 0;

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
            z_temp += (z_table_temp & 0xFFFF0000);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -=  (z_table_temp & 0xFFFF0000);
        }
        x_temp_1 = x_temp_2;
        y_temp_1 = y_temp_2;
    }


    if( z_temp < 0) {
        x_temp_2 = x_temp_1 + (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 - (x_temp_1 >> 14);
        ++z_temp;
    }
    else {
        x_temp_2 = x_temp_1 - (y_temp_1 >> 14);
        y_temp_2 = y_temp_1 + (x_temp_1 >> 14);
        --z_temp;
    }

    struct vector v;
    
    v.x = x_temp_2;
    v.y = y_temp_2;
    return v;
}

__int32_t arctan_xy(__int32_t x, __int32_t y) {
    if(x<0)
        return -1; //outside domain
    return cordic_V_fixed_point(x, y); 
}

__int32_t arctan_x(__int32_t x) {
    if(x<0)
        return -1; //outside domain
    return cordic_V_fixed_point(1, x); 
}

__int32_t cos_theta(__int32_t z){
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;
       
    return cordic_R_fixed_point(z).x;
}

__int32_t sin_theta(__int32_t z){
    if(z > 360)
        return -1; //outside domain
    else if(z > 90)
        z -= 90;
    else if(z < -90)
        z += 90;
    return cordic_R_fixed_point(z).y;
}


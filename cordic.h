void cordic_V_fixed_point( register int *x, register int *y, register int *z) {
    register int x_temp_1, y_temp_1, z_temp_1, z_temp;
    register int x_temp_2, y_temp_2;
    register int i, z_table_temp;
    x_temp_1 = *x;
    y_temp_1 = *y;
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
            z_temp += ((z_table_temp << 16) >> 16);
        }
        else {
            x_temp_2 = x_temp_1 - (y_temp_1 >> i);
            y_temp_2 = y_temp_1 + (x_temp_1 >> i);
            z_temp -=  ((z_table_temp << 16) >> 16);
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

   

    *x = x_temp_2;
    *y = y_temp_2;
    *z = z_temp;
}
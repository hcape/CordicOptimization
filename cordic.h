#ifndef CORDIC_H
#define CORDIC_H

#include <stdint.h>
#include <stdio.h>



// Default functions
int32_t arctan_xy_original(double x, double y);
int32_t arctan_x_original(double y);
int32_t cos_theta_original(float z);
int32_t sin_theta_original(float z);

// Optimized functions
int32_t arctan_xy_optimized(double x, double y);
int32_t arctan_x_optimized(double y);
int32_t cos_theta_optimized(float z);
int32_t sin_theta_optimized(float z);

#endif

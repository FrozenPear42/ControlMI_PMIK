#ifndef PLAYGROUND_MPU6050_H
#define PLAYGROUND_MPU6050_H

#include "stm32f3xx_hal.h"

#define MPU6050_DEVICE_ADDRESS  0xD0

#define MPU6050_PWR_MGMT_1                      0x6B
#define MPU6050_ACCEL_CONFIG                    0x1C

#define MPU6050_ACCEL_X_OUT                     0x3B
#define MPU6050_ACCEL_Y_OUT                     0x3D
#define MPU6050_ACCEL_Z_OUT                     0x3F


enum MPU6050_PWR_MGMT_1_Values {
    MPU6050_SLEEP = (1 << 6),
};


enum MPU6050_ACCEL_CONFIG_Values {
    MPU6050_ACCEL_CONFIG_AFS_SEL_2 = 0,
    MPU6050_ACCEL_CONFIG_AFS_SEL_4 = (1 << 3),
    MPU6050_ACCEL_CONFIG_AFS_SEL_8 = (2 << 3),
    MPU6050_ACCEL_CONFIG_AFS_SEL_16 = (3 << 3),
};

/* FUNCTIONS */

void MPU6050_Init(I2C_HandleTypeDef*);

uint8_t MPU6050_Accel_Get_X ();
uint8_t MPU6050_Accel_Get_Y ();
uint8_t MPU6050_Accel_Get_Z ();








#endif //PLAYGROUND_MPU6050_H

#ifndef PLAYGROUND_MPU6050_H
#define PLAYGROUND_MPU6050_H

/*!
 * @file
 * @brief This file is responsible for MPU6050.
 *
 */

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

/*!
 * @brief Initializes MPU6050
 *
 * Sets up proper I2C and then configures device so it works in demanded way.
 */
void MPU6050_Init(I2C_HandleTypeDef*);

/*!
 * Returns accelerometer X-axis value.
 * Values are normalized so they are from 0 to 127
 * @return normalized X-axis value
 */
uint8_t MPU6050_Accel_Get_X ();

/*!
 * Returns accelerometer Y-axis value.
 * Values are normalized so they are from 0 to 127
 * @return normalized Y-axis value
 */
uint8_t MPU6050_Accel_Get_Y ();

/*!
 * Returns accelerometer Y-axis value.
 * Values are normalized so they are from 0 to 127
 * @return normalized Y-axis value
 */
uint8_t MPU6050_Accel_Get_Z ();








#endif //PLAYGROUND_MPU6050_H

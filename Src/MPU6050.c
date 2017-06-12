#include <stdlib.h>
#include <MPU6050.h>

I2C_HandleTypeDef* MPU6050_I2C;
char buffer [256];

void MPU6050_Init(I2C_HandleTypeDef* i2c){

    MPU6050_I2C = i2c;

    const uint8_t wait_time = 100;
    const uint8_t config = 0;

    //Enables the MPU6050
    HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_DEVICE_ADDRESS, MPU6050_PWR_MGMT_1, 1, &config, 1, wait_time);

    //Sets scale from -2g to +2g
    HAL_I2C_Mem_Write(MPU6050_I2C, MPU6050_DEVICE_ADDRESS, MPU6050_ACCEL_CONFIG, 1, &config, 1, wait_time);



}

uint8_t MPU6050_Read_Accel (uint8_t dataRegister){

    int8_t result;

    HAL_I2C_Mem_Read(MPU6050_I2C, MPU6050_DEVICE_ADDRESS, dataRegister , 1, &result, 1, 100);

    result += 64;

    return abs(result);

}

uint8_t MPU6050_Accel_Get_X (){
    return MPU6050_Read_Accel(MPU6050_ACCEL_X_OUT);
}

uint8_t MPU6050_Accel_Get_Y (){
    return MPU6050_Read_Accel(MPU6050_ACCEL_Y_OUT);
}
uint8_t MPU6050_Accel_Get_Z (){
    return MPU6050_Read_Accel(MPU6050_ACCEL_Z_OUT);
}



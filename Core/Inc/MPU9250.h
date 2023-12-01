
#ifndef __MPU9250_H
#define __MPU9250_H

#include "stm32f4xx_hal.h"

class MPU9250{
private:
	enum CommunicationMode{
		I2C,
		SPI
	};

	class __I2CData{
	public:
		I2C_HandleTypeDef& hi2c;
		uint16_t address;

		__I2CData(I2C_HandleTypeDef& hi2c,bool AD0):hi2c(hi2c){
			if(AD0 == true){
				address = 0x69 << 1;
			}
			else{
				address = 0x68 << 1;
			}
		}
	};

	const __I2CData I2CData;

public:
    static const uint8_t ACCEL_OUT = 0x3B;
    static const uint8_t GYRO_OUT = 0x43;
    static const uint8_t TEMP_OUT = 0x41;
    static const uint8_t EXT_SENS_DATA_00 = 0x49;
    static const uint8_t ACCEL_CONFIG = 0x1C;
    static const uint8_t ACCEL_FS_SEL_2G = 0x00;
    static const uint8_t ACCEL_FS_SEL_4G = 0x08;
    static const uint8_t ACCEL_FS_SEL_8G = 0x10;
    static const uint8_t ACCEL_FS_SEL_16G = 0x18;
    static const uint8_t GYRO_CONFIG = 0x1B;
    static const uint8_t GYRO_FS_SEL_250DPS = 0x00;
    static const uint8_t GYRO_FS_SEL_500DPS = 0x08;
    static const uint8_t GYRO_FS_SEL_1000DPS = 0x10;
    static const uint8_t GYRO_FS_SEL_2000DPS = 0x18;
    static const uint8_t ACCEL_CONFIG2 = 0x1D;
    static const uint8_t ACCEL_DLPF_184 = 0x01;
    static const uint8_t ACCEL_DLPF_92 = 0x02;
    static const uint8_t ACCEL_DLPF_41 = 0x03;
    static const uint8_t ACCEL_DLPF_20 = 0x04;
    static const uint8_t ACCEL_DLPF_10 = 0x05;
    static const uint8_t ACCEL_DLPF_5 = 0x06;
    static const uint8_t CONFIG = 0x1A;
    static const uint8_t GYRO_DLPF_184 = 0x01;
    static const uint8_t GYRO_DLPF_92 = 0x02;
    static const uint8_t GYRO_DLPF_41 = 0x03;
    static const uint8_t GYRO_DLPF_20 = 0x04;
    static const uint8_t GYRO_DLPF_10 = 0x05;
    static const uint8_t GYRO_DLPF_5 = 0x06;
    static const uint8_t SMPDIV = 0x19;
    static const uint8_t INT_PIN_CFG = 0x37;
    static const uint8_t INT_ENABLE = 0x38;
    static const uint8_t INT_DISABLE = 0x00;
    static const uint8_t INT_PULSE_50US = 0x00;
    static const uint8_t INT_WOM_EN = 0x40;
    static const uint8_t INT_RAW_RDY_EN = 0x01;
    static const uint8_t PWR_MGMNT_1 = 0x6B;
    static const uint8_t PWR_CYCLE = 0x20;
    static const uint8_t PWR_RESET = 0x80;
    static const uint8_t CLOCK_SEL_PLL = 0x01;
    static const uint8_t PWR_MGMNT_2 = 0x6C;
    static const uint8_t SEN_ENABLE = 0x00;
    static const uint8_t DIS_GYRO = 0x07;
    static const uint8_t USER_CTRL = 0x6A;
    static const uint8_t I2C_MST_EN = 0x20;
    static const uint8_t I2C_MST_CLK = 0x0D;
    static const uint8_t I2C_MST_CTRL = 0x24;
    static const uint8_t I2C_SLV0_ADDR = 0x25;
    static const uint8_t I2C_SLV0_REG = 0x26;
    static const uint8_t I2C_SLV0_DO = 0x63;
    static const uint8_t I2C_SLV0_CTRL = 0x27;
    static const uint8_t I2C_SLV0_EN = 0x80;
    static const uint8_t I2C_READ_FLAG = 0x80;
    static const uint8_t MOT_DETECT_CTRL = 0x69;
    static const uint8_t ACCEL_INTEL_EN = 0x80;
    static const uint8_t ACCEL_INTEL_MODE = 0x40;
    static const uint8_t LP_ACCEL_ODR = 0x1E;
    static const uint8_t WOM_THR = 0x1F;
    static const uint8_t WHO_AM_I = 0x75;
    static const uint8_t FIFO_EN = 0x23;
    static const uint8_t FIFO_TEMP = 0x80;
    static const uint8_t FIFO_GYRO = 0x70;
    static const uint8_t FIFO_ACCEL = 0x08;
    static const uint8_t FIFO_MAG = 0x01;
    static const uint8_t FIFO_COUNT = 0x72;
    static const uint8_t FIFO_READ = 0x74;
public:
	const CommunicationMode mode;

	MPU9250(I2C_HandleTypeDef& hi2c,bool AD0);

	void initialize();

	void writeData(uint8_t address,uint8_t data);
	uint8_t readData(uint8_t address);
	void readData(uint8_t address,int size,uint8_t * recv);

	uint8_t whoami();

	uint16_t getRawAccX();
    uint16_t getRawGyrX();
};

#endif

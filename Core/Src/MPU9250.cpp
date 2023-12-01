#include "MPU9250.h"


MPU9250::MPU9250(I2C_HandleTypeDef& hi2c,bool AD0) : I2CData(hi2c,AD0), mode(CommunicationMode::I2C){

}

void MPU9250::initialize(){
	writeData(PWR_MGMNT_1, 	CLOCK_SEL_PLL);
	writeData(USER_CTRL, 	I2C_MST_EN);

	//Set the clock of I2C to 400kHz
	writeData(I2C_MST_CTRL,	I2C_MST_CLK);

	writeData(PWR_MGMNT_2,	SEN_ENABLE);

	writeData(ACCEL_CONFIG,	ACCEL_FS_SEL_16G);

	writeData(GYRO_CONFIG,	GYRO_FS_SEL_2000DPS);

	writeData(ACCEL_CONFIG2,ACCEL_DLPF_184);

	writeData(CONFIG,GYRO_DLPF_184);

	writeData(SMPDIV,0x00);
}

void MPU9250::writeData(uint8_t address,uint8_t data){
	if(mode == CommunicationMode::I2C){
		uint8_t seq[2] = {address,data};

		HAL_I2C_Master_Transmit(&I2CData.hi2c, I2CData.address, seq, 2, 10);
	}
	else{

	}
}

uint8_t MPU9250::readData(uint8_t address){
	if(mode == CommunicationMode::I2C){
		HAL_I2C_Master_Transmit(&I2CData.hi2c, I2CData.address, &address, 1, 10);

		uint8_t recvData;
		HAL_I2C_Master_Receive(&I2CData.hi2c, I2CData.address, &recvData, 1, 10);

		return recvData;
	}
	else{

	}

	return 0;
}

void MPU9250::readData(uint8_t address,int size,uint8_t * recv){
	if(mode == CommunicationMode::I2C){
		HAL_I2C_Mem_Read(&I2CData.hi2c, I2CData.address, address, 1, recv, size, 10);
	}
	else{

	}
}

uint8_t MPU9250::whoami(){
	return readData(WHO_AM_I);
}

uint16_t MPU9250::getRawAccX(){
	uint8_t recv[2] = {0,};
	readData(ACCEL_OUT,2,recv);

	return recv[0] << 8 | recv[1];
}

uint16_t MPU9250::getRawGyrX(){
	uint8_t recv[2] = {0,};
	readData(GYRO_OUT,2,recv);

	return recv[0] << 8 | recv[1];
}
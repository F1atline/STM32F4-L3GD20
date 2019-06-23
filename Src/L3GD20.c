#include "L3GD20.h"

#define NSS_PORT GPIOE
#define NSS_PIN GPIO_PIN_3

uint8_t Read_WHOAMI(SPI_HandleTypeDef hspi1){
	uint8_t REG_WHOAMI = 0;
	uint8_t address = 0;
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	HAL_SPI_Transmit(&hspi1, &address, sizeof(address), 0x1000);
	address = 0x0F;
	HAL_SPI_Transmit(&hspi1, &address, sizeof(address), 0x1000);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_RESET);
	address = 0x8F; //10001111 - WHO_AM_I - READ
	HAL_SPI_Transmit(&hspi1, &address, sizeof(address), 0x1000);
	address = 0x00; //00000000
	HAL_SPI_TransmitReceive(&hspi1, &address, &REG_WHOAMI, sizeof(REG_WHOAMI), 0x1000);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, GPIO_PIN_SET);
	return REG_WHOAMI;
}

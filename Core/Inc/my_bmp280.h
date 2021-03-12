/*
 * bmp280.h
 *
 *  Created on: Mar 6, 2019
 *      Author: vbol
 */

#ifndef MY_BMP280_H_
#define MY_BMP280_H_

#include "main.h"
#include "bmp280_defs.h"
#include "bmp280.h"

//#define CS_OFF	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_RESET)
//#define CS_ON	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, GPIO_PIN_SET)
#define CS_OFF	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_RESET)
#define CS_ON	HAL_GPIO_WritePin(SPI1_CS_GPIO_Port, SPI1_CS_Pin, GPIO_PIN_SET)
extern SPI_HandleTypeDef hspi1;

uint8_t bmp280Read(uint8_t ID, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t NumByteToRead);
uint8_t bmp280Write(uint8_t ID, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite);
uint8_t SPIx_WriteRead(uint8_t Byte);

void Error (void);
void Delay(uint32_t time);


#endif /* MY_BMP280_H_ */

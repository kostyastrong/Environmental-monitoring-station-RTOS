/*
 * BMP280.c
 *
 *  Created on: Mar 6, 2019
 *      Author: vbol
 */

#include "my_bmp280.h"

uint8_t SPIx_WriteRead(uint8_t Byte) {
  uint8_t receivedbyte = 0;
  if(HAL_SPI_TransmitReceive(&hspi1, (uint8_t*) &Byte, (uint8_t*) &receivedbyte, 1, 0x1000) != HAL_OK)
	  printf("hui");
  return receivedbyte;
}


uint8_t bmp280Read(uint8_t ID, uint8_t ReadAddr, uint8_t *pBuffer, uint16_t NumByteToRead) {
  CS_OFF;
  SPIx_WriteRead(ReadAddr);
  while(NumByteToRead > 0x00) {
    /* Send dummy byte (0x00) to generate the SPI clock to bmp280 (Slave device) */
    *pBuffer = SPIx_WriteRead(0x00);
    NumByteToRead--;
    pBuffer++;
  }
  CS_ON;
  return 0;
}

uint8_t bmp280Write(uint8_t ID, uint8_t WriteAddr, uint8_t *pBuffer, uint16_t NumByteToWrite) {
//	CS_ON;
	CS_OFF;
	SPIx_WriteRead(WriteAddr);
	while(NumByteToWrite >= 0x01) {
		SPIx_WriteRead(*pBuffer);
		NumByteToWrite--;
		pBuffer++;
	}
	CS_ON;
}

void Delay(uint32_t time){
	HAL_Delay(time);
}


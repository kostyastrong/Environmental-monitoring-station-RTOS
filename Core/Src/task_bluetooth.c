/*
 * task_bluetooth.c
 *
 *  Created on: Mar 1, 2021
 *      Author: annsi
 */
#include "task_bluetooth.h"
extern double temp;
extern double pres;
extern osSemaphoreId semaphoreHandle;
extern osMutexId mutexHandle;
extern UartInfo uInfoBlth;

double temperature;
double pressure;

static u32 resData[2];
void taskBluetooth(void const * argument){
	uartInitInfo();
	for(;;){
		xSemaphoreTake(semaphoreHandle, portMAX_DELAY);
		xSemaphoreTake(mutexHandle, portMAX_DELAY);
		resData[0] = temp;
		resData[1] = pres;
		xSemaphoreGive(mutexHandle);
		uartTx(resData, sizeof(resData), &uInfoBlth);
	}

}

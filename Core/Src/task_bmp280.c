/*
 * task_bmp280.c
 *
 *  Created on: Mar 1, 2021
 *      Author: annsi
 */


#include "task_bmp280.h"
#include "adc.h"
#define tV_25   1.34f      // Напряжение (в вольтах) на датчике при температуре 25 °C.
#define tSlope  0.0043f    // Изменение напряжения (в вольтах) при изменении температуры на градус.
#define Vref    3.3f       // Образцовое напряжение АЦП (в вольтах).
#define VREFINT_CAL_ADDR 0x1FFFF7BA // адрес в ПЗУ где лежит калибровочное значение
extern osMutexId mutexHandle;
struct bmp280_dev bmp;
struct bmp280_config conf;
double temp;
double pres;

void configBMP();
uint8_t flag = 0;
int16_t Result=0;
const uint16_t V25 = 1750;// when V25=1.41V at ref 3.3V
const uint16_t Avg_Slope = 5; //when avg_slope=4.3mV/C at ref 3.3V
void taskBmp280Monitor(void const * argument){

	/*configBMP();
	struct bmp280_uncomp_data ucomp_data;
	uint8_t meas_dur;
	uint8_t rslt;
	for(;;)
	{
		meas_dur = bmp280_compute_meas_time(&bmp);
		rslt = bmp280_get_uncomp_data(&ucomp_data, &bmp);
		xSemaphoreTake(mutexHandle, portMAX_DELAY);
		temp = bmp280_comp_temp_double(ucomp_data.uncomp_temp, &bmp);
		pres = bmp280_comp_pres_double(ucomp_data.uncomp_press, &bmp);
		xSemaphoreGive(mutexHandle);
	}*/


    float temp;

    HAL_ADCEx_Calibration_Start(&hadc1);
    HAL_ADC_Start_IT(&hadc1);
    for(;;){
    	while(!flag) osDelay(100);
    	temp = (float) Result * 1.0 /4096*Vref;   // Напряжение в вольтах на датчике.
    	temp = (uint16_t)((V25-Result)/Avg_Slope+25);
    	flag = 0;
    	HAL_ADC_Start_IT(&hadc1);

		/*if (HAL_ADC_PollForConversion(&hadc1, 100) == HAL_OK) // Ожидание завершения преобразования.{
			Result = HAL_ADC_GetValue(&hadc1); // Считывание с АЦП.

			temp = (float) Result/4096*Vref;   // Напряжение в вольтах на датчике.
			temp = (tV_25-temp)/tSlope + 25;   // Температура в градусах.                // Приводим данные к формату DS18B20.
			Result = (int16_t) temp;

		}
		HAL_ADC_Stop(&hadc1); // Остановка АЦП.*/
    }

}

void configBMP(){
	CS_OFF;

	 /* Sensor interface over SPI with native chip select line */
	int8_t rslt;
//	  struct bmp280_dev bmp;
//	  struct bmp280_config conf;

	  /* Sensor interface over SPI with native chip select line */
	  bmp.dev_id  =  0;
	  bmp.intf = BMP280_SPI_INTF;
	  bmp.read = bmp280Read;
	  bmp.write = bmp280Write;
	  bmp.delay_ms = Delay;

	  rslt = bmp280_init(&bmp);

	  if (rslt == BMP280_OK) {
	    /* Sensor chip ID will be printed if initialization was successful */
	    printf("\n Device found with chip id 0x%x", bmp.chip_id);
	  }

	  rslt = bmp280_get_config(&conf, &bmp);
//	  if (rslt != BMP280_OK)
//	  			Error();
	  /* Check if rslt == BMP280_OK, if not, then handle accordingly */

	  /* Overwrite the desired settings */
	  conf.filter = BMP280_FILTER_COEFF_2;
	  conf.os_pres = BMP280_OS_16X;
	  conf.os_temp = BMP280_OS_4X;
	  conf.odr = BMP280_ODR_1000_MS;

	  rslt = bmp280_set_config(&conf, &bmp);
//	  if (rslt != BMP280_OK)
//	    			Error();
	  /* Check if rslt == BMP280_OK, if not, then handle accordingly */

	  /* Always set the power mode after setting the configuration */
	  rslt = bmp280_set_power_mode(BMP280_NORMAL_MODE, &bmp);
}

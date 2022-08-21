#include <stdio.h>
#include "freertos/FreeRTOS.h" //for free RTOS to we create
#include "freertos/task.h"	   //for task creation
#include  "freertos/semphr.h"
//#include "freertos/timers.h"   //for timer creation

TaskHandle_t adc_task_handle, process_task_handle;
SemaphoreHandle_t adcSignal;

// return data type created in the adc
void adc_task(void *data)
{
	printf("\nADC Signal Starting the Task\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);
	xSemaphoreGive(adcSignal);
	printf("ADC: Posted Signal to Processing Task\n");
	vTaskDelete(NULL);
	//vTaskDelete(adc_task_handle);
}

// return data type created in the process
void process_task(void *data)
{
	printf("Starting Process Task\n");
	xSemaphoreTake(adcSignal,0);
	printf("Process Task got the signal\n");
	vTaskDelete(NULL);
	//vTaskDelete(process_task_handle);
}

// creating the task to be done
void app_main()
{
	BaseType_t res;
	adcSignal = xSemaphoreCreateBinary();
	printf("THIS IS THE MAIN TASK\n");
	res = xTaskCreate(adc_task, "Serial_task", 2048, NULL, 8, &adc_task_handle);
	res = xTaskCreate(process_task, "Processing_task", 2048, NULL, 5, &process_task_handle);
	if (res != pdPASS)
	{
		perror("Timer is NOT CREATED : \n");
	}
}

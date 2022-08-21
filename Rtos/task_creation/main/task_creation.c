#include<stdio.h>
#include"freertos/FreeRTOS.h"	//for free RTOS to we create
#include"freertos/task.h"	//for task creation
void my_task(void *data)	//for creating the task purpose
{
	printf("My First Task Created\n");
	vTaskDelete(NULL);
}

void app_main()
{
	BaseType_t res;
	TaskHandle_t my_handle;
	printf("MAIN TASK\n");
	res = xTaskCreate(my_task,"sample_task",2048,NULL,3,&my_handle);
	if(res == pdPASS)
	{
		printf("Task Created Successfully\n");
	}
}

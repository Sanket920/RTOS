#include<stdio.h>
#include"freertos/FreeRTOS.h"	//for free RTOS to we create
#include"freertos/task.h"	//for task creation

void my_task(void *data)	//for creating the task purpose
{
	printf("My First Task Created\n");
//	vTaskDelete(NULL);
}

void desd_task(void *data)
{
	printf("My Second Task Created\n");
//	vTaskDelete(NULL);
}

void app_main()
{
	BaseType_t res, res2;

	TaskHandle_t my_handle, desd_handle;
	
	printf("MAIN TASK\n");
	
	res = xTaskCreate(my_task,"sample_task",2048,NULL,5,&my_handle);
	
	res2 = xTaskCreate(desd_task,"task_1",2048,NULL,3,&desd_handle);
	
	if(res == pdPASS)
	{
		printf("Task 1 Created Successfully\n");
	}
	
	if(res2 == pdPASS)
	{
		printf("Task 2 Created Successfully\n");
	}
}

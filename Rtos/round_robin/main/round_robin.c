#include <stdio.h>
#include "freertos/FreeRTOS.h" //for free RTOS to we create
#include "freertos/task.h"	   //for task creation

TaskHandle_t task1_handle, task2_handle, task3_handle;

void task1(void *data) // function return type
{
	int count = 0;							  // for non garbage value
	UBaseType_t prio_1;						  // return type
	prio_1 = uxTaskPriorityGet(task1_handle); // showing priority number for 1st Task
	while (1)
	{
		printf("FIRST TASK\n");
		count += 1;	   // increment by 1
		if (count > 5) // till count 5
		{
			printf("Task 2 is RESUMED\n");
			vTaskResume(task2_handle);
			vTaskSuspend(task1_handle);
			count = 0; // starting from 0
		}
		printf("This is the FIRST TASK and PRIORITY : %d\n", prio_1);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task2(void *data) // function return type
{
	vTaskSuspend(task2_handle);
	int count = 0;
	UBaseType_t prio_2;						  // return type
	prio_2 = uxTaskPriorityGet(task2_handle); // showing priority number for 2nd Task
	while (1)
	{
		printf("SECOND TASK\n");
		count += 1;
		if (count > 5)
		{
			printf("Task 3 is RESUMED\n");
			vTaskResume(task3_handle);
			vTaskSuspend(task2_handle);
			count = 0;
		}
		printf("This is the SECOND TASK and PRIORITY : %d\n", prio_2);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task3(void *data) // function return type
{
	vTaskSuspend(task3_handle);
	int count = 0;
	UBaseType_t prio_3;						  // return type
	prio_3 = uxTaskPriorityGet(task3_handle); // showing priority number for 3rd Task
	while (1)
	{
		printf("THIRD TASK\n");
		count += 1;
		if (count > 5)
		{
			printf("Task 1 is RESUMED\n");
			vTaskResume(task1_handle);
			vTaskSuspend(task3_handle); // suspend the task2 until resume task1
			count = 0;
		}
		printf("This is the THIRD TASK and PRIORITY : %d\n", prio_3);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main()
{
	BaseType_t res1, res2, res3; // for return function
	printf("THIS IS THE MAIN TASK\n");
	res1 = xTaskCreate(task1, "TASK 1", 2048, NULL, 3, &task1_handle);
	res2 = xTaskCreate(task2, "TASK 2", 2048, NULL, 5, &task2_handle);
	res3 = xTaskCreate(task3, "TASK 3", 2048, NULL, 6, &task3_handle);
	if (res1 != pdPASS || res2 != pdPASS || res3 != pdPASS)
	{
		perror("Error in Creating tasks :");
	}
}

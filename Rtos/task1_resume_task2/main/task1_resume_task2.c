#include <stdio.h>
#include "freertos/FreeRTOS.h" //for free RTOS to we create
#include "freertos/task.h"	   //for task creation

TaskHandle_t task1_handle, task2_handle;

void task1(void *data) // function return type
{
	int count = 0; // for non garbage value
	while (1)
	{
		printf("FIRST TASK\n");
		count += 1;	   // increment by 1
		if (count > 5) // till count 5
		{
			printf("Task 2 is now RESUME\n");
			vTaskResume(task2_handle);
			count = 0; // starting from 0
		}
		vTaskDelay(500 / portTICK_PERIOD_MS);
	}
}

void task2(void *data) // function return type
{
	while (1)
	{
		vTaskSuspend(task2_handle); // suspend the task2 until resume task1
		printf("SECOND TASK\n");
	}
}

void app_main()
{
	BaseType_t res1, res2; // for return function
	printf("THIS IS THE MAIN TASK\n");
	res1 = xTaskCreate(task1, "TASK 1", 2048, NULL, 3, &task1_handle);
	res2 = xTaskCreate(task2, "TASK 2", 2048, NULL, 5, &task2_handle);

	// if (task1 && task2 != pdPASS)
	// {
	// 	perror("")
	// }
}

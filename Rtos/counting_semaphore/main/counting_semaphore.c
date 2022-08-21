#include <stdio.h>
#include "freertos/FreeRTOS.h" //for free RTOS to we create
#include "freertos/task.h"	   //for task creation
#include "freertos/semphr.h"

TaskHandle_t task1_handle, task2_handle, task3_handle, task4_handle;
SemaphoreHandle_t serial_counting_sem;

void task1(void *data)
{
	printf("Task 1 : Starting the task\n");
	printf("Task 1 requesting for the serial port\n");
	xSemaphoreTake(serial_counting_sem,pdMS_TO_TICKS(20000));
	printf("Task 1 got the serial port\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);		
	xSemaphoreGive(serial_counting_sem);
	printf("Task 1 released the serial port\n");
	vTaskDelete(NULL);
}

void task2(void *data)
{
	printf("Task 2 : Starting the task\n");
	printf("Task 2 requesting for the serial port\n");
	xSemaphoreTake(serial_counting_sem,pdMS_TO_TICKS(8000));
	printf("Task 2 got the serial port\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);
	xSemaphoreGive(serial_counting_sem);
	printf("Task 2 released the serial port\n");
	vTaskDelete(NULL);
}

void task3(void *data)
{
	printf("Task 3 : Starting the task\n");
	printf("Task 3 requesting for the serial port\n");
	xSemaphoreTake(serial_counting_sem,pdMS_TO_TICKS(5000));
	printf("Task 3 got the serial port\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);
	xSemaphoreGive(serial_counting_sem);
	printf("Task 3 released the serial port\n");
	vTaskDelete(NULL);
}

void task4(void *data)
{
	printf("Task 4 : Starting the task\n");
	printf("Task 4 requesting for the serial port\n");
	xSemaphoreTake(serial_counting_sem,pdMS_TO_TICKS(3000));
	printf("Task 4 got the serial port\n");
	vTaskDelay(1000/portTICK_PERIOD_MS);
	xSemaphoreGive(serial_counting_sem);
	printf("Task 4 released the serial port\n");
	vTaskDelete(NULL);
}

// creating the task to be done
void app_main()
{
	BaseType_t res;
	UBaseType_t mt_prio;
	
	printf("THIS IS THE MAIN TASK\n");
	mt_prio = uxTaskPriorityGet(NULL);
	printf("Main Task : Task created successfully : Prio %d\n",mt_prio);
	serial_counting_sem = xSemaphoreCreateCounting(2,2);	//maximum count, initial count
	
	res = xTaskCreate(task1, "Task_1", 2048, NULL, 8, &task1_handle);
	res = xTaskCreate(task2, "Task_2", 2048, NULL, 8, &task2_handle);
	res = xTaskCreate(task3, "Task_3", 2048, NULL, 8, &task3_handle);
	res = xTaskCreate(task4, "Task_4", 2048, NULL, 8, &task4_handle);
	
	if (res != pdPASS)
	{
		perror("Timer is NOT CREATED : \n");
	}
}

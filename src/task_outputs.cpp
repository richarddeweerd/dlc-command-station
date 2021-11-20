#include "task_outputs.h"

extern TwoWire I2Cone;
extern TwoWire I2Ctwo;
extern SemaphoreHandle_t mutexBus_1;
extern SemaphoreHandle_t mutexBus_2;
extern QueueHandle_t outputQueue;

void TaskOutputs(void *pvParameters)
{
    // Task init

    // signalSetting rcv_msg;

    for (;;)
    {
        //Task main loop
        // if (xQueueReceive(signalQueue, (void *)&rcv_msg, 0) == pdTRUE)
        // {

        // }
        delay(10);
    }
}
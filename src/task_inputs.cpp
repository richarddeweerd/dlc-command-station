#include "task_inputs.h"

extern TwoWire I2Cone;
extern TwoWire I2Ctwo;
extern SemaphoreHandle_t mutexBus_1;
extern SemaphoreHandle_t mutexBus_2;
extern QueueHandle_t inputQueue;

void TaskInputs(void *pvParameters)
{
    // Task init

    // SignalOutput Out_1_1(&I2Cone, 0x22);
    // SignalOutput Out_1_2(&I2Cone, 0x23);
    // SignalOutput Out_2_1(&I2Ctwo, 0x22);
    // SignalOutput Out_2_2(&I2Ctwo, 0x23);

    // xSemaphoreTake(mutexBus_1, portMAX_DELAY);
    // Out_1_1.initialize();
    // xSemaphoreGive(mutexBus_1);

    // xSemaphoreTake(mutexBus_1, portMAX_DELAY);
    // Out_1_2.initialize();
    // xSemaphoreGive(mutexBus_1);

    // xSemaphoreTake(mutexBus_2, portMAX_DELAY);
    // Out_2_1.initialize();
    // xSemaphoreGive(mutexBus_2);

    // xSemaphoreTake(mutexBus_2, portMAX_DELAY);
    // Out_2_2.initialize();
    // xSemaphoreGive(mutexBus_2);

    // signalSetting rcv_msg;

    for (;;)
    {
        //Task main loop
        // if (xQueueReceive(signalQueue, (void *)&rcv_msg, 0) == pdTRUE)
        // {
        //     if (rcv_msg.id < 8)
        //     {
        //         xSemaphoreTake(mutexBus_1, portMAX_DELAY);
        //         Out_1_1.setLight(rcv_msg.id, rcv_msg.status);
        //         xSemaphoreGive(mutexBus_1);
        //     }
        //     else if (rcv_msg.id < 16)
        //     {
        //         xSemaphoreTake(mutexBus_1, portMAX_DELAY);
        //         Out_1_2.setLight(rcv_msg.id, rcv_msg.status);
        //         xSemaphoreGive(mutexBus_1);
        //     }
        //     else if (rcv_msg.id < 24)
        //     {
        //         xSemaphoreTake(mutexBus_2, portMAX_DELAY);
        //         Out_2_1.setLight(rcv_msg.id, rcv_msg.status);
        //         xSemaphoreGive(mutexBus_2);
        //     }
        //     else if (rcv_msg.id < 32)
        //     {
        //         xSemaphoreTake(mutexBus_2, portMAX_DELAY);
        //         Out_2_2.setLight(rcv_msg.id, rcv_msg.status);
        //         xSemaphoreGive(mutexBus_2);
        //     }
        // }
        delay(10);
    }
}
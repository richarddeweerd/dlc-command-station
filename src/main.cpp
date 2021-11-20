#include <Arduino.h>

#include <Wire.h>
#include "task_signals.h"
#include "task_inputs.h"
#include "task_outputs.h"
#include "task_screen.h"

#define SDA_1 21
#define SCL_1 22

#define SDA_2 32
#define SCL_2 33

TaskHandle_t Signals_Task;
TaskHandle_t Inputs_Task;
TaskHandle_t Outputs_Task;
TaskHandle_t Screen_Task;

QueueHandle_t signalQueue;
QueueHandle_t inputQueue;
QueueHandle_t outputQueue;
QueueHandle_t screenQueue;

TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

SemaphoreHandle_t mutexBus_1;
SemaphoreHandle_t mutexBus_2;

int error;

void setup(void)
{
  // pinMode(4, OUTPUT);
  // digitalWrite(4, HIGH);
  Serial.begin(115200);
  Serial.println("Booting");
  mutexBus_1 = xSemaphoreCreateMutex();
  mutexBus_2 = xSemaphoreCreateMutex();

  signalQueue = xQueueCreate(10, sizeof(signalSetting));

  I2Cone.begin(SDA_1, SCL_1, 400000);
  I2Ctwo.begin(SDA_2, SCL_2, 400000);

  xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
      TaskSignals,         // Function to be called
      "Toggle 1",          // Name of task
      1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                // Parameter to pass to function
      0,                   // Task priority (0 to configMAX_PRIORITIES - 1)
      &Signals_Task,       // Task handle
      0);

  xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
      TaskInputs,          // Function to be called
      "Toggle 2",          // Name of task
      1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                // Parameter to pass to function
      0,                   // Task priority (0 to configMAX_PRIORITIES - 1)
      &Inputs_Task,        // Task handle
      0);

  xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
      TaskOutputs,         // Function to be called
      "In",          // Name of task
      1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                // Parameter to pass to function
      0,                   // Task priority (0 to configMAX_PRIORITIES - 1)
      &Outputs_Task,       // Task handle
      0);
  xTaskCreatePinnedToCore( // Use xTaskCreate() in vanilla FreeRTOS
      TaskScreen,          // Function to be called
      "Screen",          // Name of task
      1024,                // Stack size (bytes in ESP32, words in FreeRTOS)
      NULL,                // Parameter to pass to function
      0,                   // Task priority (0 to configMAX_PRIORITIES - 1)
      &Screen_Task,        // Task handle
      0);
}


void loop()
{

  signalSetting msg = {0, 2};
  xQueueSend(signalQueue, (void *)&msg, 10);
  msg = {1, 3};
  xQueueSend(signalQueue, (void *)&msg, 10);

  delay(1000);

  msg = {0, 0};
  xQueueSend(signalQueue, (void *)&msg, 10);
  msg = {1, 0};
  xQueueSend(signalQueue, (void *)&msg, 10);

  delay(1000);
}

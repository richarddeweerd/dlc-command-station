#include "task_screen.h"
#include <TFT_eSPI.h> // Graphics and font library for ST7735 driver chip
#include <SPI.h>
extern QueueHandle_t screenQueue;

TFT_eSPI tft = TFT_eSPI(); // Invoke library, pins defined in User_Setup.h

void TaskScreen(void *pvParameters)
{
    // Task init
    tft.init();
    tft.setRotation(3);
    tft.fillScreen(TFT_BLACK);
    tft.setTextColor(TFT_GREEN, TFT_BLACK); // Adding a black background colour erases previous text automatically
    int x = 0;
    int y = 88;
    int col = 16;
    int row = 4;
    int size = 160 / col;
    int offset = 1;
    for (int j = 0; j < row; j++)
    {
        for (int i = 0; i < col; i++)
        {
            // if (i % 2 == 0)
            // {
            //   tft.fillRect(i * 10, 108 + (10 * j), 10, 10, TFT_GREEN);
            // }
            // if (i % 2 == 1)
            // {
            //   tft.fillRect(i * 10, 108 + (10 * j), 10, 10, TFT_DARKGREEN);
            // }
            // if (i > 8)
            // {
            //   tft.fillRect(i * 10, 108 + (10 * j), 10, 10, TFT_BLACK);
            // }
            tft.drawRect(x + (i * size) + offset, y + (j * size) + offset, size - (2 * offset), size - (2 * offset), TFT_WHITE);
        }
    }
    for (;;)
    {
        //Task main loop
        // if (xQueueReceive(signalQueue, (void *)&rcv_msg, 0) == pdTRUE)
        // {
        // }
        delay(10);
    }
}
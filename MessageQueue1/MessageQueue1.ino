// **********************************************
// ** 06.10.16  - RUST
// **
// ** This project shows how to use a message 
// ** queue on the ATMega 328p.
// ** The program is written in Arduino 1.6.11.
// **
// ** The program is used for education purpose 
// ** on EAL
// **********************************************

#include <Arduino_FreeRTOS.h>
#include <queue.h>
#include <stdlib.h>

void threadMeasure(void* pvParameters);
void threadPrint(void* pvParameters);

QueueHandle_t queue;

typedef struct {
  int temperature;
  int humidity;
}weather_data_t;

void setup() {  
  Serial.begin(9600);
  Serial.println("Serial Started");
  queue = xQueueCreate (8, sizeof(weather_data_t));
  
  // Initialize threadMeasure
  xTaskCreate(
    threadMeasure,                       // Name of the Thread funktion
    (const portCHAR *) "Thread Measure", // A name just for humans
    128,                                 // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,                                // No parameters
    2,                                   // Priority, with 1 being the highest, and 4 being the lowest.
    NULL);

  // Initialize ThreadPrint
  xTaskCreate(
    threadPrint,                        // Name of the Thread funktion
    (const portCHAR *) "Thread Print",  // A name just for humans
    128,                                // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,                               // No parameters
    2,                                  // Priority, with 1 being the highest, and 4 being the lowest.
    NULL);

}

void loop() {

}

// Thread Measure
void threadMeasure(void* pvParameters __attribute__((unused)))
{
  int number;
  weather_data_t ptr;
  for(;;)
  {
    number = random(-20, 50);
    ptr.temperature = number;
    number = random(0, 100);
    ptr.humidity = number;
    Serial.print("ThreadMeas: Temp = ");
    Serial.print(ptr.temperature);
    Serial.print(", Hum = ");
    Serial.println(ptr.humidity);
    number = random(1, 30);
    vTaskDelay(number);
    xQueueSendToBack (queue, (void*) &ptr, portMAX_DELAY);
  }
}

// Implementation of Thread Print
void threadPrint(void* pvParameters __attribute__((unused)))
{
  weather_data_t ptr;
  for(;;)
  {
    do {
      xQueueReceive (queue, (void*) &ptr, portMAX_DELAY);
      Serial.print("ThreadPrint: Temp =  ");
      Serial.print(ptr.temperature);
      Serial.print(", Hum = ");
      Serial.println(ptr.humidity);
    } while (uxQueueMessagesWaiting(queue) > 0);
    vTaskDelay(50);
  }
}

// **********************************************
// ** 22.09.16  - RUST
// **
// ** This project shows how to use a mutex
// ** on the ATMega 328p.
// ** The program is written in Arduino 1.6.11.
// **
// ** The program is used for education purpose 
// ** on EAL
// **********************************************

#include <Arduino_FreeRTOS.h>
#include <semphr.h>

// Create a global instance of the semaphore. 
SemaphoreHandle_t xSemaphore;

// Forward decleration of the two threads.
void ThreadA (void* pvParameters);
void ThreadB (void* pvParameters);

void setup() {
  Serial.begin(115200);

  // Initialize the semaphore nicely
  if (xSemaphore == NULL) {
    xSemaphore = xSemaphoreCreateMutex();
    if (xSemaphore != NULL) {
      xSemaphoreGive(xSemaphore);
    } // else do nothing - semaphore already created.
  } // else do nothing - semaphore already created.

  // Initialize ThreadA
  xTaskCreate(
    ThreadA,                        // Name of the Thread funktion
    (const portCHAR *) "Thread A",  // A name just for humans
    64,                             // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,                           // No parameters
    2,                              // Priority, with 1 being the highest, and 4 being the lowest.
    NULL);

  // Initialize ThreadB
  xTaskCreate(
    ThreadB,                        // Name of the Thread funktion
    (const portCHAR *) "Thread B",  // A name just for humans
    64,                             // This stack size can be checked & adjusted by reading the Stack Highwater
    NULL,                           // No parameters
    2,                              // Priority, with 1 being the highest, and 4 being the lowest.
    NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void ThreadA(void* pvParameters __attribute__((unused)))
{
  for(;;)
  {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY ) == pdTRUE)
    {
      Serial.println("Hi from A");
      xSemaphoreGive(xSemaphore);    
    }
    vTaskDelay(1);
  }
}

// Implementation of ThreadB
void ThreadB(void* pvParameters __attribute__((unused)))
{
  for(;;)
  {
    if (xSemaphoreTake(xSemaphore, portMAX_DELAY ) == pdTRUE)
    {
      Serial.println("Hi from B");
      xSemaphoreGive(xSemaphore);    
    }
    vTaskDelay(1);
  }
}


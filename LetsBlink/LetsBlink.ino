// **********************************************
// ** 22.09.16  - RUST
// **
// ** This project implements the lets blink
// ** exercise.
// ** The program is written in Arduino 1.6.11.
// **
// ** The program is used for education purpose 
// ** on EAL
// **********************************************
#include <Arduino_FreeRTOS.h>
#include <semphr.h>

#define RED_LED 10
#define GREEN_LED 11
#define YELLOW_LED 12

void ThreadRED(void* pvParameters);
void ThreadYELLOW(void* pvParameters);
void ThreadGREEN(void* pvParameters);

SemaphoreHandle_t xSem_RedGreen;
SemaphoreHandle_t xSem_GreenYellow;
SemaphoreHandle_t xSem_YellowRed;

void setup() {
  Serial.begin(250000);
  
  // Prepare the semaphores
  if (xSem_YellowRed == NULL) {
    xSem_YellowRed = xSemaphoreCreateBinary(); 
    if (xSem_YellowRed != NULL) {
      xSemaphoreGive(xSem_YellowRed);  // Initially signal first semaphore 
    } // else do nothing - a warning message would have been good.
  } // else do nothing - an assertion would have been good
  
  if (xSem_RedGreen == NULL) {
    xSem_RedGreen = xSemaphoreCreateBinary(); // Signalling not necessary
  }

  if (xSem_GreenYellow == NULL) {
    xSem_GreenYellow = xSemaphoreCreateBinary(); // Signalling not necessary
  } // else do nothing - an assertion would have been good

  xTaskCreate (
    ThreadRED,
    (const portCHAR *) "ThreadRED", 
    128,
    NULL,
    1,
    NULL);

  xTaskCreate (
    ThreadGREEN,
    (const portCHAR *) "ThreadRED", 
    128,
    NULL,
    1,
    NULL);

  xTaskCreate (
    ThreadYELLOW,
    (const portCHAR *) "ThreadRED", 
    128,
    NULL,
    1,
    NULL);
}

void loop() {
  // put your main code here, to run repeatedly:
}

void blinkLED(unsigned int pin) {
  digitalWrite(pin, HIGH);
  vTaskDelay(5);
  digitalWrite(pin, LOW);
}

void initializeLED(unsigned int pin) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void ThreadRED(void* pvParameters __attribute__ ((unused))) {
  int randNumber;
  // Initialize LED pin
  initializeLED(RED_LED);

  for (;;)
  {
    if ( xSemaphoreTake(xSem_YellowRed, portMAX_DELAY) == pdTRUE ) {
      // Semaphore aquired - blink LED and signal next thread
      randNumber = random(1, 30);
      vTaskDelay(randNumber);
      
      blinkLED(RED_LED);
      Serial.println("RED");
      xSemaphoreGive(xSem_RedGreen);
    }
  }
}

void ThreadGREEN(void* pvParameters __attribute__ ((unused))) {
  // Initialize LED pin
  initializeLED(GREEN_LED);
  
  for (;;)
  {
    if ( xSemaphoreTake(xSem_RedGreen, portMAX_DELAY) == pdTRUE ) {
      // Semaphore aquired - blink LED and signal next thread
      blinkLED(GREEN_LED);
      Serial.println("GREEN");
      xSemaphoreGive(xSem_GreenYellow);
    }
  }
}

void ThreadYELLOW(void* pvParameters __attribute__ ((unused))) {
  // Initialize LED pin
  initializeLED(YELLOW_LED);
  
  for (;;)
  {
    if ( xSemaphoreTake(xSem_GreenYellow, portMAX_DELAY) == pdTRUE ) {
      // Semaphore aquired - blink LED and signal next thread
      blinkLED(YELLOW_LED);
      Serial.println("YELLOW");
      xSemaphoreGive(xSem_YellowRed);
    }
  }
}

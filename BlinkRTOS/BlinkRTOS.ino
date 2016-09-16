// **********************************************
// ** 16.09.16  - RUST
// **
// ** This project implements a thread on 
// ** ATMega328p which blinks a LED. 
// ** The program is written in Arduino 1.6.11.
// **
// ** The program is used for education purpose 
// ** on EAL
// **********************************************

#include <Arduino_FreeRTOS.h>

// Defines the pins with the LEDs
#define PIN_YELLOW 12
#define PIN_GREEN  11
#define PIN_RED    10

// define one task for Blink 
void TaskBlinkYellow( void *pvParameters );

// The setup function runs once when you press reset or power the board
void setup() {

  // Now set up one task to run independently.
  xTaskCreate(
    TaskBlinkYellow
    ,  (const portCHAR *)"Blink Yellow"   // A name just for humans
    ,  64  // Stack size
    ,  NULL
    ,  2  // priority
    ,  NULL );

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/

void TaskBlinkYellow(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin 13 as an output.
  pinMode(PIN_YELLOW, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(PIN_YELLOW, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(PIN_YELLOW, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 1000 / portTICK_PERIOD_MS ); // wait for one second
  }
}


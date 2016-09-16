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
void TaskBlinkGreen( void *pvParameters );

// The setup function runs once when you press reset or power the board
void setup() {
  unsigned short timeout = 200;

  // Now set up one task to run independently.  
  xTaskCreate(
    TaskBlinkYellow                       // The task function
    ,  (const portCHAR *)"Blink Yellow"   // A name just for humans
    ,  64                                 // Stack size (buswidth x size)
    ,  (void*)&timeout                    // Arguments to the task
    ,  2                                  // priority     
    ,  NULL );                            // ??

  xTaskCreate(TaskBlinkGreen, (const portCHAR *)"Blink Green", 64, NULL, 2, NULL ); 

  // Now the task scheduler, which takes over control of scheduling individual tasks, is automatically started.
}

void loop()
{
  // Empty. Things are done in Tasks.
}

/*--------------------------------------------------*/
/*---------------------- Tasks ---------------------*/
/*--------------------------------------------------*/
// The thread implementation for the yellow LED
void TaskBlinkYellow(void *pvParameters)  // This is a task.
{
  (void) pvParameters;
  unsigned short timeout = (unsigned short) (*pvParameters);
  // Initialize digital pin with the yellow LED as an output.
  pinMode(PIN_YELLOW, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(PIN_YELLOW, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( timeout / portTICK_PERIOD_MS ); // wait for one second
    digitalWrite(PIN_YELLOW, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( timeout / portTICK_PERIOD_MS ); // wait for one second
  }
}

// The thread implementation for the Green LED
void TaskBlinkGreen(void *pvParameters)  // This is a task.
{
  (void) pvParameters;

  // initialize digital pin with the green LED as an output.
  pinMode(PIN_GREEN, OUTPUT);

  for (;;) // A Task shall never return or exit.
  {
    digitalWrite(PIN_GREEN, HIGH);   // turn the LED on (HIGH is the voltage level)
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for 0.5 seconds
    digitalWrite(PIN_GREEN, LOW);    // turn the LED off by making the voltage LOW
    vTaskDelay( 500 / portTICK_PERIOD_MS ); // wait for 0.5 second
  }
}


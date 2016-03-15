/*
 * main.cpp
 *
 *  Created on: 16 марта 2016 г.
 *      Author: kot
 */

#include    "FreeRTOSConfig.h"
#include    "FreeRTOS.h"
#include    "stm32f2xx_hal.h"
#include "BlinkLed.h"
#include "task.h"
//#include "dummy.h"
#include <stdio.h>
#include <stdlib.h>
//#include "diag/Trace.h"




#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

#define BLINK_PORT_NUMBER         (1)
#define BLINK_PIN_NUMBER_GREEN    (2)
#define BLINK_PIN_NUMBER_ORANGE   (13)
#define BLINK_PIN_NUMBER_RED      (14)
#define BLINK_PIN_NUMBER_BLUE     (15)
#define BLINK_ACTIVE_LOW          (false)

BlinkLed blinkLeds[1] =
  {
    { BLINK_PORT_NUMBER, BLINK_PIN_NUMBER_GREEN, BLINK_ACTIVE_LOW }

  };


void vTaskLED1(void *pvParameters) {

        for (;;) {
                blinkLeds[0].turnOn();

                vTaskDelay(800);
                blinkLeds[0].turnOff();
                vTaskDelay(250);

        }

}

void vTaskDisplayInit(void *pvParameters) {



    vTaskDelete(NULL);

}

int
main(int argc, char* argv[])
{




    // Perform all necessary initialisations for the LEDs.
     for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
       {
         blinkLeds[i].powerUp ();
       }


     for (size_t i = 0; i < (sizeof(blinkLeds) / sizeof(blinkLeds[0])); ++i)
       {
         blinkLeds[i].turnOn ();

       }


     // Enable GPIO Peripheral clock
     RCC->AHB1ENR |= (1<<5);

     GPIO_InitTypeDef GPIO_InitStructure;

     // Configure pin in output push/pull mode
     GPIO_InitStructure.Pin = GPIO_PIN_9;
     GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;
     GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
     GPIO_InitStructure.Pull = GPIO_NOPULL;
     HAL_GPIO_Init (GPIOE, &GPIO_InitStructure);





      xTaskCreate( vTaskLED1, ( const char * ) "LED1", configMINIMAL_STACK_SIZE, NULL, 1,
                              ( xTaskHandle * ) NULL);
      xTaskCreate( vTaskDisplayInit, ( const char * ) "DispInit", configMINIMAL_STACK_SIZE, NULL, 2,
                              ( xTaskHandle * ) NULL);


      vTaskStartScheduler();



}

#pragma GCC diagnostic pop

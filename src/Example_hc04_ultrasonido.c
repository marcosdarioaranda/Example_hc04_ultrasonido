/*
===============================================================================
 Name        : Example_hc04_ultrasonido.c
 Author      : Ms. Ing, Marcos D. Aranda
 Version     : 1.0
 Copyright   : $(copyright)
 Description : Este ejemplo utilizada un sensor de ultrasonido HC-SR04 y la placa
               LPC1769
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>

// TODO: insert other include files here
#include <sapi_uart.h>
#include <sapi_gpio.h>
#include "retardos.h"
#include "timer.h"
// TODO: insert other definitions and declarations here

uint32_t distancia = 0;
void *InterrupcionTimer;

uint32_t LeerSensorDistancia(void)
{
  uint32_t contador=0;

  gpioWrite(0,28, ON);
  delayUs(0,10);
  gpioWrite(0,28, OFF);

  do {} while (gpioRead(0,27) == 0);
  do {
    contador++;
	delayUs(0,1);
  } while ((gpioRead(0,27) == 1) | (contador == 6400));

  return contador*2/58;		//convierte a cm
}

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

    // TODO: insert code here

     /*Inicializo la UART3 a 115200 baudios */
     uartInit( UART_3, 115200 );

     /*Interrupción de 1 segundo*/
     timerInit(1000,&InterrupcionTimer);

     /*Inicializo el LED2 como salida*/
     gpioInit(0,22,GPIO_OUTPUT);

     /*Pines del Sensor de Ultrasonido HC-SR04*/
     gpioInit(0,27,GPIO_INPUT);
     gpioInit(0,28,GPIO_OUTPUT);

     while(1){
    	 /*Leo la distancia en CM*/
    	 distancia=LeerSensorDistancia();

    	 if (distancia>50){
    		gpioWrite(0,28, ON);
         }
		else{
			gpioWrite(0,28, OFF);
		}

     }
  return 0;
}

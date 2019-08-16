/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "board.h"
#include "gpio.h"
#include <stdlib.h>

/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

static void delayLoop(uint32_t veces);


/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */

int past_state;
int curr_state;
int button_pressed;

void App_Init (void)
{
    //gpioMode(PIN_LED_GREEN, OUTPUT);
    gpioMode(PIN_LED_EXT, OUTPUT);

    //gpioMode(PIN_SW3, INPUT);
    //gpioMode(PIN_SW2, INPUT);
    gpioMode(PIN_SW_EXT, INPUT);

    past_state = LOW;			//el led se prende en LOW
    curr_state = past_state;
    gpioWrite (PIN_LED_GREEN, past_state);
    button_pressed = false;
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	//curr_state = !gpioRead(PIN_SW3);
	curr_state = !gpioRead(PIN_SW_EXT);
	if( curr_state != past_state){
		if(button_pressed)
			button_pressed = !button_pressed;
		else{
			gpioToggle(PIN_LED_EXT);
			button_pressed = 1;
		}
		past_state = curr_state;
	}
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

static void delayLoop(uint32_t veces)
{
    while (veces--);
}


/*******************************************************************************
 ******************************************************************************/

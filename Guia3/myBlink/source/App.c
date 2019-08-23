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
static bool tooglear_baliza();

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */

int past_state;
int curr_state;
bool button_pressed;
bool baliza_on;
void App_Init (void)
{
    gpioMode(PIN_LED_EXT, OUTPUT);
    gpioMode(PIN_LED_RED, OUTPUT);
    gpioMode(PIN_SW_EXT, INPUT);
    past_state = LOW;			//el led se prende en LOW
    curr_state = past_state;
    gpioWrite (PIN_LED_EXT, past_state);
    gpioWrite (PIN_LED_RED, HIGH);
    button_pressed = false;
    baliza_on = false;
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
	int timer_count = 0;
	while(timer_count < 10){
		curr_state = !gpioRead(PIN_SW_EXT);
		if( curr_state != past_state){
			if(button_pressed)
				button_pressed = !button_pressed;	//boton dejo de presionarse
			else if(tooglear_baliza())			//el boton recien se presio
				break;
			past_state = curr_state;
		}
		delayLoop(1200000uL);
		timer_count++;
	}
	if(baliza_on)
		gpioToggle(PIN_LED_EXT);


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
static bool tooglear_baliza(){
	bool apagada = false;
	baliza_on = !baliza_on;				//se tooglea la baliza
	gpioWrite(PIN_LED_RED, !baliza_on);	//el led sigue a la baliza
	button_pressed = 1;
	if(!baliza_on){
		if(gpioRead(PIN_LED_EXT) == HIGH){
			gpioToggle(PIN_LED_EXT);
			apagada = true;
		}
	}
	return apagada;
}

/*******************************************************************************
 ******************************************************************************/

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
#include "SysTick.h"



/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

#define BLINK_FREQ_HZ 2U
#if SYSTICK_ISR_FREQUENCY_HZ % (2*BLINK_FREQ_HZ) != 0
#warning BLINK cannot implement this exact frequency.
		Using floor(SYSTICK_ISR_FREQUENCY_HZ/BLINK_FREQ_HZ/2) instead.
#endif


/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

void systick_callback(void);

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_LED_BLUE, OUTPUT);


    void (*asd)(void) = &systick_callback;
    SysTick_Init(asd);
}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
    while (1) { ; }
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

void systick_callback(void)
{
	static uint32_t counter = 0;

	// use counter for dividing systick frequency
	if (counter == SYSTICK_ISR_FREQUENCY_HZ/BLINK_FREQ_HZ/2) {
		// toggle pin twice per period
		gpioToggle(PIN_LED_BLUE);
		counter = 0;
	}
	else {
		counter++;
	}

}


/*******************************************************************************
 ******************************************************************************/

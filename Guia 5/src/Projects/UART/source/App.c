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
#include "uart.h"
/*******************************************************************************
 * CONSTANT AND MACRO DEFINITIONS USING #DEFINE
 ******************************************************************************/

/*******************************************************************************
 * FUNCTION PROTOTYPES FOR PRIVATE FUNCTIONS WITH FILE LEVEL SCOPE
 ******************************************************************************/

/*******************************************************************************
 *******************************************************************************
                        GLOBAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    gpioMode(PIN_LED_BLUE, OUTPUT);

    uart_cfg_t config;
    config.baudrate = 9600;
    config.parity = false;
    config.eight_bit_word = true;

    uartInit(0, config);
    //uartInitAri();

	//uart_putchar(UART0, '5');

}

/* Función que se llama constantemente en un ciclo infinito */
void App_Run (void)
{
//	static int i = 0;
//
//	while (!(UART0->S1 & 0x80)){}
//	unsigned int j = 100000;
//	while (j < 1000) j--;
//
//	if (i % 2 == 0){
//	//	UART0->C3 |= UART_C3_T8_SHIFT; // enviamos un 1
//		uart_putchar(UART3, 0x55);
//	}else{
//		//UART0->C3 &= ~0x40; //enviamos un 1
//		//UART0->D = 0x55;
//		uart_putchar(UART3, 0x55);
//		//UART0->C3 |= UART_C3_T8_SHIFT; // enviamos un 0
////		UART0->D = 0x00;
//	}
//	i ++;

	unsigned char buffer[10];
	uint8_t n;
	if (uartIsRxMsg(0)) {
		n = uartReadMsg(0, buffer, 10);
		uartWriteMsg(0, buffer, n);

		volatile uint32_t i = 0;
		while (!uartIsTxMsgComplete(0)) {
			i++;
		}
		i = 0;
	}

//	char c = uart_getchar(UART0);
//	uart_putchar(UART0, c);
//	uart_putchar(UART0, c);
//	uart_putchar(UART0, c);
			//delayLoop(0xFFFFFFFF);



//	UART_Type * uart = UART0;
//	while(!(uart->S1 & UART_S1_TDRE_MASK)) {
//		;
//	}
//
//	uart->D = '0';
}


/*******************************************************************************
 *******************************************************************************
                        LOCAL FUNCTION DEFINITIONS
 *******************************************************************************
 ******************************************************************************/



/*******************************************************************************
 ******************************************************************************/




/***************************************************************************//**
  @file     App.c
  @brief    Application functions
  @author   Nicolás Magliola
 ******************************************************************************/

/*******************************************************************************
 * INCLUDE HEADER FILES
 ******************************************************************************/

#include "pc_interface/pc_interface.h"
#include "pc_interface/UART/uart.h"
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

#define MSG_LEN 8

/* Función que se llama 1 vez, al comienzo del programa */
void App_Init (void)
{
    pc_init();
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

	unsigned char buffer[MSG_LEN+1];
	uint8_t n;
	if (uartIsRxMsg(0)) {
		n = uartReadMsg(0, buffer, MSG_LEN);
		buffer[n] = 0;
		pc_send(buffer);
	}

	pc_periodic();
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




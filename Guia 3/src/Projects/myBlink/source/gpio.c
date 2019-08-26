/*
 * gpio.c
 *
 *  Created on: 24 ago. 2019
 *      Author: Tomas
 */
#include "gpio.h"
#include "MK64F12.h"
#include <stdint.h>

static void initial_conf_pcr(int port_num, int pin_num);
static void initial_conf_gpio(int port_num, int pin_num);
static void set_input_mode(int port_num, int pin_num);
static void set_output_mode(int port_num, int pin_num);
static void set_input_pulldown_mode(int port_num, int pin_num);
static void set_input_pullup_mode(int port_num, int pin_num);

//queda todo como en reset
void gpioMode (pin_t pin, uint8_t mode){
	int port_num = PIN2PORT(pin);
	int pin_num = PIN2NUM(pin);

	// Poner el registo PCR en un estado casi de reset
	initial_conf_pcr(port_num, pin_num);
	// poner los pines de los regstros de GPIO en estado de reset
	initial_conf_gpio(port_num, pin_num);

	switch(mode){
	case INPUT:
		set_input_mode(port_num, pin_num);
		break;
	case OUTPUT:
		set_output_mode(port_num, pin_num);
		break;
	case INPUT_PULLDOWN:
		set_input_pulldown_mode(port_num, pin_num);
		break;
	case INPUT_PULLUP:
		set_input_pullup_mode(port_num, pin_num);
		break;
	default:
		//Excepcion!!!
		break;
	}
}

/***********************************
*********initial_conf_pcr**********
************************************
* initial_conf_pcr deja configurada a una estructura
* PORT_Type como quedaria configurada luego de un reset
* de maquina para el pin N en especfico, a excepcion
* del MUX, que es seteado a GPIO:
*	MUX = 001
*	DSE = 1 (PTA0 a PTA5), 0 (c.c)
*	PFE = 0
*	SRE = 0
*	PE = 0
*	PS = 0
*	ISF = 1
*	LK = 0
*	INPUT:
*		- port_conf : Estructura que sera modificada
*		- port_num : numero de puerto cuyos valores de port_conf seran
*		- pin_num : numero de pin cuyos valores de port_conf seran actualizados.
*	OUTPUT:
*		void. Todo se cambia por referencia.
*/
static void initial_conf_pcr (int port_num, int pin_num){

	PORT_Type * addr_array[] = PORT_BASE_PTRS;
	PORT_Type * port = addr_array[port_num];

	port->PCR[pin_num] = 0;
	port->PCR[pin_num] |= 1 << PORT_PCR_MUX_SHIFT;
	port->PCR[pin_num] |= 1 << PORT_PCR_ISF_SHIFT;
	if(port_num == PA && pin_num <= 5){
		port->PCR[pin_num] |= 1 << PORT_PCR_DSE_SHIFT;
	}

}

/***********************************
*********initial_conf_gpio**********
************************************
* initial_conf_gpio deja configurado a una estructura
* GPIO_Type como quedaria configurada luego de un reset
* de maquina para el pin N en especfico. Esto quiere decir:
*	pdor todo a cero
*	psor todo a cero
*	pcor todo a cero
*	ptor todo a cero
*	pddr todo a cero
*	pdir no se toca porque es de input y no se puede modificar
*
*	INPUT:
*		- gpio_conf : Estructura que sera modificada con los valores de reset por referencia
*		- pin_num : numero de pin cuyos valores de gpio_conf seran actualizados a reset.
*	OUTPUT:
*		void. Todo se cambia por referencia.
*/
static void initial_conf_gpio(int port_num, int pin_num){

	GPIO_Type * addr_array[] = GPIO_BASE_PTRS;
	GPIO_Type * gpio = addr_array[port_num];

	gpio->PCOR &= ~(1 << pin_num);
	gpio->PDDR &= ~(1 << pin_num);
	gpio->PDOR &= ~(1 << pin_num);
	gpio->PSOR &= ~(1 << pin_num);
	gpio->PTOR &= ~(1 << pin_num);

}

static void set_input_mode(int port_num, int pin_num){
	//from the MK64 reference manual, section 55.2.6:
	//0 : Pin is configured as general-purpose input, for the GPIO function.
	GPIO_Type * addr_array[] = GPIO_BASE_PTRS;
	GPIO_Type * gpio = addr_array[port_num];
	gpio->PDDR &= ~(1 << pin_num);
}

static void set_output_mode(int port_num, int pin_num){
	//from the MK64 reference manual, section 55.2.6:
	//1 : Pin is configured as general-purpose output, for the GPIO function.
	GPIO_Type * addr_array[] = GPIO_BASE_PTRS;
	GPIO_Type * gpio = addr_array[port_num];
	gpio->PDDR |= (1 << pin_num);
}

static void set_input_pulldown_mode(int port_num, int pin_num){
	set_input_mode(port_num, pin_num);
	/*from the MK64 reference manual, section 11.5.1, PORTx_PCRn field descriptions
	 * 	PE:
	 		1 : Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a
digital input.
	 *	PS:
			0 : Internal pulldown resistor is enabled on the corresponding pin, if the corresponding PE field is set.*/
	PORT_Type * addr_arrays[] = PORT_BASE_PTRS;
	PORT_Type * port = addr_arrays[port_num];
	port->PCR[pin_num] |= (1 & ~(1 << 1));	//sets b0 to 1, enabling PE, and sets bit1 to 0 for pulldown.

}

static void set_input_pullup_mode(int port_num, int pin_num){
	set_input_mode(port_num, pin_num);
	/*from the MK64 reference manual, section 11.5.1, PORTx_PCRn field descriptions
	 * 	PE:
	 		1 : Internal pullup or pulldown resistor is enabled on the corresponding pin, if the pin is configured as a
digital input.
	 *	PS:
			1 : Internal pullup resistor is enabled on the corresponding pin, if the corresponding PE field is set.*/
	PORT_Type * addr_arrays[] = PORT_BASE_PTRS;
	PORT_Type * port = addr_arrays[port_num];
	port->PCR[pin_num] |= (uint32_t) 0x2;			//sets both bit0 and bit1, setting PS in pullup and enabling PE respectively.
}

void gpioWrite (pin_t pin, bool value){

}

void gpioToggle (pin_t pin){

}

bool gpioRead (pin_t pin){
	return true;
}

/*
 * gpio.c
 *
 *  Created on: 24 ago. 2019
 *      Author: Tomas
 */
#include "gpio.h"
#include "MK64F12.h"

static void initial_conf_pcr (PORT_Type* port_conf, int pin_num);

static void initial_conf_gpio(GPIO_Type* gpio_conf, int pin_num);
static void set_input_mode(GPIO_Type* gpio_conf);
static void set_output_mode(GPIO_Type* gpio_conf);
static void set_input_pulldown_mode(GPIO_Type* gpio_conf);
static void set_input_pullup_mode(GPIO_Type* gpio_conf);

//queda todo como en reset
void gpioMode (pin_t pin, uint8_t mode){
	//int port_num = PIN2PORT(pin);
	int pin_num = PIN2NUM(pin);
	//char * memory_map = ORIGIN + port_num * OFFSET;
	PORT_Type port_conf;
	GPIO_Type gpio_conf;

	initial_conf_pcr(&port_conf, pin_num);
	initial_conf_gpio(&gpio_conf, pin_num);

	switch(mode){
	case INPUT:
		set_input_mode(&gpio_conf);
		break;
	case OUTPUT:
		set_output_mode(&gpio_conf);
		break;
	case INPUT_PULLDOWN:
		set_input_pulldown_mode(&gpio_conf);
		break;
	case INPUT_PULLUP:
		set_input_pullup_mode(&gpio_conf);
		break;
	default:
		//Excepcion!!!
		break;
	};
	//copy_2_memory_map();
	//copy_2_memory_map();

}
//internal pullup y pulldown desactivados.
// MUX en 001 (ESTE NO ES SEGUN RESET, ES EN GPIO!!!)
// DSE pta0 a pta5 enabled(1), el resto todo en disabled
// PFE	Disabled (0) control
// SRE Disabled (0)
// PE Disabled (0)
// PS No lo tocamos
// ISF w1c, asi que le escribimos un 1.
// LK no se toca

static void initial_conf_pcr (PORT_Type* port_conf, int pin_num){

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
*	pdir todo a cero
*	pddr todo a cero
*
*	INPUT:
*		- gpio_conf : Estructura que sera modificada con los valores de reset por referencia
*		- pin_num : numero de pin cuyos valores de gpio_conf seran actualizados a reset.
*	OUTPUT:
*		void. Todo se cambia por referencia.
*/
static void initial_conf_gpio(GPIO_Type* gpio_conf, int pin_num){

	uint32_t empty_word = 0;
	gpio_conf->PDOR = empty_word;
	gpio_conf->PSOR = empty_word;
	gpio_conf->PCOR = empty_word;
	gpio_conf->PTOR = empty_word;
	gpio_conf->PDIR = empty_word;
	gpio_conf->PDDR = empty_word;

}

static void set_input_mode(GPIO_Type* gpio_conf){

}
static void set_output_mode(GPIO_Type* gpio_conf){

}
static void set_input_pulldown_mode(GPIO_Type* gpio_conf){

}
static void set_input_pullup_mode(GPIO_Type* gpio_conf){

}
void gpioWrite (pin_t pin, bool value){

}

void gpioToggle (pin_t pin){

}

bool gpioRead (pin_t pin){
	return true;
}

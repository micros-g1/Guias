/*
 * gpio.c
 *
 *  Created on: 24 ago. 2019
 *      Author: Tomas
 */
#include "gpio.h"
#include "MK64F12.h"

static void conf_initial_pcr (PORT_Type* port_conf, int pin_num);
static void conf_initial_gpio(GPIO_Type* gpio_conf, int pin_num);
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

	conf_initial_pcr(&port_conf, pin_num);
	conf_initial_gpio(&gpio_conf, pin_num);

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

static void conf_initial_pcr (PORT_Type* port_conf, int pin_num){

}

//PARA EL PIN N EN ESPECIFICO!!
// pdor todo a cero
// psor todo a cero
// pcor todo a cero
// ptor todo a cero
// pdir todo a cero
// pddr todo a cero
static void conf_initial_gpio(GPIO_Type* gpio_conf, int pin_num){

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

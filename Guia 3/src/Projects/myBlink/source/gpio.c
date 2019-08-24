/*
 * gpio.c
 *
 *  Created on: 24 ago. 2019
 *      Author: Tomas
 */
#include "gpio.h"

//queda todo como en reset
void gpioMode (pin_t pin, uint8_t mode){
	int puerto = PIN2PORT(pin);
	int pin = PIN2NUM(pin);
	char * memory_map = ORIGIN + puerto * sizeof(PORT_type);
	PORT_Type puerto;
	switch(mode){
	case INPUT:
		//internal pullup y pulldown desactivados.
		// MUX en 001
		// DSE
		// PFE
		// SRE
		// PE
		// PS
		// ISF w1c, asi que le escribimos un 1.
		// PFE
		set_input_mode(&puerto);
	case OUTPUT:
	case INPUT_PULLDOWN:
	case INPUT_PULLUP:
	}


	copy_2_memory_map();
	GPIO_Type gpio;
	char * memory_map2 = + pin;


}

void gpioWrite (pin_t pin, bool value){

}

void gpioToggle (pin_t pin){

}

bool gpioRead (pin_t pin){
	return true;
}

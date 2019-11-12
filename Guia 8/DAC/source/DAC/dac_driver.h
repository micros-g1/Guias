#ifndef DAC_DRIVER_H_
#define DAC_DRIVER_H_

#include "MK64F12.h"

typedef uint16_t dac_data_t;


void dac_init();
void dac_trigger();

/*
 * Cuando buffer esta disabled, setea DATA0
 */
void dac_set_data(dac_data_t data);

void dac_get_output_addr(uint16_t * out_ptr);


#endif

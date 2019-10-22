#ifndef DAC_DRIVER_H_
#define DAC_DRIVER_H_

#include "MK64F12.h"

typedef uint16_t dac_data_t;
typedef enum{
	DAC_0 = 0,
	DAC_1 = 1
}dac_enum;

void dac_init();
void dac_set_data(dac_enum index, dac_data_t data);
#endif

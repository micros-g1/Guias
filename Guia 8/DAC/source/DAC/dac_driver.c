#include "dac_driver.h"
#include "MK64F12.h"
#include "MK64F12_features.h"

#define DAC_COUNT FSL_FEATURE_SOC_DAC_COUNT
#define DAC_DATL_DATA0_WIDTH 8


DAC_Type * dac_array[DAC_COUNT];

void dac_init(){
	// Clock gating a todos los DACS.
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
	SIM->SCGC2 |= SIM_SCGC2_DAC0_MASK;
	SIM->SCGC2 |= SIM_SCGC2_DAC1_MASK;

	DAC0->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK | DAC_C0_DACTRGSEL_MASK;
	DAC1->C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK | DAC_C0_DACTRGSEL_MASK;

	dac_array[DAC_0] = DAC0;
	dac_array[DAC_1] = DAC1;


}

void dac_set_data(dac_enum index, dac_data_t data){
	dac_array[index]->DAT[0].DATL = DAC_DATL_DATA0(data);
	dac_array[index]->DAT[0].DATH = DAC_DATH_DATA1(data >> DAC_DATL_COUNT);
}





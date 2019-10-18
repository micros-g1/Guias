#include "ftm_driver.h"
#include "stdbool.h"

static timer_overflow_callback_t overflow_callback;

void ftm_init(){
	// clokc gating
	SIM->SCGC6 |= SIM_SCGC6_FTM0_MASK;

	//Clock source system clock
	FTM0->SC = (FTM0->SC & ~FTM_SC_CLKS_MASK) | FTM_SC_CLKS(0x01);
	// prescaler divide por 4
	FTM0->SC = (FTM0->SC & ~FTM_SC_PS_MASK) | FTM_SC_PS(0b010);

	// CNTIN = 0
	FTM0->CNTIN = 0;

	// Mod = 50-1
	FTM0->MOD = (FTM0->MOD & ~FTM_MOD_MOD_MASK) | FTM_MOD_MOD(50-1);

	//Habiliar interrupcion
	FTM0->SC = (FTM0->SC & ~FTM_SC_TOIE_MASK) | FTM_SC_TOIE(1);
	NVIC_EnableIRQ(FTM0_IRQn);
}

void ftm_set_overflow_handler(timer_overflow_callback_t callback){
	overflow_callback = callback;
}

void FTM0_IRQHandler(void){
	if (FTM0->SC & FTM_SC_TOF_MASK){
		overflow_callback();
		FTM0->SC = (FTM0->SC & ~FTM_SC_TOF_MASK);
	}
}


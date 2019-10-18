#include "MK64F12.h"

//Driver Callback Function Definition
typedef void (*timer_overflow_callback_t)(void);

void ftm_init();
void ftm_set_overflow_handler(timer_overflow_callback_t callback);

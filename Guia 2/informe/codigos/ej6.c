#define PIN_LED_EXT		PORTNUM2PIN(PC,12) // PTB23
#define PIN_LED_RED     PORTNUM2PIN(PB,22) // PTB22
#define PIN_SW_EXT		PORTNUM2PIN(PC,0)
static bool tooglear_baliza();

int past_state;
int curr_state;
bool button_pressed;
bool baliza_on;
void App_Init (void){
    gpioMode(PIN_LED_EXT, OUTPUT);
    gpioMode(PIN_LED_RED, OUTPUT);
    gpioMode(PIN_SW_EXT, INPUT);
    past_state = LOW;			//el led se prende en LOW
    curr_state = past_state;
    gpioWrite (PIN_LED_EXT, past_state);
    gpioWrite (PIN_LED_RED, HIGH);
    button_pressed = false;
    baliza_on = false;
}

void App_Run (void){
	int timer_count = 0;
	while(timer_count < 10){
		curr_state = !gpioRead(PIN_SW_EXT);
		if( curr_state != past_state){
			if(button_pressed)
				button_pressed = !button_pressed;	//boton dejo de presionarse
			else if(tooglear_baliza())			//el boton recien se presio
				break;
			past_state = curr_state;
		}
		delayLoop(1200000uL);
		timer_count++;
	}
	if(baliza_on)
		gpioToggle(PIN_LED_EXT);
}

static bool tooglear_baliza(){
	bool apagada = false;
	baliza_on = !baliza_on;				//se tooglea la baliza
	gpioWrite(PIN_LED_RED, !baliza_on);	//el led sigue a la baliza
	button_pressed = 1;
	if(!baliza_on){
		if(gpioRead(PIN_LED_EXT) == HIGH){
			gpioToggle(PIN_LED_EXT);
			apagada = true;
		}
	}
	return apagada;
}
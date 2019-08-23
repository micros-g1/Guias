#define PIN_LED_GREEN   PORTNUM2PIN(PE,26) //PTE26
#define PIN_SW3         PORTNUM2PIN(PA,4)

int past_state;
int curr_state;
int button_pressed;

void App_Init (void){
    gpioMode(PIN_LED_GREEN, OUTPUT);
    gpioMode(PIN_SW3, INPUT);

    past_state = LOW;			//el led se prende en LOW
    curr_state = past_state;
    gpioWrite (PIN_LED_GREEN, past_state);
    button_pressed = false;
}

void App_Run (void){
	curr_state = !gpioRead(PIN_SW3);
	if( curr_state != past_state){
		if(button_pressed)
			button_pressed = !button_pressed;
		else{
			gpioToggle(PIN_LED_GREEN);
			button_pressed = 1;
		}
		past_state = curr_state;
	}
}
#include "clk.h"
#include "led.h"
#include "button.h"

int main(void)
{
	uint8_t state = 0;
	
	clk_CoreConfig();
	led_Init();
	button_Init();

  while (1){
	  
		state = button_State();

		led_Write(!state);
	}
}

/***********************************************************************************************************************************
* Copyright (C) 2021 TUSUR, FB
* File              : main.c
* Compiler          : gcc
* IDE               : Keil IDE
* Version           : 5.33
* Created File      : 20.01.2021
* Last modified     : 20.01.2021
*
* Support mail      : kirill.grigoryev.1998@gmail.ru
*
* Target MCU        : any
* 
* Description       : LED illumination by pressing a button
***********************************************************************************************************************************/
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

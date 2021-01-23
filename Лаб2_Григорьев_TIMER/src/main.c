#include <MDR32F9Qx_port.h>
#include <MDR32F9Qx_rst_clk.h>
#include <MDR32F9Qx_timer.h>


void port_init()
{
	PORT_InitTypeDef PORT_InitStructure;
	RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTC, ENABLE);
/***********************************************************************************************************************************
* Copyright (C) 2021 TUSUR, FB
* File              : main.c
* Compiler          : gcc
* IDE               : Keil IDE
* Version           : 5.33
* Created File      : 23.01.2021
* Last modified     : 23.01.2021
*
* Support mail      : kirill.grigoryev.1998@gmail.ru
*
* Target MCU        : any
* 
* Description       : Flashing LED using timer libraries
***********************************************************************************************************************************/
	PORT_StructInit(&PORT_InitStructure);
	PORT_InitStructure.PORT_Pin = PORT_Pin_2;
	PORT_InitStructure.PORT_OE= PORT_OE_OUT;
	PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT; 
	PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
	PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
	PORT_Init(MDR_PORTC, &PORT_InitStructure);
}

void Timer2_IRQHandler(){
	static uint8_t count = 0;
	if(TIMER_GetITStatus(MDR_TIMER2,TIMER_STATUS_CNT_ZERO))
	{
		if (count == 0){
    PORT_SetBits(MDR_PORTC, PORT_Pin_2);
    count = 1;
    }
    else{
    PORT_ResetBits(MDR_PORTC, PORT_Pin_2);
    count = 0;
    }
	TIMER_ClearITPendingBit(MDR_TIMER2, TIMER_STATUS_CNT_ZERO);
	}
}

int main()
{
	TIMER_CntInitTypeDef TestTimer;
	port_init();
	RST_CLK_PCLKcmd(RST_CLK_PCLK_TIMER2, ENABLE);
	
	TIMER_CntStructInit(&TestTimer);
	TestTimer.TIMER_Prescaler = 16000;
	TestTimer.TIMER_Period = 500;
	TIMER_BRGInit(MDR_TIMER2, TIMER_HCLKdiv1);
	TIMER_CntInit(MDR_TIMER2, &TestTimer);
	TIMER_ITConfig(MDR_TIMER2, TIMER_STATUS_CNT_ZERO, ENABLE);
	TIMER_Cmd(MDR_TIMER2, ENABLE);
	
	__enable_irq();
	NVIC_ClearPendingIRQ(TIMER2_IRQn);
	NVIC_EnableIRQ(TIMER2_IRQn);
	NVIC_SetPriority(TIMER2_IRQn, 0);

	while(1)
	{
	}
}


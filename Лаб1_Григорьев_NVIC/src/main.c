#include "MDR32Fx.h" // Device header
#include "MDR32F9Qx_port.h" // Keil::Drivers:PORT
#include "system_MDR32F9Qx.h" // Keil::Device:Startup
#include "MDR32F9Qx_rst_clk.h" // Keil::Drivers:RST_CLK


PORT_InitTypeDef PORT_InitStructure;

int main(void)
{
RST_CLK_PCLKcmd(RST_CLK_PCLK_PORTA |
RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC |
RST_CLK_PCLK_PORTE, ENABLE);

SCB->VTOR = 0x08000000;
PORT_InitStructure.PORT_Pin = (PORT_Pin_2);
PORT_InitStructure.PORT_OE = PORT_OE_OUT;
PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
PORT_Init(MDR_PORTC, &PORT_InitStructure);

PORT_InitStructure.PORT_Pin = (PORT_Pin_1);
PORT_InitStructure.PORT_OE = PORT_OE_OUT;
PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
PORT_InitStructure.PORT_MODE = PORT_MODE_ANALOG;
PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
PORT_Init(MDR_PORTA, &PORT_InitStructure);

PORT_InitStructure.PORT_Pin = (PORT_Pin_0);
PORT_InitStructure.PORT_OE = PORT_OE_IN;
PORT_InitStructure.PORT_FUNC = PORT_FUNC_PORT;
PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
PORT_InitStructure.PORT_SPEED = PORT_SPEED_MAXFAST;
PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
PORT_Init(MDR_PORTA, &PORT_InitStructure);

PORT_InitStructure.PORT_Pin = (PORT_Pin_0);
PORT_InitStructure.PORT_OE = PORT_OE_IN;
PORT_InitStructure.PORT_FUNC = PORT_FUNC_ALTER;

PORT_InitStructure.PORT_MODE = PORT_MODE_DIGITAL;
PORT_InitStructure.PORT_SPEED = PORT_SPEED_SLOW;
PORT_InitStructure.PORT_PULL_UP = PORT_PULL_UP_OFF;
PORT_InitStructure.PORT_PULL_DOWN = PORT_PULL_DOWN_ON;
PORT_Init(MDR_PORTA, &PORT_InitStructure);

//NVIC_ClearPendingIRQ(EXT_INT1_IRQn);
__enable_irq();
NVIC_EnableIRQ(EXT_INT1_IRQn);

while(1){PORT_SetBits(MDR_PORTA, PORT_Pin_1);};
}

void EXT_INT1_IRQHandler(void)
{
PORT_SetBits(MDR_PORTC, PORT_Pin_2);
PORT_ResetBits(MDR_PORTC, PORT_Pin_2);
NVIC_ClearPendingIRQ(EXT_INT1_IRQn);
}
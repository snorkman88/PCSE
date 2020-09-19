#include "perifericos.h"
/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

uint8_t entrada[2];


/**
 * @brief	main routine
 * @return	Function should not exit.
 *
 */
void manda_aviso_led_OFF(void);
void manda_aviso_led_ON(void);

int main(void)
{
	//inicializa_fsm();
	inicia_periferico();

	//---configuro LED1---//
	const int LED1[2] = {3, 7}; //El led1 correspond al GPIO3 bit7
	Chip_SCU_PinMuxSet(6, 11, SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN);//LED1
	Chip_GPIO_SetPinDIROutput(LPC_GPIO_PORT, LED1[0], LED1[1]);

	//---configuro boton KEY 2
	const int KEY2[2] = {3, 13}; //El led1 correspond al GPIO3 bit13
	Chip_SCU_PinMuxSet(7, 5,  SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN); //KEY 2
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, KEY2[0], KEY2[1]);

	while (1)
	{
		Chip_UART_Read(LPC_USART0 , entrada, 2);
		switch(entrada[0])
		{
			case 'l':
			{
				//apago el led
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED1[0], LED1[1], false);
				manda_aviso_led_OFF();
				entrada[0] = NULL;
				break;
			}
			case'h':
			{
				//prendo el led
				Chip_GPIO_SetPinState(LPC_GPIO_PORT, LED1[0], LED1[1], true);
				manda_aviso_led_ON();
				entrada[0] = NULL;
				break;
			}
		}
	}
	return 0;
}

void manda_aviso_led_OFF(void)
{
	Chip_UART_SendBlocking( LPC_USART0 , "LED1 OFF" , 10);
}

void manda_aviso_led_ON(void)
{
	Chip_UART_SendBlocking ( LPC_USART0 , "LED1 ON " , 10);
}

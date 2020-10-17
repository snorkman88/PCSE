#include "perifericos.h"
//#include "sapi_uart.h"

const int TEC1[2] = {3, 12}; // Pulsador 1 corresponde a GPIO 3 bit 12
const int KEY2[2] = {3, 13}; //El led1 correspond al GPIO3 bit13

void inicia_periferico(void)
{
	Chip_SetupXtalClocking ();
	SystemCoreClockUpdate ();
	configura_pines();
	inicia_uart0();
	//uartInit(UART0, 115200);
	//inicia_ADC();
}

void configura_pines(void)
{
	/*Configuracion de los pines para pulsador y ADC*/
	Chip_SCU_PinMuxSet(7, 4,  SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN);
	Chip_SCU_PinMuxSet(4, 1,  SCU_MODE_FUNC0 | SCU_MODE_INACT); //
	Chip_SCU_PinMuxSet(7, 5,  SCU_MODE_FUNC0 | SCU_MODE_PULLUP | SCU_MODE_INBUFF_EN); //KEY 2
	Chip_SCU_ADC_Channel_Config(0, 1);//Cconfigura UART0 y canal 1
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, TEC1[0], TEC1[1]); //Configuro el pin como entrada para el pulsador
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, 2, 3);//Configuro el pin como entrada para el potenciometro
	Chip_GPIO_SetPinDIRInput(LPC_GPIO_PORT, KEY2[0], KEY2[1]);
}

void inicia_uart0(void)
{
	/*Configuracion e inicializacion de la UART0*/
	Chip_SCU_PinMuxSet (2 , 0 , SCU_MODE_PULLDOWN | SCU_MODE_FUNC1 );
	Chip_SCU_PinMuxSet (2 , 1 , SCU_MODE_INACT | SCU_MODE_INBUFF_EN | SCU_MODE_ZIF_DIS | SCU_MODE_FUNC1 );
	Chip_UART_Init ( LPC_USART0 );
	Chip_UART_ConfigData ( LPC_USART0 , UART_LCR_WLEN8 | UART_LCR_SBS_1BIT | UART_LCR_PARITY_DIS );
	Chip_UART_SetBaud ( LPC_USART0 , 115200);
	Chip_UART_TXEnable ( LPC_USART0 );
	//Chip_UART_SendBlocking ( LPC_USART0 , "UART CONFIG OK!" , strlen("UART CONFIG OK!"));
}

bool lee_boton1(void)
{
	return !Chip_GPIO_GetPinState(LPC_GPIO_PORT, TEC1[0], TEC1[1]);
}

bool lee_boton2(void)
{
	return !Chip_GPIO_GetPinState(LPC_GPIO_PORT, KEY2[0], KEY2[1]);
}

void delay_ms (uint16_t ms)
{
	uint16_t delay;
	volatile uint32_t i;
	for (delay = ms; delay >0 ; delay--)
	{
		for (i=3500; i >0;i--){};
	}
}

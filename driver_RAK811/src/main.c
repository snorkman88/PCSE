#include <string.h>
#include "perifericos.h"
#include "rak811.h"

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
const uint32_t ExtRateIn = 0;
const uint32_t OscRateIn = 12000000;

uint8_t join_mode = 0; //Join with OTAA
uint8_t class = 0; //Class A device


char dev_eui[] = "00AC64D4A86D77C7";
char app_eui[] = "70B3D57ED001A7C6";
char app_key[] = "95486585013718248A276AF10B4BE4E5";
//get_config = "at+get_config=lora:status\r\n";


int main(void)
{
	inicia_periferico();

	//config_lora_join_mode(join_mode);
	//config_lorawan_class(class);
	//config_lora_region("EU868");
	//config_dev_eui(dev_eui);
	//config_app_eui(app_eui);
	//config_app_key(app_key);
	//config_device_sleep("0");
	lora_join();

	while (1)
	{
		if (lee_boton1())
		{
			lora_send("0c99aaa0cbbaa204");//mando dato de prueba a TTN
			delay_ms(2000);
		}
		if (lee_boton2())
		{
			lora_send("0000000000000000");
			delay_ms(2000);
		}
	}
	return 0;
}

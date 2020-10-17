
/*--------------------RAK 811 LIBRARY FOR LPCOPEN-------------------*/

#include "perifericos.h"//Replace this file with the one proper of your board
#include "lpc_types.h"//Import variables types proper of your SDK

#define CLASS_A_DEVICE_MESSAGE "at+set_config=lora:class:0\r\n"
#define CLASS_B_DEVICE_MESSAGE "at+set_config=lora:class:1\r\n"
#define CLASS_C_DEVICE_MESSAGE "at+set_config=lora:class:2\r\n"

#define LORAWAN_WORK_MODE "at+set_config=lora:work_mode:0\r\n"
#define LORAP2P_WORK_MODE "at+set_config=lora:work_mode:1\r\n"

#define LORAWAN_OTAA_JOIN_MODE "at+set_config=lora:join_mode:0\r\n"
#define LORAWAN_ABP_JOIN_MODE "at+set_config=lora:join_mode:1\r\n"

#define LORAWAN_JOIN_COMMAND "at+join\r\n"

void config_lora_region(char lora_region[]);
void config_lorawan_class(uint8_t class);
void config_lora_work_mode(uint8_t work_mode);
void config_lora_join_mode(uint8_t join_mode);
void config_dev_eui(char dev_eui[]);
void config_app_eui(char app_eui[]);
void config_app_key(char app_key[]);
void config_device_sleep(char sleep_command[]);
void lora_join(void);
void lora_send(char payload[40]);
void lora_send_P2P(char payload[40]);


#include "chip.h" //Replace with proper libreary for your board
#include <string.h>

void inicia_periferico(void);

void configura_pines(void);

void inicia_uart0(void);

bool lee_boton1(void);
bool lee_boton2(void);

void delay_ms (uint16_t ms);

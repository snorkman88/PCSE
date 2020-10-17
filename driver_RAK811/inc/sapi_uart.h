/* Copyright 2015, Eric Pernia.
 * All rights reserved.
 *
 * This file is part sAPI library for microcontrollers.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

/* Date: 2016-02-26 */

#ifndef _SAPI_UART_H_
#define _SAPI_UART_H_

/*==================[inclusions]=============================================*/

//#include "sapi_delay.h"
//#include "sapi_datatypes.h"
#include "lpc_types.h"
//#include "sapi_peripheral_map.h"

/*==================[c++]====================================================*/
#ifdef __cplusplus
extern "C" {
#endif

/*==================[macros]=================================================*/

#define uartConfig uartInit

/*==================[typedef]================================================*/
typedef void (*callBackFuncPtr_t)(void *);

typedef uint8_t bool_t;

typedef struct {
   int8_t port;
   int8_t pin;
} pinInitLpc4337_t;

typedef struct {
   uint8_t lpcScuPort;
   uint8_t lpcScuPin;
   uint8_t lpcScuFunc;
} lpc4337ScuPin_t;

typedef enum {
	   UART0 = 0, // Hardware UART0 via GPIO1(TX), GPIO2(RX) pins on header P0
	   UART_485  = 1, // Hardware UART0 via RS_485 A, B and GND Borns
		// Hardware UART1 not routed
	   UART_USB  = 3, // Hardware UART2 via USB DEBUG port
	   UART_ENET = 4, // Hardware UART2 via ENET_RXD0(TX), ENET_CRS_DV(RX) pins on header P0
	   UART_232  = 5, // Hardware UART3 via 232_RX and 232_tx pins on header P1
   UART_MAXNUM,
} uartMap_t;


typedef enum{
   UART_PARITY_NONE = 0,
   UART_PARITY_ODD = 0,
   UART_PARITY_EVEN,
} uartParity_t;

typedef enum{
   UART_STOP_BITS_1 = 1,
   UART_STOP_BITS_2 = 2,
   UART_STOP_BITS_1_5 = 3,
} uartStopBits_t;

typedef enum{
   UART_DATA_BITS_5 = 5,
   UART_DATA_BITS_6 = 6,
   UART_DATA_BITS_7 = 7,
   UART_DATA_BITS_8 = 8,
   UART_DATA_BITS_9 = 9,
} uartDataBits_t;


typedef enum{
   UART_RECEIVE,
   UART_TRANSMITER_FREE
} uartEvents_t;

/*==================[external functions declaration]=========================*/


// Return TRUE if have unread data in RX FIFO
bool_t uartRxReady( uartMap_t uart );
// Return TRUE if have space in TX FIFO
bool_t uartTxReady( uartMap_t uart );
// Read from RX FIFO
uint8_t uartRxRead( uartMap_t uart );
// Write in TX FIFO
void uartTxWrite( uartMap_t uart, uint8_t value );

//-------------------------------------------------------------
// UART Initialization
void uartInit( uartMap_t uart, uint32_t baudRate );

void uartInit2( uartMap_t uart, uint32_t baudRate,
                uint8_t dataBits, uint8_t parity, uint8_t stopBits );

// Read 1 byte from RX FIFO, check first if exist aviable data
bool_t uartReadByte( uartMap_t uart, uint8_t* receivedByte );
// Blocking, Write 1 byte to TX FIFO
void uartWriteByte( uartMap_t uart, const uint8_t value );

// Blocking, Send a string
void uartWriteString( uartMap_t uart, const char* str );

// Blocking, Send a Byte Array
void uartWriteByteArray( uartMap_t uart, const uint8_t* byteArray, uint32_t byteArrayLen );

//#ifdef SAPI_USE_INTERRUPTS

//-------------------------------------------------------------
// Interrupts
//-------------------------------------------------------------

// UART Global Interrupt Enable/Disable
void uartInterrupt( uartMap_t uart, bool_t enable );

// UART Interrupt event Enable and set a callback
void uartCallbackSet( uartMap_t uart, uartEvents_t event,
                      callBackFuncPtr_t callbackFunc, void* callbackParam );

// UART Interrupt event Disable
void uartCallbackClr( uartMap_t uart, uartEvents_t event );

// UART Set Pending Interrupt. Useful to force first character in tx transmission
void uartSetPendingInterrupt(uartMap_t uart);

// UART Clear Pending Interrupt.
void uartClearPendingInterrupt(uartMap_t uart);

/*==================[ISR external functions declaration]======================*/

/* 0x28 0x000000A0 - Handler for ISR UART0 (IRQ 24) */
void UART0_IRQHandler(void);
/* 0x2a 0x000000A8 - Handler for ISR UART2 (IRQ 26) */
void UART2_IRQHandler(void);
/* 0x2b 0x000000AC - Handler for ISR UART3 (IRQ 27) */
void UART3_IRQHandler(void);

//#endif /* SAPI_USE_INTERRUPTS */

/*==================[c++]====================================================*/
#ifdef __cplusplus
}
#endif

/*==================[end of file]============================================*/
#endif /* _SAPI_UART_H_ */

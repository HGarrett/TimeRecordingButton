/* 
 * File:   uart.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on November 3, 2023, 12:12 AM
 */

#ifndef UART_H
#define	UART_H

#ifdef	__cplusplus
extern "C" {
#endif

#define BAUD_RATE 600
    
// UART Commands
#define UART_DOCKED          0x64 // d
#define UART_SUCCESS         0x73 // s
#define UART_DONE            0x78 // x
#define UART_TRANSFER_START  0x74 // t
#define UART_TRANSFER_END    0x65 // e
#define UART_CALIBRATE       0x63 // c
#define UART_WRITE_TEST_TIME 0x77 // w

void    Uart_Init(void);
void    Uart_TxEnable(void);
void    Uart_TxDisable(void);
uint8_t Uart_DataReady(void);
void    Uart_Tx(uint8_t data);
uint8_t Uart_Rx(void);
void    Uart_Docked(void);
void    Uart_Undocked(void);
void    Uart_TransferEeprom(void);
void    Uart_ResetAndCalibrate(void);
void    Uart_WriteTestTimestamp(void);

#ifdef	__cplusplus
}
#endif

#endif	/* UART_H */


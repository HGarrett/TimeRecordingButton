 /* 
 * File:   uart.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on November 3, 2023, 12:12 AM
 */

#include <xc.h>
#include <stdint.h>
#include <pic16f18114.h>
#include "uart.h"
#include "eeprom_access.h"
#include "timestamp.h"
#include "config_PIC16F18114.h"

void Uart_Init(void) {
    RX1PPS = 0x02; // Set RX pin to RA2
    RA4PPS = 0x13; // Set RA4 PPS to TX1 for UART Async output

    // with the low power internal OSC, we have to use high speed, 16-bit mode
    TX1STAbits.BRGH = 1;
    BAUD1CONbits.BRG16 = 1;
    SP1BRG = ( _XTAL_FREQ / (4 * BAUD_RATE) ) - 1;

    // UART registers to set up ASYNC mode
    TX1STAbits.SYNC = 0; // Async mode
    RC1STAbits.CREN = 1; // Continuous Receive Enable
    RC1STAbits.SPEN = 1; // Serial Port Enable
}

void Uart_TxEnable(void) {
    TRISAbits.TRISA4 = 0; // configure RA4 as an input
    TX1STAbits.TXEN  = 1; // Transmit enable
}

void Uart_TxDisable(void) {
    while (TX1STAbits.TRMT == 0); // make sure we wait until done transmitting
    
    TX1STAbits.TXEN  = 0; // Transmit disable
    TRISAbits.TRISA4 = 1; // reset RA4 to output for button
}

uint8_t Uart_DataReady(void) {
    return (uint8_t)RC1IF;
}
 
uint8_t Uart_Rx(void) {
    // check for overrun error
    if(RC1STAbits.OERR) {
        // if error found, must clear overrun error bit to receive again
        // clear by disabling and re-enabling continuous receive
        RC1STAbits.CREN = 0;
        RC1STAbits.CREN = 1;
    }
    
    // return the 8-bit value in the receive register
    return RC1REG;
}
 
void Uart_Tx(uint8_t data) {
    while (TX1STAbits.TRMT == 0); // wait for transmit shift register to be empty
    TX1REG = data; // write data to transmit register
}

void Uart_Docked(void) {
    Uart_TxEnable();
    Uart_Tx(UART_SUCCESS);
}

void Uart_Undocked(void) {
    Uart_TxDisable();
}

void Uart_TransferEeprom(void) {
    uint8_t eeprom_address;
    
    for(eeprom_address = EEPROM_START_ADDRESS_NVMADRL;
            eeprom_address < EEPROM_SIZE; eeprom_address++) {
        Uart_Tx(Eeprom_ReadByte(eeprom_address));
    }
    
    Uart_Tx(UART_SUCCESS);
}

void Uart_ResetAndCalibrate(void) {
    uint8_t tmr_overflow;
    uint8_t tmr_high;
    uint8_t tmr_low;
    
    // erase eeprom
    Eeprom_EraseAll();
    
    // save new timestamp
    tmr_overflow = TIMER_INTERRUPT_FLAG;
    tmr_low      = TMR0L;
    tmr_high     = TMR0H;
    
    // transmit the new timestamp to dockui for calibration
    Uart_Tx(tmr_high);
    Uart_Tx(tmr_low);
    
    Timestamp_ResetPointerAddress();
    Timestamp_ResetTimerOverflowCounter();
    Timestamp_Save(tmr_low, tmr_high, tmr_overflow);
    
    Uart_Tx(UART_SUCCESS);
}

void Uart_WriteTestTimestamp(void) {
    uint8_t tmr_overflow;
    uint8_t tmr_high;
    uint8_t tmr_low;
    
    // save new timestamp
    tmr_overflow = TIMER_INTERRUPT_FLAG;
    tmr_low      = TMR0L;
    tmr_high     = TMR0H;

    // transmit the new timestamp to dockui for calibration
    Uart_Tx(tmr_high);
    Uart_Tx(tmr_low);
    
    Timestamp_Save(tmr_low, tmr_high, tmr_overflow);
    
    Uart_Tx(UART_SUCCESS);
}
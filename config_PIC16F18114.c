/*
 * File:   config_PIC16F18114.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 9:12 AM
 */

#include <xc.h>
#include "config_PIC16F18114.h"

void Config_RuntimeConfig(void) {
    // configuring PORTA
    PORTA  = 0x00; // Clear PORTA
    LATA   = 0x00; // Clear Data Latch
    ANSELA = 0x00; // Set all pins to digital
    WPUA   = 0x00; // Weak pull up disabled on all pins
    
    TRISA  = 0x00; // Make sure everything is an output then...
    TRISAbits.TRISA2 = 1; // RA2 is RX for UART
    TRISAbits.TRISA4 = 1; // Default RA4 setting is input for button
                          // but it is also our UART TX, (see Uart_TxEnable)
                          // so will change default setting during operation

    // Enable interrupts
    INTCONbits.GIE  = 1; // Global Interrupt Enable
    INTCONbits.PEIE = 1; // Peripheral Interrupt Enable

//    // Disable modules for lowest power possible
//    // All modules are on by default
//    // PMD0 leave all modules enabled
//    PMD1 = 0xFF; // Disable PWM2, CCP2, CCP1, TMR4, TMR2, TMR3, TMR1
//    PMD2 = 0xFF; // Disable CLC3, CLC2, CLC1, CWG1, NCo1, PWM2
//    PMD3 = 0xFD; // Enable UART1 (bit 1); Disable CM2, CM1, FVR, MSSP2, MSSP1, UART2, CLC4
//    PMD4 = 0xFF; // Disable ZCD, DAC2, DAC1, ADC
}
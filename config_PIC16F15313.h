/* 
 * File:   config.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 9:02 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

/***************************************
 * Chip PIC16F15313 configuration bytes
 ***************************************/
// CONFIG1
#pragma config FEXTOSC  = OFF   // External Oscillator mode selection bits (LP optimized for 32.768 kHz; PFM set to low power)
#pragma config RSTOSC   = LFINT // Power-up default value for COSC bits (LFINTOSC)
#pragma config CLKOUTEN = OFF   // Clock Out Enable bit (CLKOUT function is disabled; i/o or oscillator function on OSC2)
#pragma config CSWEN    = ON    // Clock Switch Enable bit (Writing to NOSC and NDIV is allowed)
#pragma config FCMEN    = OFF   // Fail-Safe Clock Monitor Enable bit (FSCM timer disabled)
// CONFIG2
#pragma config MCLRE   = ON  // Master Clear Enable bit (MCLR pin is Master Clear function)
#pragma config PWRTE   = ON  // Power-up Timer Enable bit (PWRT enabled)
#pragma config LPBOREN = OFF // Low-Power BOR enable bit (ULPBOR disabled)
#pragma config BOREN   = OFF // Brown-out reset enable bits (Brown-out reset disabled)
#pragma config BORV    = LO  // Brown-out Reset Voltage Selection (Brown-out Reset Voltage (VBOR) set to 1.9V on LF, and 2.45V on F Devices)
#pragma config ZCD     = OFF // Zero-cross detect disable (Zero-cross detect circuit is disabled at POR.)
#pragma config PPS1WAY = OFF // Peripheral Pin Select one-way control (The PPSLOCK bit can be set and cleared repeatedly by software)
#pragma config STVREN  = ON  // Stack Overflow/Underflow Reset Enable bit (Stack Overflow or Underflow will cause a reset)
// CONFIG3
#pragma config WDTCPS = WDTCPS_31 // WDT Period Select bits (Divider ratio 1:65536; software control of WDTPS)
#pragma config WDTE   = OFF       // WDT operating mode (WDT Disabled, SWDTEN is ignored)
#pragma config WDTCWS = WDTCWS_7  // WDT Window Select bits (window always open (100%); software control; keyed access not required)
#pragma config WDTCCS = LFINTOSC  // WDT input clock selector (WDT reference clock is the 31.0kHz LFINTOSC output)
// CONFIG4
#pragma config BBSIZE = BB512 // Boot Block Size Selection bits (512 words boot block size)
#pragma config BBEN   = OFF   // Boot Block Enable bit (Boot Block disabled)
#pragma config SAFEN  = ON    // Storage Area Flash Enable bit (SAF enabled)
#pragma config WRTAPP = OFF   // Application Block Write Protection bit (Application Block not write protected)
#pragma config WRTB   = OFF   // Boot Block Write Protection bit (Boot Block not write protected)
#pragma config WRTC   = OFF   // Configuration Register Write Protection bit (Configuration Register not write protected)
#pragma config WRTSAF = OFF   // Storage Area Flash Write Protection bit (SAF not write protected)
#pragma config LVP    = OFF   // Low Voltage Programming Enable bit (High Voltage on MCLR/Vpp must be used for programming)
// CONFIG5
#pragma config CP = OFF // UserNVM Program memory code protection bit (UserNVM code protection disabled)

/******************
 * Timer frequency
 ******************/
#define _XTAL_FREQ  31000 // LFINTOSC mode, 31kHz, this is used by the __delay_ms(xx) and __delay_us(xx) functions

/*******************************
 * LED and Button Configuration
 *******************************/
#define LED_PIN     LATAbits.LATA5
#define LED_ON      1
#define LED_OFF     0

#define BUTTON_DOWN PORTAbits.RA4
#define BUTTON_UP   !(PORTAbits.RA4)

#define MS_BUTTON_HOLD_INTERVAL 1000000 // how long user needs to hold button to save timestamp
#define MS_DELAY_INTERVAL       10000  // delay in ms used between loops
#define LOOP_COUNT              (MS_BUTTON_HOLD_INTERVAL/MS_DELAY_INTERVAL)

#define MS_LED_FLASH_INTERVAL   60000  // delay in ms used to flash the LED on successful timestamp save

/***********************
 * Function Definitions
 ***********************/
void Config_RuntimeConfig(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */


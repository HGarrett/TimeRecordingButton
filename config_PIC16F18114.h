/* 
 * File:   config_PIC16F18114.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 9:02 AM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <xc.h>

/***************************************
 * Chip PIC16F18114 configuration bytes
 ***************************************/
// CONFIG1
#pragma config FCMEN    = 0        // Fail-Safe Clock Monitor Enable (FSCM is disabled)
#pragma config VDDAR    = 0        // VDD Analog Range Calibration Selection (Internal analog systems are calibrated for operation between VDD = 1.8V - 3.6V)
#pragma config CSWEN    = 1        // Clock Switch Enable (Writing to NOSC and NDIV is allowed)
#pragma config CLKOUTEN = 1        // Clock Out Enable (CLKOUT function is disabled; I/O function on CLKOUT pin)
#pragma config RSTOSC   = 0x05     // Power-up Default Value for the NOSC/COSC bits (LFINTOSC)
#pragma config FEXTOSC  = 0x04     // External Oscillator Mode Selection (Oscillator not enabled)

// CONFIG2
#pragma config DEBUG     = 1    // Debugger Enable (Background debugger disabled)
#pragma config STVREN    = 1    // Stack Overflow/Underflow Reset Enable (Stack Overflow or Underflow will cause a reset)
#pragma config PPS1WAY   = 0    // Peripheral Pin Select LOCKED One-Way Set Enable (The PPSLOCKED bit can be set and cleared as needed (unlocking sequence is required))
#pragma config ZCD       = 1    // Zero-Cross Detect Disable (ZCD disabled, ZCD can be enabled by setting the ZCDSEN bit of ZCDCON)
#pragma config BORV      = 1    // Brown-out Reset Voltage Selection (VBOR set to 1.9V)
#pragma config DACAUTOEN = 1    // DAC Buffer Automatic Range Select Enable (DAC Buffer reference range is determined by the REFRNG bit of DACxCON)
#pragma config BOREN     = 0    // Brown-out Reset Enable (BOR disabled)
#pragma config LPBOREN   = 1    // Low-Power Brown-out Reset Enable (Low-Power BOR disabled)
#pragma config PWRTS     = 0x02 // Power-Up Timer (PWRT) Selection (PWRT is set at 64 ms)
#pragma config MCLRE     = 1    // Master Clear (MCLR) Enable (MCLR pin is Master Clear function)

// CONFIG3
#pragma config WDTCCS = 0         // WDT Input Clock Selector (WDT reference clock is the 31.0kHz LFINTOSC output)
#pragma config WDTCWS = WDTCWS_7  // WDT Window Select (window always open (100%); software control; keyed access not required)
#pragma config WDTE   = 0         // WDT Operating Mode (WDT disabled, the SEN bit in WDTCON0 is ignored)
#pragma config WDTCPS = WDTCPS_31 // WDT Period Select (Divider ratio 1:65536; software control of WDTPS)

// CONFIG4
#pragma config LVP    = 0 // Low-Voltage Programming Enable (High voltage (HV) on MCLR/VPP must be used for programming)
#pragma config WRTSAF = 1 // Storage Area Flash (SAF) Write Protection (SAF is not write-protected)
#pragma config WRTD   = 1 // Data EEPROM Write Protection (Data EEPROM is not write-protected)
#pragma config WRTC   = 1 // Configuration Registers Write Protection (Configuration registers are not write-protected)
#pragma config WRTB   = 1 // Boot Block Write Protection (Boot Block is not write-protected)
#pragma config WRTAPP = 1 // Application Block Write Protection (Application Block is not write-protected)
#pragma config SAFEN  = 1 // Storage Area Flash (SAF) Enable (SAF is disabled)
#pragma config BBEN   = 1 // Boot Block Enable (Boot Block is disabled)
#pragma config BBSIZE = 0 // Boot Block Size Selection (End Address of Boot Block 0x3FFF, Boot Block Size Undefined)

// CONFIG5
#pragma config CPD = 1 // Data EEPROM Code Protection (Data EEPROM code protection is disable)
#pragma config CP  = 1 // User Program Flash Memory (PFM) Code Protection (User PFM code protection is disabled)

/******************
 * Timer frequency
 ******************/
#define _XTAL_FREQ 31000 // LFINTOSC mode, 31kHz, this is used by the __delay_ms(xx) and __delay_us(xx) functions

/*******************************
 * LED and Button Configuration
 *******************************/
#define LED_PIN     LATAbits.LATA5
#define LED_ON      1
#define LED_OFF     0

#define BUTTON_DOWN PORTAbits.RA4
#define BUTTON_UP   !(PORTAbits.RA4)

#define MS_DELAY_INTERVAL       100  // delay in ms used between loops, 100 msec = 0.1 sec
    
#define MS_BUTTON_HOLD_INTERVAL 3000 // how long user needs to hold button to save timestamp, 3000 msec = 3 sec
#define BUTTON_LOOP_COUNT       (MS_BUTTON_HOLD_INTERVAL/MS_DELAY_INTERVAL)

#define MS_DOCK_HOLD_INTERVAL   1000 // how long between intervals that dockui needs to reconfirm dock status
#define DOCKED_LOOP_COUNT       (MS_DOCK_HOLD_INTERVAL/MS_DELAY_INTERVAL)

#define MS_LED_FLASH_INTERVAL   250  // delay in ms used to flash the LED on successful timestamp save

/***********************
 * Function Definitions
 ***********************/
void Config_RuntimeConfig(void);
    
#ifdef	__cplusplus
}
#endif

#endif	/* CONFIG_H */


/**
 * Generated Pins header File
 * 
 * @file pins.h
 * 
 * @defgroup  pinsdriver Pins Driver
 * 
 * @brief This is generated driver header for pins. 
 *        This header file provides APIs for all pins selected in the GUI.
 *
 * @version Driver Version  3.0.0
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
*/

#ifndef PINS_H
#define PINS_H

#include <xc.h>

#ifdef VSCODE_PIC
#include "pic16f18124.h"
#endif

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set IO_RA2 aliases
#define EEPROM_WP_TRIS                 TRISAbits.TRISA2
#define EEPROM_WP_LAT                  LATAbits.LATA2
#define EEPROM_WP_PORT                 PORTAbits.RA2
#define EEPROM_WP_WPU                  WPUAbits.WPUA2
#define EEPROM_WP_OD                   ODCONAbits.ODCA2
#define EEPROM_WP_ANS                  ANSELAbits.ANSA2
#define EEPROM_WP_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define EEPROM_WP_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define EEPROM_WP_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define EEPROM_WP_GetValue()           PORTAbits.RA2
#define EEPROM_WP_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define EEPROM_WP_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define EEPROM_WP_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define EEPROM_WP_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define EEPROM_WP_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define EEPROM_WP_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define EEPROM_WP_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define EEPROM_WP_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)
// get/set IO_RA4 aliases
#define RN4871_LowBat_TRIS                 TRISAbits.TRISA4
#define RN4871_LowBat_LAT                  LATAbits.LATA4
#define RN4871_LowBat_PORT                 PORTAbits.RA4
#define RN4871_LowBat_WPU                  WPUAbits.WPUA4
#define RN4871_LowBat_OD                   ODCONAbits.ODCA4
#define RN4871_LowBat_ANS                  ANSELAbits.ANSA4
#define RN4871_LowBat_SetHigh()            do { LATAbits.LATA4 = 1; } while(0)
#define RN4871_LowBat_SetLow()             do { LATAbits.LATA4 = 0; } while(0)
#define RN4871_LowBat_Toggle()             do { LATAbits.LATA4 = ~LATAbits.LATA4; } while(0)
#define RN4871_LowBat_GetValue()           PORTAbits.RA4
#define RN4871_LowBat_SetDigitalInput()    do { TRISAbits.TRISA4 = 1; } while(0)
#define RN4871_LowBat_SetDigitalOutput()   do { TRISAbits.TRISA4 = 0; } while(0)
#define RN4871_LowBat_SetPullup()          do { WPUAbits.WPUA4 = 1; } while(0)
#define RN4871_LowBat_ResetPullup()        do { WPUAbits.WPUA4 = 0; } while(0)
#define RN4871_LowBat_SetPushPull()        do { ODCONAbits.ODCA4 = 0; } while(0)
#define RN4871_LowBat_SetOpenDrain()       do { ODCONAbits.ODCA4 = 1; } while(0)
#define RN4871_LowBat_SetAnalogMode()      do { ANSELAbits.ANSA4 = 1; } while(0)
#define RN4871_LowBat_SetDigitalMode()     do { ANSELAbits.ANSA4 = 0; } while(0)
// get/set IO_RA5 aliases
#define RN4871_RX_Ind_TRIS                 TRISAbits.TRISA5
#define RN4871_RX_Ind_LAT                  LATAbits.LATA5
#define RN4871_RX_Ind_PORT                 PORTAbits.RA5
#define RN4871_RX_Ind_WPU                  WPUAbits.WPUA5
#define RN4871_RX_Ind_OD                   ODCONAbits.ODCA5
#define RN4871_RX_Ind_ANS                  ANSELAbits.ANSA5
#define RN4871_RX_Ind_SetHigh()            do { LATAbits.LATA5 = 1; } while(0)
#define RN4871_RX_Ind_SetLow()             do { LATAbits.LATA5 = 0; } while(0)
#define RN4871_RX_Ind_Toggle()             do { LATAbits.LATA5 = ~LATAbits.LATA5; } while(0)
#define RN4871_RX_Ind_GetValue()           PORTAbits.RA5
#define RN4871_RX_Ind_SetDigitalInput()    do { TRISAbits.TRISA5 = 1; } while(0)
#define RN4871_RX_Ind_SetDigitalOutput()   do { TRISAbits.TRISA5 = 0; } while(0)
#define RN4871_RX_Ind_SetPullup()          do { WPUAbits.WPUA5 = 1; } while(0)
#define RN4871_RX_Ind_ResetPullup()        do { WPUAbits.WPUA5 = 0; } while(0)
#define RN4871_RX_Ind_SetPushPull()        do { ODCONAbits.ODCA5 = 0; } while(0)
#define RN4871_RX_Ind_SetOpenDrain()       do { ODCONAbits.ODCA5 = 1; } while(0)
#define RN4871_RX_Ind_SetAnalogMode()      do { ANSELAbits.ANSA5 = 1; } while(0)
#define RN4871_RX_Ind_SetDigitalMode()     do { ANSELAbits.ANSA5 = 0; } while(0)
// get/set IO_RC0 aliases
#define EEPROM_RTCC_CLK_TRIS                 TRISCbits.TRISC0
#define EEPROM_RTCC_CLK_LAT                  LATCbits.LATC0
#define EEPROM_RTCC_CLK_PORT                 PORTCbits.RC0
#define EEPROM_RTCC_CLK_WPU                  WPUCbits.WPUC0
#define EEPROM_RTCC_CLK_OD                   ODCONCbits.ODCC0
#define EEPROM_RTCC_CLK_ANS                  ANSELCbits.ANSC0
#define EEPROM_RTCC_CLK_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define EEPROM_RTCC_CLK_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define EEPROM_RTCC_CLK_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define EEPROM_RTCC_CLK_GetValue()           PORTCbits.RC0
#define EEPROM_RTCC_CLK_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define EEPROM_RTCC_CLK_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define EEPROM_RTCC_CLK_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define EEPROM_RTCC_CLK_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define EEPROM_RTCC_CLK_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define EEPROM_RTCC_CLK_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define EEPROM_RTCC_CLK_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define EEPROM_RTCC_CLK_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)
// get/set IO_RC1 aliases
#define EEPROM_RTCC_DAT_TRIS                 TRISCbits.TRISC1
#define EEPROM_RTCC_DAT_LAT                  LATCbits.LATC1
#define EEPROM_RTCC_DAT_PORT                 PORTCbits.RC1
#define EEPROM_RTCC_DAT_WPU                  WPUCbits.WPUC1
#define EEPROM_RTCC_DAT_OD                   ODCONCbits.ODCC1
#define EEPROM_RTCC_DAT_ANS                  ANSELCbits.ANSC1
#define EEPROM_RTCC_DAT_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define EEPROM_RTCC_DAT_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define EEPROM_RTCC_DAT_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define EEPROM_RTCC_DAT_GetValue()           PORTCbits.RC1
#define EEPROM_RTCC_DAT_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define EEPROM_RTCC_DAT_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define EEPROM_RTCC_DAT_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define EEPROM_RTCC_DAT_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define EEPROM_RTCC_DAT_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define EEPROM_RTCC_DAT_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define EEPROM_RTCC_DAT_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define EEPROM_RTCC_DAT_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)
// get/set IO_RC2 aliases
#define Switch_LED_TRIS                 TRISCbits.TRISC2
#define Switch_LED_LAT                  LATCbits.LATC2
#define Switch_LED_PORT                 PORTCbits.RC2
#define Switch_LED_WPU                  WPUCbits.WPUC2
#define Switch_LED_OD                   ODCONCbits.ODCC2
#define Switch_LED_ANS                  ANSELCbits.ANSC2
#define Switch_LED_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define Switch_LED_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define Switch_LED_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define Switch_LED_GetValue()           PORTCbits.RC2
#define Switch_LED_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define Switch_LED_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define Switch_LED_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define Switch_LED_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define Switch_LED_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define Switch_LED_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define Switch_LED_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define Switch_LED_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)
// get/set IO_RC3 aliases
#define Switch_TRIS                 TRISCbits.TRISC3
#define Switch_LAT                  LATCbits.LATC3
#define Switch_PORT                 PORTCbits.RC3
#define Switch_WPU                  WPUCbits.WPUC3
#define Switch_OD                   ODCONCbits.ODCC3
#define Switch_ANS                  ANSELCbits.ANSC3
#define Switch_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define Switch_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define Switch_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define Switch_GetValue()           PORTCbits.RC3
#define Switch_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define Switch_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define Switch_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define Switch_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define Switch_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define Switch_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define Switch_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define Switch_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)
// get/set IO_RC4 aliases
#define RN4871_TX_TRIS                 TRISCbits.TRISC4
#define RN4871_TX_LAT                  LATCbits.LATC4
#define RN4871_TX_PORT                 PORTCbits.RC4
#define RN4871_TX_WPU                  WPUCbits.WPUC4
#define RN4871_TX_OD                   ODCONCbits.ODCC4
#define RN4871_TX_ANS                  ANSELCbits.ANSC4
#define RN4871_TX_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RN4871_TX_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RN4871_TX_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RN4871_TX_GetValue()           PORTCbits.RC4
#define RN4871_TX_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RN4871_TX_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RN4871_TX_SetPullup()          do { WPUCbits.WPUC4 = 1; } while(0)
#define RN4871_TX_ResetPullup()        do { WPUCbits.WPUC4 = 0; } while(0)
#define RN4871_TX_SetPushPull()        do { ODCONCbits.ODCC4 = 0; } while(0)
#define RN4871_TX_SetOpenDrain()       do { ODCONCbits.ODCC4 = 1; } while(0)
#define RN4871_TX_SetAnalogMode()      do { ANSELCbits.ANSC4 = 1; } while(0)
#define RN4871_TX_SetDigitalMode()     do { ANSELCbits.ANSC4 = 0; } while(0)
// get/set IO_RC5 aliases
#define RN4871_RX_TRIS                 TRISCbits.TRISC5
#define RN4871_RX_LAT                  LATCbits.LATC5
#define RN4871_RX_PORT                 PORTCbits.RC5
#define RN4871_RX_WPU                  WPUCbits.WPUC5
#define RN4871_RX_OD                   ODCONCbits.ODCC5
#define RN4871_RX_ANS                  ANSELCbits.ANSC5
#define RN4871_RX_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RN4871_RX_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RN4871_RX_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RN4871_RX_GetValue()           PORTCbits.RC5
#define RN4871_RX_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RN4871_RX_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RN4871_RX_SetPullup()          do { WPUCbits.WPUC5 = 1; } while(0)
#define RN4871_RX_ResetPullup()        do { WPUCbits.WPUC5 = 0; } while(0)
#define RN4871_RX_SetPushPull()        do { ODCONCbits.ODCC5 = 0; } while(0)
#define RN4871_RX_SetOpenDrain()       do { ODCONCbits.ODCC5 = 1; } while(0)
#define RN4871_RX_SetAnalogMode()      do { ANSELCbits.ANSC5 = 1; } while(0)
#define RN4871_RX_SetDigitalMode()     do { ANSELCbits.ANSC5 = 0; } while(0)
/**
 * @ingroup  pinsdriver
 * @brief GPIO and peripheral I/O initialization
 * @param none
 * @return none
 */
void PIN_MANAGER_Initialize (void);

/**
 * @ingroup  pinsdriver
 * @brief Interrupt on Change Handling routine
 * @param none
 * @return none
 */
void PIN_MANAGER_IOC(void);


#endif // PINS_H
/**
 End of File
*/
/* 
 * File:   constants.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on November 28, 2023, 10:55 AM
 */

#ifndef CONSTANTS_H
#define	CONSTANTS_H

#ifdef	__cplusplus
extern "C" {
#endif

/*******************************
 * LED and Button Defines
 *******************************/
#define LED_ON      1
#define LED_OFF     0

#define MS_DELAY_INTERVAL       100  // delay in ms used between loops, 100 msec = 0.1 sec
    
#define MS_BUTTON_HOLD_INTERVAL 1500 // how long user needs to hold button to save timestamp, 3000 msec = 3 sec
#define BUTTON_LOOP_COUNT       (MS_BUTTON_HOLD_INTERVAL/MS_DELAY_INTERVAL)

#define MS_LED_FLASH_INTERVAL   250  // delay in ms used to flash the LED on successful timestamp save
                                     // and error flash state

#define FALSE 0
#define TRUE  1

// TODO @hagarret - need to map to different addresses so all codes are unique
typedef enum {
    NO_ERROR,
    // eeprom errors
    ERROR_CODE_EEPROM_WRITE_ERROR,
    ERROR_CODE_EEPROM_ERASE_ERROR,
    ERROR_CODE_EEPROM_READ_ERROR,
    // misc errors
    ERROR_CODE_UNKNOWN_STATUS,
    ERROR_CODE_UART_CALIBRATION_FAILED,
    ERROR_CODE_TIMESTAMP_SAVE_FAILED,
    ERROR_CODE_UNDEFINED
} error_codes_t;

typedef enum {
    NVM_STATUS_CODE_INIT,
    NVM_STATUS_CODE_CALIBRATED,
    NVM_STATUS_CODE_DATA_STORED,
    NVM_STATUS_CODE_MAX_REACHED,
    NVM_STATUS_CODE_DATA_READ,
    NVM_STATUS_CODE_UNDEFINED
} nvm_status_codes_t;

#ifdef	__cplusplus
}
#endif

#endif	/* CONSTANTS_H */


/*
 * File:   led.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 5:04 PM
 */

//#include "led_flash.h"
//#include <xc.h>
//#include "config_PIC16F18124.h"
//#include "constants.h"
//
//void LED_Flash_ProgramSuccess(void) {
//    uint8_t loop = 0;
//    
//    // LED flash implying program success
//    for(loop = 0; loop < 6; loop++) {
//        // toggle LED 3 times
//        LED_PIN = !LED_PIN;
//        __delay_ms(MS_LED_FLASH_INTERVAL);
//    }
//
//    // leave LED off
//    LED_PIN = LED_OFF;
//}
//
//void LED_Flash_Error(error_codes_t error_code) {
//    // TODO @hagarret - need a reset mechanism here, preferably after transmitting the error code
//    // flash error forever until forced CPU reset
//    while(1) {
//        LED_PIN = !LED_PIN;
//        __delay_ms(MS_LED_FLASH_INTERVAL);
//    }
//}
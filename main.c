/*
 * File:   main.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 5, 2023, 1:31 PM
 */

#include <xc.h>
#include <stdint.h>
#include "config_PIC16F18114.h"
#include "timestamp.h"
#include "led_flash.h"

void main(void) {
    // *************************************
    // Variables
    // *************************************
    uint8_t loop_counter = 0;
    // *************************************
    // End Variables
    // *************************************
    
    Config_RuntimeConfig();
    Timestamp_SetupTimer();
    
    // *************************************
    // Main Loop
    // *************************************
    while(1) {
        LED_PIN = LED_OFF;
        loop_counter = 0;
        
        // loop until button is pressed more than the hold interval
        while(BUTTON_DOWN) {
            LED_PIN = LED_ON;
            __delay_ms(MS_DELAY_INTERVAL);
            loop_counter = loop_counter+1;
            
            // button held for complete delay
            if(loop_counter > LOOP_COUNT) {
                // run save code
                Timestamp_Save(TMR0H, TMR0L);
                // implies success if previous function returns
                LED_Flash_ProgramSuccess();

                while(BUTTON_DOWN) {
                    // while button is still held down after save and LED flash, do nothing
                }
            }
        }

        // if docked, do uart xfer of timestamps
    }
    // *************************************
    // End Main Loop
    // *************************************
    
    return;
}
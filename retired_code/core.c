/*
 * File:   core.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on November 29, 2023, 1:31 PM
 */

#include <xc.h>
#include "constants.h"
#include "timestamp.h"
#include "eeprom_access.h"
#include "uart.h"

void Core_InitialSetupLoop(void) {

    nvm_status_codes_t current_status = NULL;
    
    current_status = Utils_NvmReadStatus();

    // need to loop until we are in a state we expect to start main loop
    // technically we need to be re-calibrated by the dock UI
    while(1) {
        // after every reset, the device is not calibrated to the PC dock UI
        // depending on status, reset the eeprom and wait for PC dock
        switch (current_status) {
            default:
            case NVM_STATUS_CODE_CALIBRATED:
                Eeprom_EraseAll();
                Timestamp_ResetPointerAddress();
                Timestamp_ResetTimerOverflowCounter();
                Utils_NvmWriteStatus(NVM_STATUS_CODE_INIT);
            case NVM_STATUS_CODE_INIT:
            case NVM_STATUS_CODE_DATA_STORED:
            case NVM_STATUS_CODE_MAX_REACHED:
            case NVM_STATUS_CODE_DATA_READ:
                LED_Flash_WaitingForDock();
        }

        // Once docked, hand off to dock manager
        Core_UartDockedLoop();

        current_status = Utils_NvmReadStatus();

        // if we return from the docked state and we are calibrated, then we are ready for main
        // operation, otherwise try again to init
        if(current_status == NVM_STATUS_CODE_CALIBRATED) {
            return;
        }
    }
    
}

void Core_MainLoop(void) {
    // *************************************
    uint8_t button_loop_counter = 0;
    // *************************************
    // End Variables
    // *************************************

    // need UART to break out of flash mode and interface to report status codes

    // *************************************
    // Main Loop
    // *************************************
    while(1) {
        // ** Loop Variables *******************
        LED_PIN = LED_OFF;
        button_loop_counter = 0;
        docked_loop_counter = 0;
        // ** End Loop Variables ***************
        
        // ** Button Down Loop *****************
        //    This will loop as long as the button 
        //    is being held down
        while(BUTTON_DOWN) {
            LED_PIN = LED_ON;
            __delay_ms(MS_DELAY_INTERVAL);
            button_loop_counter = button_loop_counter+1;
            
            // When button is held for complete delay,
            // save a timestamp
            if(button_loop_counter > BUTTON_LOOP_COUNT) {
                // run save code
                Timestamp_Save(TMR0L, TMR0H, TIMER_INTERRUPT_FLAG);
                // implies success if previous function returns
                LED_Flash_ProgramSuccess();

                while(BUTTON_DOWN) {
                    // while button is still held down after save and LED flash, do nothing
                }
            }
        }
        // ** End Button Down Loop *************

        // TODO @hagarrett - change this to interrupt
        // ** Timer Overflow Check *************
        //    Check the timer0 overflow interrupt flag
        //    If set, increase saved overflow counter and
        //    reset flag
        if(TIMER_INTERRUPT_FLAG) {
            Timestamp_IncreaseTimerOverflowCounter();
            TIMER_INTERRUPT_FLAG = 0;
        }
        // ** End Timer Overflow Check *********
        
        // slight delay before rerun of main loop
        __delay_ms(MS_DELAY_INTERVAL);
    }
    // *************************************
    // End Main Loop
    // *************************************
}
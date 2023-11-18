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
#include "uart.h"

void main(void) {
    // *************************************
    // Variables
    // *************************************
    uint8_t button_loop_counter = 0;
    uint8_t docked              = 0;
    uint8_t dock_request        = 0;
    uint8_t docked_loop_counter = 0;
    // *************************************
    // End Variables
    // *************************************

    // *************************************
    // Runtime Setup
    // *************************************
    Config_RuntimeConfig();
    Uart_Init();
    Timestamp_SetupTimer();
    // *************************************
    // End Runtime Setup
    // *************************************
    
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

        // ** UART *****************************
        //    When this device is "docked", the dock side 
        //    should send a byte command over UART to let 
        //    us know we are docked
        if(Uart_DataReady() && (Uart_Rx() == UART_DOCKED)) {
            LED_PIN = LED_ON;
            Uart_Docked();
            docked = 1;
        }
        
        // ** UART Docked Loop *****************
        while(docked) {
            // ** UART Dock Commands ***************
            //    If we are docked and there is a byte ready, 
            //    perform requested command
            if(Uart_DataReady()) {
                dock_request = Uart_Rx();
                
                // transfer timestamps
                if(dock_request == UART_TRANSFER_START) {
                    // TODO @hagarrett - add LED flashing for data transfer state (on dock side))
                    Uart_TransferEeprom();
                }
                
                // reset and calibrate
                if(dock_request == UART_CALIBRATE) {
                    Uart_ResetAndCalibrate();
                }

                // write a test timestamp (for debug purposes)
                if(dock_request == UART_WRITE_TEST_TIME) {
                    Uart_WriteTestTimestamp();
                }

                // if received a dockui "dock" query, restart counter and respond
                if(dock_request == UART_DOCKED) {
                    docked_loop_counter = 0;
                    Uart_Tx(UART_SUCCESS);
                }
            }
            // ** End UART Dock Commands ***********
            
            // ** UART Dock Timeout Check **********
            //    dockui should refresh docking success before 
            //    timeout (see check above)
            //    Note: docking timeout isn't affected/increased by transmit  
            //          or reset and calibrate, only by idle time
            if(docked_loop_counter > DOCKED_LOOP_COUNT) {
                Uart_Undocked();
                docked = 0;
                LED_PIN = LED_OFF;
            }
            else {
                // delay and loop again if timeout hasn't been reached
                __delay_ms(MS_DELAY_INTERVAL);
                docked_loop_counter = docked_loop_counter+1;
            }
            // ** End UART Dock Timeout Check *******
        }
        // ** End UART Docked Loop *************
        // ** End UART *************************
        
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
    
    return;
}
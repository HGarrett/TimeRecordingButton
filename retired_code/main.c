/*
 * File:   main.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 5, 2023, 1:31 PM
 */

// #include <xc.h>
// #include <stdint.h>
// #include "config_PIC16F18114.h"

// #include "led_flash.h"
// #include "uart.h"

/* Globals */

void main(void) {
    Config_RuntimeConfig();

    Uart_Init();
    Timestamp_Init();
    
    Core_InitialSetupLoop();
    Core_MainLoop();
    
    return;
}
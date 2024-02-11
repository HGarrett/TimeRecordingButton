/*
 * File:   config.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 9:12 AM
 */

#include <xc.h>
#include "config_PIC16F15313.h"

void Config_RuntimeConfig(void) {
    VREGCONbits.VREGPM = 1; // Enable low power sleep mode, PIC16F15313 only, LF device doesn't have this.
 
    // configuring PORTA
    LATA   = 0;    // TODO @hagarrett - why is init this to 0 necessary
    TRISA  = 0x10; // RA4 is an input, everything else is an output
    ANSELA = 0;    // all pins are digital
    WPUA   = 0;    // weak pull up disabled on all pins

    // disable modules, lowest power possible
    PMD2=0xFF;
    PMD3=0xFF;
    PMD4=0xF9; // leave MSSP1MD enabled (bit 4 b'1111 0111)
    PMD5=0xFF;
}
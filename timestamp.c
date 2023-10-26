/*
 * File:   timestamp.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 8:59 AM
 */

#include <xc.h>
#include <stdint.h>
#include "timestamp.h"
#include "eeprom_access.h"
#include "led_flash.h"

void Timestamp_SetupTimer(void) {
    // TMR0 Settings
    T0CON0 = 0xD1; // TMR0 Enabled, 16-bit timer, 1:2 Post-scaler
    T0CON1 = 0x88; // Clock source LFINTOSC, ASYNC is disabled, Pre-scaler 1:256
    
    // EEPROM setup for timestamp non-volatile storage
    // Write the list start address to the timestamp address pointer stored in EEPROM
    EEPROM_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, TIMESTAMP_START_ADDRESS);
}

void Timestamp_Save(uint8_t timer_bits_high, uint8_t timer_bits_low) {
    uint8_t current_timestamp_list_pointer = 0;
    
    // read byte from TIMESTAMP_END_ADDRESS_POINTER
    current_timestamp_list_pointer = EEPROM_ReadByte(TIMESTAMP_CURRENT_ADDRESS_POINTER);
    
    // write bytes to address read
    EEPROM_WriteByte(current_timestamp_list_pointer, timer_bits_low);
    EEPROM_WriteByte(current_timestamp_list_pointer++, timer_bits_high);
    
    current_timestamp_list_pointer++;
    
    // write new end address to TIMESTAMP_END_ADDRESS_POINTER
    EEPROM_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, current_timestamp_list_pointer);
    
    // If at max address to save a timestamp, hang forever and flash LED
    if(current_timestamp_list_pointer >= TIMESTAMP_MAX_ADDRESS_POINTER) {
        LED_Flash_Error(); // does not return
    }
}
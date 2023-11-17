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
    Timestamp_ResetPointerAddress();
    Timestamp_ResetTimerOverflowCounter();
}

void Timestamp_ResetPointerAddress(void) {
    // Write the list start address to the timestamp address pointer stored in EEPROM
    Eeprom_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, TIMESTAMP_START_ADDRESS);
}

void Timestamp_ResetTimerOverflowCounter(void) {
    // Write 0 to the overflow loop counter stored in EEPROM
    Eeprom_WriteByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER, 0x0);
}

uint8_t Timestamp_IncreaseTimerOverflowCounter(void) {
    uint8_t current_timer_overflow_count = 0;
    
    // read byte from TIMESTAMP_OVERFLOW_LOOP_COUNTER
    // to get the current overflow count
    current_timer_overflow_count = Eeprom_ReadByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER);
    
    // increase the count and write the new count value
    Eeprom_WriteByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER, ++current_timer_overflow_count);
    
    return current_timer_overflow_count;
}

void Timestamp_Save(uint8_t timer_bits_high, uint8_t timer_bits_low, uint8_t overflow) {
    uint8_t current_timestamp_list_pointer = 0;
    uint8_t current_timer_overflow_count   = 0;
    
    // if the overflow flag is true, increase counter before save
    if(overflow) {
        current_timer_overflow_count = Timestamp_IncreaseTimerOverflowCounter();
        TIMER_INTERRUPT_FLAG = 0;
    }
    else {
        current_timer_overflow_count = Eeprom_ReadByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER);
    }
    
    // read byte from TIMESTAMP_END_ADDRESS_POINTER
    // to get the current list pointer
    current_timestamp_list_pointer = Eeprom_ReadByte(TIMESTAMP_CURRENT_ADDRESS_POINTER);
    
    // write bytes to address read
    Eeprom_WriteByte(current_timestamp_list_pointer++, current_timer_overflow_count);
    Eeprom_WriteByte(current_timestamp_list_pointer++, timer_bits_high);
    Eeprom_WriteByte(current_timestamp_list_pointer++, timer_bits_low);
    
    // write new end address to TIMESTAMP_END_ADDRESS_POINTER
    Eeprom_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, current_timestamp_list_pointer);
    
    // If at max address to save a timestamp, hang forever and flash LED
    if(current_timestamp_list_pointer >= TIMESTAMP_MAX_ADDRESS_POINTER) {
        LED_Flash_Error(); // does not return
    }
}
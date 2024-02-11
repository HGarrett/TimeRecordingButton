/*
 * File:   timestamp.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 8:59 AM
 */
//
//#include <xc.h>
//#include <stdint.h>
//#include "constants.h"
//#include "timestamp.h"
//#include "eeprom_access.h"
//#include "led_flash.h"
//
//void Timestamp_Init(void) {
//    // uint8_t current_address_pointer = 0xFF;
//    
//    // TMR0 Settings
//    T0CON0 = 0xD0; // TMR0 Enabled, 16-bit timer, 1:1 Post-scaler
//    T0CON1 = 0x8F; // Clock source LFINTOSC, ASYNC is disabled, Pre-scaler 1:32768 (1 second per tick in LFINTOSC mode)
//}
//
//void Timestamp_ResetPointerAddress(void) {
//    // Write the list start address to the timestamp address pointer stored in EEPROM
//    Eeprom_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, TIMESTAMP_START_ADDRESS);
//}
//
//void Timestamp_ResetTimerOverflowCounter(void) {
//    // Write 0 to the overflow loop counter stored in EEPROM
//    Eeprom_WriteByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER, 0x0);
//}
//
//uint8_t Timestamp_IncreaseTimerOverflowCounter(void) {
//    uint8_t current_timer_overflow_count = 0;
//    
//    // read byte from TIMESTAMP_OVERFLOW_LOOP_COUNTER
//    // to get the current overflow count
//    current_timer_overflow_count = Eeprom_ReadByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER);
//    
//    // increase the count and write the new count value
//    Eeprom_WriteByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER, ++current_timer_overflow_count);
//    
//    return current_timer_overflow_count;
//}
//
//error_codes_t Timestamp_Save(uint8_t timer_bits_low, uint8_t timer_bits_high, uint8_t overflow, uint8_t override) {
//    uint8_t current_timestamp_list_pointer = 0;
//    uint8_t current_timer_overflow_count   = 0;
//    nvm_status_codes_t current_status      = NULL;
//
//    // check that the nvm is in the right state for recording
//    if(!override && Utils_NvmReadStatus() != ) {
//    }
//    
//    // if the overflow flag is true, increase counter before save
//    if(overflow) {
//        current_timer_overflow_count = Timestamp_IncreaseTimerOverflowCounter();
//        TIMER_INTERRUPT_FLAG = 0;
//    }
//    else {
//        current_timer_overflow_count = Eeprom_ReadByte(TIMESTAMP_OVERFLOW_LOOP_COUNTER);
//    }
//    
//    // read byte from TIMESTAMP_END_ADDRESS_POINTER
//    // to get the current list pointer
//    current_timestamp_list_pointer = Eeprom_ReadByte(TIMESTAMP_CURRENT_ADDRESS_POINTER);
//    
//    // write bytes to address read
//    Eeprom_WriteByte(current_timestamp_list_pointer++, current_timer_overflow_count);
//    Eeprom_WriteByte(current_timestamp_list_pointer++, timer_bits_high);
//    Eeprom_WriteByte(current_timestamp_list_pointer++, timer_bits_low);
//    
//    // write new end address to TIMESTAMP_END_ADDRESS_POINTER
//    Eeprom_WriteByte(TIMESTAMP_CURRENT_ADDRESS_POINTER, current_timestamp_list_pointer);
//
//    // TODO @hagarrett - add status data stored and max reached
//    
//    // If at max address to save a timestamp, write status code to NVM, hang forever and flash LED
//    if(current_timestamp_list_pointer >= TIMESTAMP_MAX_ADDRESS_POINTER) {
//        Eeprom_WriteByte(EEPROM_STATUS_BYTE, STATUS_CODE_TIMESTAMP_MAX_ERROR);
//        LED_Flash_Error(STATUS_CODE_TIMESTAMP_MAX_ERROR); // does not return
//    }
//}
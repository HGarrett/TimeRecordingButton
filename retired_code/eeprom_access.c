/*
 * File:   eeprom_access.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 15, 2023, 10:31 PM
 */

#include <xc.h>
#include <stdint.h>
#include "config_PIC16F18124.h"
#include "constants.h"
#include "eeprom_access.h"
#include "led_flash.h"

uint8_t Eeprom_ReadByte(uint8_t eeprom_address) {
    // This code block will read 1 word (byte) of EEPROM
    NVMCON1bits.NVMREGS = 1; // Point to EEPROM
    NVMADR = (((uint16_t) EEPROM_DEFAULT_NVMADRH << 8) | (eeprom_address)); // NVMADRH = 0x70, NVMADRL = EEPROM address
    NVMCON1bits.RD = 1;      // Initiate read cycle

    return NVMDATL;          // EEPROM data byte is in NVMDAT
}

void Eeprom_WriteByte(uint8_t eeprom_address, uint8_t eeprom_data) {
    // Code sequence to write one byte of EEPROM
    NVMCON1bits.NVMREGS = 1; // Point to EEPROM
    NVMADR = (((uint16_t) EEPROM_DEFAULT_NVMADRH << 8) | (eeprom_address)); // NVMADRH = 0x70, NVMADRL = EEPROM address
    NVMDATL = eeprom_data;   // Load NVMDATL
    NVMCON1bits.WREN = 1;    // Allows program/erase cycles
    INTCONbits.GIE = 0;      // Disable interrupts
    
    // Perform required unlock sequence
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    
    NVMCON1bits.WR = 1;      // Begin program/erase cycle, CPU suspended until complete
    INTCONbits.GIE = 1;      // Restore interrupt enable bit value
    NVMCON1bits.WREN = 0;    // Disable program/erase
    
    __delay_ms(EEPROM_MS_DELAY);
    
    // Verify byte write operation success, if error hang in LED flash state
    if (NVMCON1bits.WRERR) {
        LED_Flash_Error(EEPROM_ERROR_CODE_WRITE_ERROR); // does not return
    }
}

void Eeprom_EraseByte(uint8_t eeprom_address) {
    // Code sequence to erase one byte of EEPROM
    NVMCON1bits.NVMREGS = 1; // Point to EEPROM
    NVMADR = (((uint16_t) EEPROM_DEFAULT_NVMADRH << 8) | (eeprom_address)); // NVMADRH = 0x70, NVMADRL = EEPROM address
    NVMDATL = 0xFF;          // Load NVMDATL with 0xFF
    NVMCON1bits.WREN = 1;    // Allows program/erase cycles
    INTCONbits.GIE = 0;      // Disable interrupts
    
    // Perform required unlock sequence
    NVMCON2 = 0x55;
    NVMCON2 = 0xAA;
    
    NVMCON1bits.WR = 1;      // Begin program/erase cycle, CPU suspended until complete
    INTCONbits.GIE = 1;      // Restore interrupt enable bit value
    NVMCON1bits.WREN = 0;    // Disable program/erase
    
    __delay_ms(EEPROM_MS_DELAY);
    
    // Verify byte erase operation success, if error hang in LED flash state
    if (NVMCON1bits.WRERR) {
        LED_Flash_Error(EEPROM_ERROR_CODE_ERASE_ERROR); // does not return
    }
}

void Eeprom_EraseAll(void) {
    uint8_t eeprom_address;
    
    for(eeprom_address = EEPROM_START_ADDRESS_NVMADRL;
            eeprom_address < EEPROM_SIZE; eeprom_address++) {
        Eeprom_EraseByte(eeprom_address);
    }
}



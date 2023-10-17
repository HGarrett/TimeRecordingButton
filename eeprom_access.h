/* 
 * File:   eeprom_access.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 15, 2023, 10:31 PM
 */

#ifndef EEPROM_ACCESS_H
#define	EEPROM_ACCESS_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>

#define EEPROM_START_ADDRESS         0x7000
#define EEPROM_DEFAULT_NVMADRH       0x70
#define EEPROM_START_ADDRESS_NVMADRH EEPROM_DEFAULT_NVMADRH
#define EEPROM_START_ADDRESS_NVMADRL 0x00

uint8_t EEPROM_ReadByte(uint8_t eeprom_address);
void    EEPROM_EraseByte(uint8_t eeprom_address);
void    EEPROM_WriteByte(uint8_t eeprom_address, uint8_t eeprom_data);

#ifdef	__cplusplus
}
#endif

#endif	/* EEPROM_ACCESS_H */


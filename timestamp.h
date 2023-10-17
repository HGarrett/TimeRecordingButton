/* 
 * File:   save_timestamp.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 9:00 AM
 */

#ifndef TIMESTAMP_H
#define	TIMESTAMP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <stdint.h>
#include "eeprom_access.h"

#define TIMESTAMP_CURRENT_ADDRESS_POINTER EEPROM_START_ADDRESS_NVMADRL
#define TIMESTAMP_START_ADDRESS           (TIMESTAMP_CURRENT_ADDRESS_POINTER+1)
#define TIMESTAMP_MAX_ADDRESS_POINTER     (EEPROM_SIZE-2)

void Timestamp_SetupTimer(void);
void Timestamp_Save(uint8_t timer_bits_high, uint8_t timer_bits_low);

#ifdef	__cplusplus
}
#endif

#endif	/* TIMESTAMP_H */


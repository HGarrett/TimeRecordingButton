/* 
 * File:   led_flash.h
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on October 16, 2023, 5:04 PM
 */

#ifndef LED_FLASH_H
#define	LED_FLASH_H

#ifdef	__cplusplus
extern "C" {
#endif

#include "constants.h"
    
void LED_Flash_ProgramSuccess(void);
void LED_Flash_Error(status_codes_t status_code); // Does not return

#ifdef	__cplusplus
}
#endif

#endif	/* LED_FLASH_H */


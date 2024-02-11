/*
 * File:   utils.c
 * Author: hillary.a.garrett@gmail.com
 *
 * Created on November 29, 2023, 1:31 PM
 */

#include "constants.h"

nvm_status_codes_t Utils_NvmReadStatus(void) {
    return (nvm_status_codes_t)Eeprom_ReadByte(EEPROM_STATUS_BYTE);
}

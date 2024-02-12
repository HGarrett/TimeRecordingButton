/**
 * AT24C16D Generated Driver API Header File
 * 
 * @file at24c16d.h
 * 
 * @defgroup at24c16d AT24C16D
 * 
 * @brief This file contains API prototypes for the AT24C16D driver module.
 *
 * @version AT24C16D Driver Version 1.1.1
*/
 
#ifndef AT24C16D_H
#define AT24C16D_H
 
#include <stdint.h>
 
/**
 * @ingroup at24c16d
 * @brief Writes one byte of data to a specified address in the AT24C16D EEPROM device.
 * @pre Initialize MSSP2 before calling this routine.
 * @param uint32_t address - EEPROM address where the data is to be written.
 * @param uint8_t data - Data to be written to the specified EEPROM address.
 * @return None.
 */
void AT24C16D_WriteOneByte(uint32_t address, uint8_t data);

/**
 * @ingroup at24c16d
 * @brief Reads one byte of data from a specified address in the AT24C16D EEPROM device.
 * @pre Initialize MSSP2 before calling this routine.
 * @param uint32_t address - EEPROM address from where data is read.
 * @return One byte of data read from a specified EEPROM address.
 */
uint8_t AT24C16D_ReadOneByte(uint32_t address);

/**
 * @ingroup at24c16d
 * @brief Writes n-bytes of data starting from a specified address in the AT24C16D EEPROM device.
 * @pre Initialize MSSP2 before calling this routine.
 * @param uint32_t startAddress - EEPROM address where the first data is to be written.
 * @param void *data - Pointer to the data to be written.
 * @param uint16_t byteCount - Number of data bytes to be written.
 * @return None.
 */
void AT24C16D_Write(uint32_t startAddress, void *data, uint16_t byteCount);

/**
 * @ingroup at24c16d
 * @brief Reads n-bytes of data starting from a specified address in the AT24C16D EEPROM device.
 * @pre Initialize MSSP2 before calling this routine.
 * @param uint32_t startAddress - EEPROM address from where the first data is read.
 * @param void *data - Pointer to where the data read from EEPROM is stored.
 * @param uint16_t byteCount - Number of data bytes to be read.
 * @return None.
 */
void AT24C16D_Read(uint32_t startAddress, void* data, uint16_t byteCount);
 
#endif //AT24C16D_H
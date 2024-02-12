/**
 * AT24C16D Driver File
 *
 * @file at24c16d_config.h
 * 
 * @ingroup at24c16d
 * 
 * @brief This file contains the AT24C16D device configuration.
 *
 * @version AT24C16D Driver Version 0.1
*/

#ifndef AT24C16D_CONFIG_H
#define AT24C16D_CONFIG_H
 
#ifdef __cplusplus
extern "C" {
#endif
 
 
#define DEVICE_ID 0xA
 
#define GND 0
#define VCC 1
#define DEVICE_ADDRS_BIT GND
 
#define EEPROM_W 0
#define EEPROM_R 1
#define RW_OPERATION EEPROM_W
 
#define DEVICE_ADDRS_BYTE ((DEVICE_ID << 4) | (DEVICE_ADDRS_BIT << 3) | (0x0 << 2) | RW_OPERATION)

#define PAGESIZE 16
 
#ifdef __cplusplus
}
#endif
 
#endif /* AT24C16D_CONFIG_H */
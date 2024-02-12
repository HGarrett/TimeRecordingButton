/**
 * AT24CM02 Generated Driver File
 *
 * @file at24cm02_config.h
 * 
 * @ingroup at24cm02
 * 
 * @brief This file contains the AT24CM02 device configuration.
 *
 * @version AT24CM02 Driver Version 1.1.1
*/

/*
� [2024] Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms, you may use Microchip 
    software and any derivatives exclusively with Microchip products. 
    You are responsible for complying with 3rd party license terms  
    applicable to your use of 3rd party software (including open source  
    software) that may accompany Microchip software. SOFTWARE IS ?AS IS.? 
    NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS 
    SOFTWARE, INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT,  
    MERCHANTABILITY, OR FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT 
    WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY 
    KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF 
    MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE 
    FORESEEABLE. TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP?S 
    TOTAL LIABILITY ON ALL CLAIMS RELATED TO THE SOFTWARE WILL NOT 
    EXCEED AMOUNT OF FEES, IF ANY, YOU PAID DIRECTLY TO MICROCHIP FOR 
    THIS SOFTWARE.
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
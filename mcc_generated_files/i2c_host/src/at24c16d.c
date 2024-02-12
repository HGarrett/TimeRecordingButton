/**
 * AT24C16D Generated Driver File
 *
 * @file at24c16d.c
 * 
 * @ingroup at24c16d
 * 
 * @brief This file contains the driver code for the AT24C16D module.
 *
 * @version AT24C16D Driver Version 1.1.1
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
 
#include "../at24c16d.h"
#include "../at24c16d_config.h"
#include "../../system/system.h"
#include <stdlib.h>
 
#define MIN(a,b) (a<b?a:b)
 
/**
 * @ingroup at24c16d
 * @struct block_t
 * @brief Defines the block of data to be sent through I2C which contains the EEPROM address, data and data size.
 */
typedef struct
{
    uint16_t wordAdress;
    uint8_t *data;
    uint16_t dataSize;
} block_t;

/**
 * @ingroup at24c16d
 * @struct addrs_t
 * @brief Defines the EEPROM address data containing the device address and the word address (lower 16-byte of the EEPROM address).
 */
typedef struct
{
    uint8_t deviceAddrs;
    uint16_t wordAddrs;
} addrs_t;
 
// Local APIs Declaration

/**
 * @ingroup at24c16d
 * @brief Gets the Most Significant Byte (MSB) from the specified EEPROM address.
 * @param uint32_t address - A specific address in the AT24C16D EEPROM device.
 * @return EEPROM address MSB.
 */
static uint8_t AT24C16D_MSBAddressGet(uint32_t address);

/**
 * @ingroup at24c16d
 * @brief Gets the 16-bit word address from the specified EEPROM address.
 * @param uint32_t address - A specific address in the AT24C16D EEPROM device.
 * @return 16-bit word address.
 */
static uint16_t AT24C16D_WordAddressGet(uint32_t address);

/**
 * @ingroup at24c16d
 * @brief Returns the device address of the AT24C16D EEPROM.
 * @param uint32_t MSBAddress - MSB of the specified EEPROM address.
 * @return Device address.
 */
static uint8_t AT24C16D_DeviceAddressGet(uint8_t MSBAddress);
 
/**
 * @ingroup at24c16d
 * @brief Returns the AT24C16D address structure containing the device and word address data.
 * @param uint32_t address - A specific address in the AT24C16D EEPROM device.
 * @return Calculated AT24C16D address structure.
 */
static addrs_t AT24C16D_ParsedAddressGet(uint32_t address);
 
/**
 * @ingroup at24c16d
 * @brief Calculates the data to be sent through the I2C protocol by appending the EEPROM address with the actual data.
 * @param block_t *block - Structure of data containing the EEPROM address, actual data and number of data.
 * @param uint8_t *dataToSend - Pointer to where the calculated data to be sent is stored.
 * @return None.
 */
static void AT24C16D_DataToSendSet(block_t *block, uint8_t *dataToSend);
  
/*
* Global API Definitions
*/
 
void AT24C16D_WriteOneByte(uint32_t address, uint8_t data)
{
    AT24C16D_Write(address, &data, 1);
}
 
uint8_t AT24C16D_ReadOneByte(uint32_t address)
{
    uint8_t readData = 0;
 
    AT24C16D_Read(address, &readData, 1);
 
    return readData;
}
 
void AT24C16D_Write(uint32_t startAddress, void *data, uint16_t byteCount)
{
    bool i2cStatus;
    addrs_t parsedAddrs;
    block_t block = { 0 };
    uint8_t dataToSend[PAGESIZE];
 
    uint16_t blockSize = (uint16_t) PAGESIZE - (startAddress & (PAGESIZE - 1));
    uint8_t *blockData = data;
 
    do
    {
        blockSize = MIN(blockSize,byteCount);
 
        parsedAddrs = AT24C16D_ParsedAddressGet(startAddress);
 
        block.wordAdress = parsedAddrs.wordAddrs;
        block.data = blockData;
        block.dataSize = blockSize;
 
        AT24C16D_DataToSendSet(&block, dataToSend);
        i2cStatus = AT24C16D_I2C.Write(parsedAddrs.deviceAddrs, dataToSend, (blockSize + 2));
        if (i2cStatus)
        {
            while (AT24C16D_I2C.IsBusy());
        }
        else
        {
            return;
        }
 
        startAddress = (startAddress + blockSize) & 0x3FFFF;
        blockData = blockData + blockSize;
        byteCount = byteCount - blockSize;
        blockSize = PAGESIZE;
    } while(byteCount > 0);
}
 
void AT24C16D_Read(uint32_t startAddress, void* data, uint16_t byteCount)
{
    bool i2cStatus;
    addrs_t parsedAddrs;
    block_t block = { 0 };
    uint8_t dataToSend[PAGESIZE];
 
    parsedAddrs = AT24C16D_ParsedAddressGet(startAddress);
 
    block.wordAdress = parsedAddrs.wordAddrs;
    block.data = NULL;
    block.dataSize = 0;
 
    AT24C16D_DataToSendSet(&block, dataToSend);
    i2cStatus = AT24C16D_I2C.WriteRead(parsedAddrs.deviceAddrs, dataToSend, 2, data, byteCount);
    if (i2cStatus)
    {
        while (AT24C16D_I2C.IsBusy());
    }
    else
    {
        return;
    }
}

/*
* Local API Definitions
*/
 
static uint8_t AT24C16D_MSBAddressGet(uint32_t address)
{
    uint8_t deviceAddress;
 
    deviceAddress = (address & 0xF0000) >> 16;
 
    return (deviceAddress);
}

static uint16_t AT24C16D_WordAddressGet(uint32_t address)
{
    return (uint16_t) (address & 0x00FFFF);
}

static uint8_t AT24C16D_DeviceAddressGet(uint8_t MSBAddress)
{
    MSBAddress = ((MSBAddress << 1) & 0x06);
 
    return ((DEVICE_ADDRS_BYTE | MSBAddress) >> 1);
}

static addrs_t AT24C16D_ParsedAddressGet(uint32_t address)
{
    addrs_t addrs;
 
    uint8_t msbAddrs = AT24C16D_MSBAddressGet(address);
    addrs.deviceAddrs = AT24C16D_DeviceAddressGet(msbAddrs);
    addrs.wordAddrs = AT24C16D_WordAddressGet(address);
 
    return addrs;
}

static void AT24C16D_DataToSendSet(block_t *block, uint8_t *dataToSend)
{
    dataToSend[0] = (block->wordAdress >> 8) &0xFF;
    dataToSend[1] = block->wordAdress & 0xFF;
 
    for (uint16_t index = 0; index < block->dataSize; ++index) {
        dataToSend[index + 2] = *(block->data + index);
    }
}

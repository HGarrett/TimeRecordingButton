/*
 * cli_setup.h
 *
 *  Created on: Jul 7, 2023
 *      Author: NeusAap
 * 
 *  Adopted on: Feb 11, 2024
 *      Author: hagarrett
 */

#ifndef INC_CLI_SETUP_H_
#define INC_CLI_SETUP_H_

#include "embedded_cli.h"

// Definitions for CLI sizes
#define CLI_BUFFER_SIZE 64
#define CLI_RX_BUFFER_SIZE 16
#define CLI_CMD_BUFFER_SIZE 32
#define CLI_MAX_BINDING_COUNT 8

/**
 * Definition of the cli_send_ctype() buffer size.
 * Can make smaller to decrease RAM usage,
 * make larger to be able to print longer strings.
 */
#define CLI_PRINT_BUFFER_SIZE 32

/**
 * Function to setup the configuration settings for the CLI,
 * based on the definitions from this header file
 */
void setupCli(void);

/**
 * TODO @hagarrett - add description
*/
void cli_pass_rx_char(char c);

/**
 * TODO @hagarrett - add description
*/
void cli_send_ctype(uint8_t *buffer, size_t size);

/**
 * TODO @hagarrett - add description
*/
void cli_send_string(char *buffer);

/**
 * Getter function, to keep only one instance of the EmbeddedCli pointer in this file.
 * @return
 */
EmbeddedCli *getCliPointer(void);

#endif /* INC_CLI_SETUP_H_ */
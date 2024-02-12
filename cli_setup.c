/*
 * cli_setup.c
 *
 *  Created on: Jul 7, 2023
 *      Author: NeusAap
 * 
 *  Adopted on: Feb 11, 2024
 *      Author: hagarrett
 */


// STD LIBS
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Own CLI headers
#include "cli_setup.h"
#include "cli_binding.h"

// Expand cli implementation here (must be in one file only)
#define EMBEDDED_CLI_IMPL

#include "embedded_cli.h"

#include "mcc_generated_files/uart/eusart1.h"

// CLI buffer
static EmbeddedCli *cli;
static uint8_t cliBuffer[CLI_BUFFER_SIZE];

// Bool to disable the interrupts, if CLI is not yet ready.
static bool cliIsReady = false;

// Write function used in 'setupCli()' to route the chars over UART.
static void writeCharToCli(EmbeddedCli *embeddedCli, char c) {
    uint8_t c_to_send = c;
    EUSART1_Write(c_to_send);
}

// Function to setup the configuration settings for the CLI, based on the definitions from this header file
void setupCli(void) {
    // Initialize the CLI configuration settings
    EmbeddedCliConfig *config;
    config->cliBuffer = cliBuffer;
    config->cliBufferSize = CLI_BUFFER_SIZE;
    config->rxBufferSize = CLI_RX_BUFFER_SIZE;
    config->cmdBufferSize = CLI_CMD_BUFFER_SIZE;
    config->maxBindingCount = CLI_MAX_BINDING_COUNT;

    // Create new CLI instance
    cli = embeddedCliNew(config);
    // Assign character write function
    cli->writeChar = writeCharToCli;

    // CLI init failed. Is there not enough memory allocated to the CLI?
    // Please increase the 'CLI_BUFFER_SIZE' in header file.
    // Or decrease max binding size.
    // You can get required buffer size by calling
    // uint16_t requiredSize = embeddedCliRequiredSize(config);
    // Then check it's value in debugger
    while (cli == NULL) {
//        HardFault_Handler();
    }

    // Add all the initial command bindings
    initCliBinding();

    // CLI has now been initialized, set bool to true to enable interrupts.
    cliIsReady = true;
}

// pass HW (eusart1) received characters to the embedded-cli
void cli_pass_rx_char(char c) {
    if (cliIsReady) {
        embeddedCliReceiveChar(cli, c);
    }
}

void cli_send_ctype(uint8_t *buffer, size_t size) {
    embeddedCliSendCtype(getCliPointer(), buffer, size);
}

void cli_send_string(char *buffer) {
    // TODO @hagarret - need to add error here if the string is too big
    embeddedCliPrint(getCliPointer(), buffer);
}

EmbeddedCli *getCliPointer(void) {
    return cli;
}
/*
 * cli_binding.c
 *
 *  Created on: Jul 7, 2023
 *      Author: NeusAap
 * 
 *  Adopted on: Feb 11, 2024
 *      Author: hagarrett
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // needed for custom memcpy below

#include "cli_setup.h"
#include "cli_binding.h"

#define BASE10                   10
#define TRUE_ARG_STR            "true"
#define FALSE_ARG_STR           "false" 
#define ENABLED_STR             "enabled"
#define DISABLED_STR            "disabled" 
#define COMMAND_SUCCESS         "OK"
#define COMMAND_FAILURE         "FAIL"
#define CONTROL_CHAR_OFFSET      10
#define CONTROL_CHAR_REPLACEMENT 0xFF

void * memcpy_clistruct(void *s1, const void *s2, register size_t n)
{
    register char *p1 = s1;
    register const char *p2 = s2;

    if(n) {
        n++;
        while (--n > 0) {
            if((uint8_t)*p2 == CONTROL_CHAR_REPLACEMENT) {
                p2++;
                *p1++ = CONTROL_CHAR_OFFSET + (uint8_t)*p2++;
            }
            else {
                *p1++ = *p2++;
            }
        }
    }
    return s1;
}

void onRequestSomeUnion(EmbeddedCli *cli, char *args) {
//    static some_union_t u_some_union;
//    char     *endptr;
//    uint32_t  config_num;
//
//    const char *arg1 = embeddedCliGetToken(args, 1);
//
//    if (arg1 == NULL) {
//        cli_send_ctype("usage: request_union [arg1]");
//        cli_send_ctype("arg1: some union requested");
//        return;
//    }
//
//    /* use this to convert strings to numbers
//        config_num = strtoul(arg1, &endptr, BASE10);
//        if (*endptr != '\0') {
//            return;
//        }
//    */
//
//    cli_send_ctype(u_some_union.u8, sizeof(u_some_union.u8));
//    cli_send_ctype(COMMAND_SUCCESS);
}

void onTestUart(EmbeddedCli *cli, char *args) {
   const char *arg1 = embeddedCliGetToken(args, 1);

   if (arg1 == NULL) {
       cli_send_string("usage: test [arg1]");
       return;
   }

//    atoi(arg1);

   cli_send_string(COMMAND_SUCCESS);
}

void initCliBinding() {
    // Define bindings as local variables, so we don't waste static memory

    // CliCommandBinding request_union_binding = {
    //         .name = "request_union",
    //         .tokenizeArgs = true,
    //         .binding = onRequestSomeUnion
    // };

    CliCommandBinding test_uart_binding = {
            .name = "test",
            .tokenizeArgs = true,
            .binding = onTestUart
    };

    EmbeddedCli *cli = getCliPointer();
    // embeddedCliAddBinding(cli, request_union_binding);
    embeddedCliAddBinding(cli, test_uart_binding);
}
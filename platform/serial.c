/*
* Copyright (c) 2017-2020 Arm Limited
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*     http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <stdio.h>
#include <string.h>
#include "RTE_Components.h"
#include "perf_counter.h"

#if defined(RTE_Compiler_EventRecorder)
#   include <EventRecorder.h>
#endif

#if defined(RTE_Compiler_IO_STDOUT_User)

#include "device_cfg.h"
#include "Driver_USART.h"
#include "serial.h"

extern ARM_DRIVER_USART Driver_USART0;

void serial_init(void)
{
    Driver_USART0.Initialize(NULL);
    Driver_USART0.Control(ARM_USART_MODE_ASYNCHRONOUS, DEFAULT_UART_BAUDRATE);
}

void serial_print(char *str)
{
    (void)Driver_USART0.Send(str, strlen(str));
}




/* Redirects gcc printf to UART0 */
int _write(int fd, char *str, int len)
{
    if (Driver_USART0.Send(str, len) == ARM_DRIVER_OK) {
        return len;
    }
    return 0;
}

int stdout_putchar(int ch)
{
    if ('\n' == ch) {
        int temp = '\r';
        while(Driver_USART0.Send(&temp, 1) != ARM_DRIVER_OK);
    }
    
    if (Driver_USART0.Send(&ch, 1) == ARM_DRIVER_OK) {
        return ch;
    }
    
    return -1;
}


/* Redirects armclang printf to UART */
int fputc(int ch, FILE *f)
{
    return stdout_putchar(ch);
}

#endif

#if __IS_COMPILER_GCC__ || __IS_COMPILER_LLVM__

static int stdout_putchar (int ch) {
  static uint32_t index = 0U;
  static uint8_t  buffer[8];
 
  if (index >= 8U) {
    return (-1);
  }
  buffer[index++] = (uint8_t)ch;
  if ((index == 8U) || (ch == '\n')) {
    EventRecordData(EventID(EventLevelOp, 0xFE, 0x00), buffer, index);
    index = 0U;
  }
  return (ch);
}

__attribute__((section(".text._write"),used))
/* Redirects gcc printf to UART0 */
int _write(int fd, char *str, int len)
{
    do {
        stdout_putchar(*str++);
    } while(--len);
    
    return 0;
}

#endif

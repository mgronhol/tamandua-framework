#ifndef _EMULATOR_H_
#define _EMULATOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>

#include <assert.h>

#include "DeviceDriver.h"

#define EMU_PIN_0 0
#define EMU_PIN_1 1
#define EMU_PIN_2 2
#define EMU_PIN_3 3
#define EMU_PIN_4 4
#define EMU_PIN_5 5
#define EMU_PIN_6 6
#define EMU_PIN_7 7

#define EMU_READ_SINGLE 0
#define EMU_READ_ALL 1

#define EMU_WRITE_ONE 0
#define EMU_WRITE_ALL 0xF00


device_t* emulator_portA_init();
device_t* emulator_portB_init();

device_t* emulator_usart_init();
device_t* emulator_ad_init();



#endif

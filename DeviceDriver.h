#ifndef _DEVICE_DRIVER_H_
#define _DEVICE_DRIVER_H_

#include <stdint.h>


typedef void* (*device_callback)(void*, void*);



typedef struct {
	uint16_t id;
	void *data;
	
	device_callback read, write;
	
	} device_t;


device_t* device_init( uint16_t device_id );



#endif

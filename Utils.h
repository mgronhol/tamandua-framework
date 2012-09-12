#ifndef _UTILS_H_
#define _UTILS_H_
#include <stdint.h>


#define SET_BIT( target, nth ) (target) |= (1<<(nth))
#define UNSET_BIT( target, nth ) (target) &= ~(1<<(nth))
#define TOGGLE_BIT( target, nth ) (target) ^= (1<<(nth))

#define GET_BIT( target, nth ) (((target) & (1<<(nth)))>>(nth))

#define BITARRAY_SET( array, nth )  (array)[((nth)-(nth)%8)/8] |= (1<<((nth)%8))
#define BITARRAY_UNSET( array, nth )  (array)[((nth)-(nth)%8)/8] &= (~(1<<((nth)%8)))
#define BITARRAY_TOGGLE( array, nth )  (array)[((nth)-(nth)%8)/8] ^= (1<<((nth)%8))

#define BITARRAY_GET( array, nth )  (((array)[((nth)-(nth)%8)/8] & (1<<((nth)%8))) >> ((nth)%8))


#define MAX_RING_BUFFER_SIZE 32

#define MAX_BITFIELD_SIZE 8

typedef struct {
	uint8_t array[ MAX_BITFIELD_SIZE ];
	} bitfield_t;

typedef struct {
	void *buffer[ MAX_RING_BUFFER_SIZE ];
	bitfield_t reserved;
	uint16_t pos;
	} ring_buffer_t;


void bitfield_set( bitfield_t *bf, uint16_t pos );
void bitfield_unset( bitfield_t *bf, uint16_t pos );
void bitfield_toggle( bitfield_t *bf, uint16_t pos );
uint8_t bitfield_get( bitfield_t *bf, uint16_t pos );
void bitfield_clear( bitfield_t *bf );

void ring_buffer_init( ring_buffer_t *buffer );
void ring_buffer_write( ring_buffer_t *buffer, void *value );
void* ring_buffer_read( ring_buffer_t *buffer );



#endif

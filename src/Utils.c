#include "Utils.h"

void bitfield_set( bitfield_t *bf, uint16_t pos ){
	if( pos / 8 >= MAX_BITFIELD_SIZE ){ return; }
	
	BITARRAY_SET( bf->array, pos );
	}

void bitfield_unset( bitfield_t *bf, uint16_t pos ){
	if( pos / 8 >= MAX_BITFIELD_SIZE ){ return; }
	
	BITARRAY_UNSET( bf->array, pos );
	}

void bitfield_toggle( bitfield_t *bf, uint16_t pos ){
	if( pos / 8 >= MAX_BITFIELD_SIZE ){ return; }
	
	BITARRAY_TOGGLE( bf->array, pos );
	
	}
uint8_t bitfield_get( bitfield_t *bf, uint16_t pos ){
	if( pos / 8 >= MAX_BITFIELD_SIZE ){ return 0; }
	
	return BITARRAY_GET( bf->array, pos );
	
	}

void bitfield_clear( bitfield_t *bf ){
	uint16_t i;
	for( i = 0 ; i < MAX_BITFIELD_SIZE ; ++i ){
		bf->array[i] = 0;
		}
	
	}


void ring_buffer_init( ring_buffer_t *buffer ){
	bitfield_clear( &buffer->reserved );
	buffer->pos = 0;
	}


void ring_buffer_write( ring_buffer_t *buffer, void *value ){
	
	buffer->buffer[ buffer->pos ] = value;
	bitfield_set( &buffer->reserved, buffer->pos );
	buffer->pos = (buffer->pos + 1) % MAX_RING_BUFFER_SIZE;
	
	}

void* ring_buffer_read( ring_buffer_t *buffer ){
	uint16_t read_pos = (buffer->pos + 1) % MAX_RING_BUFFER_SIZE;
	if( !bitfield_get( &buffer->reserved, read_pos ) ){ return 0; }
	buffer->pos = read_pos;
	bitfield_unset( &buffer->reserved, read_pos );
	return buffer->buffer[ buffer->pos ];
	}


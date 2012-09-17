#include "Emulator.h"

device_t _emulator_portA, _emulator_portB;
device_t _emulator_usart;
device_t _emulator_ad;

uint8_t _emulator_inited = 0;

uint8_t _emulator_portA_values = 0;
uint8_t _emulator_portB_values = 0;

/*
 * Emulator protocol
 * 	command [1 byte] value[4 bytes]
 * 
 * 
 * */

void* _emulator_server_thread( void * arg ){
	int sockfd, fd, one = 1;
	socklen_t clilen;
	struct sockaddr_in serv_addr, cli_addr;
	unsigned char buffer[256];
	
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	memset( &serv_addr, 0, sizeof( struct sockaddr_in ) );
	
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(9123);
	
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof(one));
	
	bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr));
	
	listen(sockfd,5);
	clilen = sizeof(cli_addr);
	
	while( 1 ){
		fd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
		
		while( 1 ){
			memset( buffer, 0, 256 );
			read( fd, buffer, 5 );
			switch( buffer[0] ){
				case 0:
					{
						_emulator_portA_values = (uint8_t)buffer[1];
						}
				break;
				case 1:
					{
						_emulator_portB_values = (uint8_t)buffer[1];
						}
				break;
				case 2:
					{
						memset( buffer, 0, 256 );
						buffer[0] = 0;
						buffer[1] = _emulator_portA_values;
						write( fd, buffer, 5 );
						}
				break;

				case 3:
					{
						memset( buffer, 0, 256 );
						buffer[0] = 1;
						buffer[1] = _emulator_portB_values;
						write( fd, buffer, 5 );
						}
				break;
				}
				
			}
		
		
		}
	
	
	return NULL;
	}


void* _emulator_portA_read( void *pin, void *flag ){
	if( (int)flag == 0 ){
		return (void*)((_emulator_portA_values & ( 1 << (int)pin )) > 0);
		}
	else{
		return (void*)_emulator_portA_values;
		}
	
	return NULL;
	}

void* _emulator_portA_write( void *pin,  void *value ){
	if( (int)pin & 0xFF0 > 0 ){
		_emulator_portA_values = ((int)value) & 0xFF;
		}
	else {
			if( (int)value == 0 ){
				_emulator_portA_values &= ~(1<<(int)pin);
				}
			else {
				_emulator_portA_values |= (1<<(int)pin);
				}
		}
	return NULL;
	}


void* _emulator_portB_read( void *pin, void *flag ){
	if( (int)flag == 0 ){
		return (void*)((_emulator_portB_values & ( 1 << (int)pin )) > 0);
		}
	else{
		return (void*)_emulator_portB_values;
		}
	
	return NULL;
	}

void* _emulator_portB_write( void *pin,  void *value ){
	if( ((int)pin & 0xF00) > 0 ){
		_emulator_portB_values = ((int)value) & 0xFF;
		}
	else {
			if( (int)value == 0 ){
				_emulator_portB_values &= ~(1<<(int)pin);
				}
			else {
				_emulator_portB_values |= (1<<(int)pin);
				}
		}
	return NULL;
	}


void _emulator_init(){
	pthread_t thread;
	int rc;
	rc = pthread_create( &thread, NULL, &_emulator_server_thread, NULL );
	assert(0 == rc);
	_emulator_inited = 1;
	}

device_t* emulator_portA_init(){
	
	if( !_emulator_inited ){ _emulator_init(); }
	
	_emulator_portA.read = &_emulator_portA_read;
	_emulator_portA.write = &_emulator_portA_write;
	
	return &_emulator_portA;
	}

device_t* emulator_portB_init(){
	
	if( !_emulator_inited ){ _emulator_init(); }
	
	_emulator_portB.read = &_emulator_portB_read;
	_emulator_portB.write = &_emulator_portB_write;
	
	
	return &_emulator_portB;
	}



device_t* emulator_usart_init(){
	
	if( !_emulator_inited ){ _emulator_init(); }
	
	
	return &_emulator_usart;
	}

device_t* emulator_ad_init(){
	
	if( !_emulator_inited ){ _emulator_init(); }
	
	
	return &_emulator_ad;
	}

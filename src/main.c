#include <stdio.h>
#include <stdlib.h>


#include "EventEngine.h"
#include "WorkflowEngine.h"
#include "Emulator.h"

#include <time.h>

/*
void* wf_step1( void *engine, void *param ){
	int number;
	printf( "Give number: " );
	scanf( "%d", &number );
	return (void*)(number + (int)param);
	}

void* wf_step2( void *engine, void *param ){
	if( (int)param < 10 ){
		printf( "Currently sum is %d, needs to be over 10. \n", (int)param );
		workflow_repeat_last( (workflow_engine_t*)engine );
		return param;
		}
	printf( "Sum is %d \n", (int)param );
	return NULL;
	}
*/
int main( int argc, char **argv ){
	/*
	workflow_engine_t wf;

	workflow_init( &wf, 0 );
	
	workflow_add_step( &wf, &wf_step1 );
	workflow_add_step( &wf, &wf_step2 );
	
	while( workflow_running( &wf ) ){
		workflow_execute( &wf );
		}
	*/
	
	/*
	printf( "Size of EventEngine:    %d bytes \n", sizeof( event_engine_t ) );
	printf( "Size of WorkflowEngine: %d bytes \n", sizeof( workflow_engine_t ) );
	*/
	
	device_t *portA = emulator_portA_init();
	device_t *portB = emulator_portB_init();
	
	while( 1 ){
		int value = (int)portA->read( NULL, EMU_READ_ALL );
		printf( "%d \n", value ); 
		sleep( 1 );
		portB->write( EMU_WRITE_ALL, (int)(value + 1) );
		}
	
	
	return 0;
	}

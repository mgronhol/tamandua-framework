#ifndef _EVENT_ENGINE_H_
#define _EVENT_ENGINE_H_
#include <stdint.h>

#define MAX_DIFF_EVENTS 16
#define MAX_EVENT_QUEUE 16

typedef void* (*ee_callback)(void*);

typedef struct {
		
	ee_callback event_callbacks[MAX_DIFF_EVENTS];
	
	void* queue_args[MAX_EVENT_QUEUE];
	int16_t queue_events[MAX_EVENT_QUEUE];
	
	uint16_t queue_pos;
	
	} event_engine_t;


void engine_init( event_engine_t *engine );

void engine_add_event( event_engine_t *engine, uint16_t event_id, ee_callback cb );

void engine_queue_event( event_engine_t *engine, uint16_t event_id, void *arg );

void engine_fire_event( event_engine_t *engine, uint16_t event_id, void *arg );

void engine_run( event_engine_t *engine );


#endif

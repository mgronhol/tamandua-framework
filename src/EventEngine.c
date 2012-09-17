#include "EventEngine.h"

void engine_init( event_engine_t *engine ){
	uint16_t i;
	engine->queue_pos = 0;
	for( i = 0 ; i < MAX_EVENT_QUEUE ; ++i ){
		engine->queue_args[i] = 0;
		engine->queue_events[i] = -1;
		}
	}

void engine_add_event( event_engine_t *engine, uint16_t event_id, ee_callback cb ){
	engine->event_callbacks[event_id] = cb;
	}

void engine_queue_event( event_engine_t *engine, uint16_t event_id, void *arg ){
	engine->queue_args[ engine->queue_pos ] = arg;
	engine->queue_events[ engine->queue_pos ] = event_id;
	engine->queue_pos = (engine->queue_pos + 1) % MAX_EVENT_QUEUE;
	}

void engine_fire_event( event_engine_t *engine, uint16_t event_id, void *arg ){
	(engine->event_callbacks[ event_id ])( arg );
	}

void engine_run( event_engine_t *engine ){
	int16_t pos = engine->queue_pos;
	pos = (pos - 1) % MAX_EVENT_QUEUE;
	while( pos != engine->queue_pos && engine->queue_events[ pos ] >= 0 ){
		pos = (pos - 1) % MAX_EVENT_QUEUE;
		}
	if( engine->queue_events[ pos ] >= 0 ){
		engine->event_callbacks[ engine->queue_events[ pos ] ]( engine->queue_args[ pos ] );
		engine->queue_events[ pos ] = -1;
		}
	}

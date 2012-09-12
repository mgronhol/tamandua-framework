#ifndef _WORKFLOW_ENGINE_H_
#define _WORKFLOW_ENGINE_H_

#include <stdint.h>

#define MAX_WORKFLOW_STEPS 32


typedef void* (*we_callback)(void*, void*);


typedef struct {
	int16_t pos, next_pos, length;
	we_callback steps[MAX_WORKFLOW_STEPS];
	void *param;
	} workflow_engine_t;

void workflow_init( workflow_engine_t *flow, void *param );

void workflow_add_step( workflow_engine_t *flow, we_callback step );

void workflow_execute( workflow_engine_t *flow );

uint8_t workflow_running( workflow_engine_t *flow );

void workflow_stop( workflow_engine_t *flow );

void workflow_restart( workflow_engine_t *flow );

void workflow_skip_next( workflow_engine_t *flow );

void workflow_repeat( workflow_engine_t *flow );

void workflow_repeat_last( workflow_engine_t *flow );



#endif

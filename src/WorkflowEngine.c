#include "WorkflowEngine.h"


void workflow_init( workflow_engine_t *flow, void *param ){
	flow->pos = 0;
	flow->next_pos = 1;
	flow->length = 0;
	flow->param = param;
	}

void workflow_add_step( workflow_engine_t *flow, we_callback step ){
	if( flow->length >= MAX_WORKFLOW_STEPS ){ return; }
	flow->steps[flow->length] = step;
	flow->length += 1;
	}

void workflow_execute( workflow_engine_t *flow ){
	if( flow->pos >= flow->length ){ return; }
	if( flow->pos < 0 ){ flow->pos = 0; }
	flow->next_pos = flow->pos + 1;
	flow->param = (flow->steps[ flow->pos ])( flow, flow->param );
	flow->pos = flow->next_pos;
	}

uint8_t workflow_running( workflow_engine_t *flow ){
	return flow->pos < flow->length;
	}

void workflow_stop( workflow_engine_t *flow ){
	flow->next_pos = flow->length + 1;
	}

void workflow_restart( workflow_engine_t *flow ){
	flow->next_pos = 0;
	}

void workflow_skip_next( workflow_engine_t *flow ){
	flow->next_pos = flow->pos + 2;
	}

void workflow_repeat( workflow_engine_t *flow ){
	flow->next_pos = flow->pos;
	}

void workflow_repeat_last( workflow_engine_t *flow ){
	flow->next_pos = flow->pos - 1;
	}




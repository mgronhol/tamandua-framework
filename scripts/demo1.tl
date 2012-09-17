


// Events
events {
	
	EVENT_1 -> func1;

	EVENT_2 -> func2;

	EVENT_4 -> func3; // testing comments
	
	EVENT_3 -> func1;
	
	}



condition cond_1 {
	
	portA:pin1 rising;
	portA:pin2 high;
	
	}

condition cond_2 {
	
	portA:pin1 falling;
	portB:pin1 low;	

	}

condition cond_3 {
	
	portA:pin2 rising;
	portA:pin3 high;
	
	}


on cond_1 emit EVENT_1;
on cond_2 emit EVENT_2 EVENT_3;

on cond_3 emit EVENT_3;




workflow flow0 {
	step1 -> 
	step2 -> 
	step3 -> 
	step4 -> reset;
	}



configure {
	
	input {
		portA:pin1;
		portA:pin2;
		portA:pin3;
		portA:pin4;
		}
	
	output {
		
		portB:pin3;
		
		}
	
	peripherals {
		AD on;
		SPI on;
		}

	}


run {
	flow0;
	events;
	flow0;
	events;
	}




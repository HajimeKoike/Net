#include "Node_Dynamics.h"

void Node_Dynamics::step(){
	if(this->state==0){
		this->state=this->state+0;
		this->t=this->t+1;
	}else if(this->state==1){
		if(this->t==this->infectious_period){
			this->t=0;
		}
	}else{
		;
	}
}

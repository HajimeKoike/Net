#ifndef NODE_DYNAMICS_H
#define NODE_DYNAMICS_H

#include "com.h"

class Node_Dynamics: public Node{
	private:
		void step();
	public:
		int t;
		void run(int T,bool record){
			for(int t=0;t<T;t++){
				step();
			}
			this->t++;
		};	
}
#endif

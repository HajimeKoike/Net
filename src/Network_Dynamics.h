#ifndef NETWORK_DYNAMICS_H
#define NETWORK_DYNAMICS_H

#include "com.h"
#include "Network.h"

class Network_Dynamics{
	private:
		double recovering;
		void step();
	public:
		Network now;
		Network next;
		int t;
		Network_Dynamics(const Network& now): now(now),t(now.t),recovering(0.0) { }
		Network_Dynamics(const Network& now,const double& recovering): now(now),t(now.t),recovering(recovering) { }
		void run(int T, bool record){
			for(int t=0;t<T;t++){
				if(record==true){
					this->now.cout_state();
				}
				step();
			}
			this->now=this->next;
			this->t++;
		}
};

#endif

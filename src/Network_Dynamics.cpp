#include "Network_Dynamics.h"

void Network_Dynamics::step(){

//	std::cout<<"inside routine old"<<(this->now).t<<std::endl;

	//state & parameter update
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution<double> u(0.0,1.0);

	for(auto&& [node_id, node]: (this->now).nodes){
		//state update
		if(node.get_state()==0){
			for(const auto& nbd_id: node.get_adjacent()){
				if((this->now).nodes.at(nbd_id).get_state()>0){
					if(u(mt)<(this->now).nodes.at(nbd_id).get_transmission_power()){
						node.get_infected();
					}
				}
			}
		}else if(node.get_state()>0){
			node.step();
			//Recovering process
			/*
			if(u(mt)<this->recovering){
				node.set_state(-1);
			}
			*/
		}else{
			;
		}

		(this->next).nodes[node_id]=node;
		//parameter update
	}
	//structure update
	(this->next).set_adjacent((this->now).get_adjacent());
	(this->next).size=(this->now).get_size();
	(this->next).t=(this->now).t + 1;

//	std::cout<<"inside routine new"<<(this->next).t<<std::endl;
}	

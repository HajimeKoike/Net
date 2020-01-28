#ifndef NETWORK_H
#define NETWORK_H

#include "com.h"
#include "Node.h"

class Network{
	public:
		int t;
		int size;
		std::map<node_id,Node> nodes;

		Network(){;};
		Network(std::map<node_id,Node> nodes) :t(0), size(nodes.size()),nodes(nodes) { ; };
		Network(std::map<node_id,std::vector<node_id> > adjs):t(0),size(adjs.size()),adjs(adjs){
		for(auto& [node_id,adj]: adjs){
			Node node(node_id);
			assert(node.get_id()==node_id);
			node.set_adjacent(adjs.at(node_id));
			(this->nodes)[node_id]=node;
		}
	};
		Network(const Network& net): t(net.t),size(net.size),nodes(net.nodes), adjs(net.adjs) {
		};
		Network& operator=(const Network& net){ 
			if(this==&net){
				;
			}else{
				this->t=net.t;
				this->size=net.size;
				for(const auto& [id,node]: net.nodes){
					this->nodes[id]=node;
				}
				this->adjs=net.get_adjacent();
			}
			return *this;
		}
		~Network(){;};


		void set_parameter(std::map<node_id,double> transmission_power,std::map<node_id,int> infectious_period);//set each node's quantities
		void set_state(std::map<node_id,state_type> state); //set all states;
		void set_adjacent(std::map<node_id,std::vector<node_id> > adjs);

		int get_size() const { return this->size; }
		std::list<node_id> get_id() const;
		std::map<node_id,state_type> get_state() const;
		std::map<node_id,std::vector<node_id> > get_adjacent() const;

		void cout_id() const;
		void cout_state() const;
		void cout_adjacent() const;
		void cout_transmission_power() const;
		void cout_infectious_period() const;

		int count_S() const;
		//std::map<state_type,int> count_Infected() const;
		int count_I() const;
		int count_R() const;

	private: 
		std::map<node_id,std::vector<node_id> > adjs;

		std::map<int,int> degree_dist() const;
};
#endif

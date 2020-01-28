#include "Network.h"
/*
template <class Container>
std::ostream & display( const Container &container, 
                        const char *s = " ",
                        std::ostream &os = std::cout )
{
    for ( const auto &value : container )
    {
        os << value << s;
    }

    return os;
}
*/

/*
template <class container>
std::ostream& operator<<(std::ostream& os, const container& c)
{
    std::copy(c.begin(),
              c.end(),
              std::ostream_iterator<typename container::value_type>(os, ","));
    return os;
}
*/

void Network::set_parameter(std::map<node_id,double> transmission_power,std::map<node_id,int> infectious_period){
	for(auto&& [node_id,node]: this->nodes){
		node.set_transmission_power(transmission_power.at(node_id));
		node.set_infectious_period(infectious_period.at(node_id));
	}
}

void Network::set_state(std::map<node_id,state_type> state){
	for(auto&& [node_id,node]: this->nodes){
		node.set_state(state.at(node_id));
	}
}

void Network::set_adjacent(std::map<node_id,std::vector<node_id> > adjs){
	this->adjs=adjs;
	for(auto&& [node_id,node]: this->nodes){
		node.set_adjacent(adjs.at(node_id));
	}
}

std::list<node_id> Network::get_id() const {
	std::list<node_id> id_list;
	for(const auto& [node_id,node]: this->nodes){
		id_list.push_back(node_id);
	}
	return id_list;
}

std::map<node_id,state_type> Network::get_state() const {
	std::map<node_id,state_type> state;
	for(const auto& [node_id,node]: this->nodes){
		state[node_id]=node.get_state();
	}
	return state;
}

std::map<node_id,std::vector<node_id> > Network::get_adjacent() const {
	std::map<node_id,std::vector<node_id> > adjacent;
	for(const auto& [node_id,node]: this->nodes){
		adjacent[node_id]=node.get_adjacent();
	}
	return adjacent;
}

void Network::cout_id() const {
	std::cout<<"id of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_id();
	}
}

void Network::cout_state() const {
	auto&& itr=this->nodes.begin();
	for(;itr!=std::prev(this->nodes.end());++itr){
	(itr->second).cout_state();
	std::cout<<",";
	}
	(itr->second).cout_state();
	std::cout<<std::endl;
}
/*		
	int k=0;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_state();
		k++;
		if(k<this->size){
			std::cout<<",";
		}
	}
	std::cout<<std::endl;
}
*/

void Network::cout_adjacent() const {
	std::cout<<"adjacent nodes of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_adjacent();
	}
}

void Network::cout_transmission_power() const {
	std::cout<<"transmission power of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_transmission_power();		
	}
}

void Network::cout_infectious_period() const {
	std::cout<<"infectious period of each node"<<std::endl;
	for(const auto& [node_id,node]: this->nodes){
		node.cout_infectious_period();
	}
}

int Network::count_S() const {
	int s=0;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()==0){
			s++;
		}
	}
	return s;
}

/*
std::map<state_type,int> Network::count_I() const {
	std::map<int,int> i;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()>0){
			i[node.get_state()]+=1;
		}
	}
	return i;
}
*/

int Network::count_I() const {
	int i=0;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()==1){
			i++;
		}
	}
	return i;
}

int Network::count_R() const {
	int r=0;
	for(const auto& [node_id,node]: this->nodes){
		if(node.get_state()==-1){
			r++;
		}
	}
	return r;
}

std::map<int,int> Network::degree_dist() const {
	std::map<int,int> degree_dist;
	for(const auto& [node_id,node]: this->nodes){
		degree_dist[node.get_adjacent().size()]+=1;
	}
	return degree_dist;
}

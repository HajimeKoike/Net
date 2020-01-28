#include "error.h"

double rmse(const Network& n1,const Network& n2){
	double rmse=0.0;
	if(n1.size!=n2.size){
		std::cerr<<"size don't match "<<std::endl;
		std::exit(1);
	}
	int n=n1.size;
	for(const node_id& node_id: n1.get_id()){
		double diff=double(n2.nodes.at(node_id).get_state()-n1.nodes.at(node_id).get_state());
		if(diff==2){
			diff=1.0;
		}
		rmse+=diff*diff;
	}
	rmse=std::sqrt(rmse/double(n));
	return rmse;
}

double rmse(const std::vector<state_type> s1, const std::vector<state_type> s2){
	double rmse=0.0;
	assert(s1.size()==s2.size());
	for(int i=0;i<s1.size();i++){
		double diff=double(s1[i]-s2[i]);
		if(diff==2){
			diff=1.0;
		}
		rmse+=diff*diff;
	}
	rmse=std::sqrt(rmse/double(s1.size()));
	return rmse;
}

state_type add_error(state_type& state,const double& p){
	//add error by probability p(e.g.0.01)
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_real_distribution u(0.0,1.0);
	if(p<u(mt)){
		return state;
	}else{
		double rand(u(mt));
//		state=state+int((rand-0.5)/std::abs(rand-0.5));
		state=state+1;
		if(state>1){
			state=0;
		}else if(state<=-1){
			state=1;
		}
		return state;
	}	
}

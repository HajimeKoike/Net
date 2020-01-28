#include "Particles.h"

Particles::Particles(int size,Network analysis): size(size),id_list(analysis.get_id()),t(analysis.t){
	for(particle_id id=0;id<this->size;id++){
		this->analysis[id]=analysis;
		this->forecast_weight[id]=1.0/this->size;
	}
}

Particles::Particles(std::map<int,Network> analysis,std::map<int,double> weight): size(weight.size()),analysis(analysis),forecast_weight(weight){
}

void Particles::cout_likelihood() const {
	std::cout<<"likelihood"<<std::endl;
	for(const auto& [id,l]: this->likelihood){
		std::cout<<l<<" ";
	}
	std::cout<<std::endl;
}

void Particles::cout_forecast_weight() const {
	std::cout<<"forecast weight"<<std::endl;
	for(const auto& [id,weight]: this->forecast_weight){
		std::cout<<weight<<" ";
	}
	std::cout<<std::endl;
}

void Particles::cout_analysis_weight() const {
	std::cout<<"analysis weight"<<std::endl;
	for(const auto& [id,weight]: this->analysis_weight){
		std::cout<<weight<<" ";
	}
	std::cout<<std::endl;
}

void Particles::cout_state() const {
	for(const auto& [id,network]: this->forecast){
		network.cout_state();
	}
	std::cout<<std::endl;
}	

void Particles::normalize(std::map<int,double>& mp){
	double sum=std::accumulate(mp.begin(),mp.end(),0.0,[](double acc, std::pair<int,double> p){ return (acc+p.second); });
	for(auto&& [integer,element]: mp){
		element=element/sum;
	}
}

void Particles::calc_likelihood(const std::map<node_id,Node> y,const std::map<node_id,double> cent){
	std::cout<<"observe"<<std::endl;
	assert(!y.empty());
	for(const auto& [id,node]: y){
		std::cout<<node.get_state();
	}
	std::cout<<std::endl; 	
	std::map<particle_id,double> l;//size=m
	std::map<particle_id,double> d_net;//size=m
	for(const auto& [id,network] : this->forecast){
		std::map<particle_id,double> d;//size=obs_dim
		for(const auto& [obs_node_id,obs_node]: y){
			double dtmp=double(obs_node.get_state()-network.nodes.at(obs_node_id).get_state());
			if(dtmp==2.0){
				dtmp=1.0;
			}
			d[obs_node_id]=-0.5*dtmp*dtmp*cent.at(obs_node_id)/this->obs_error;
		}
		d_net[id]=std::accumulate(d.begin(),d.end(),0.0,[](double acc, std::pair<particle_id,double> p){ return (acc+p.second); });	
		d.clear();
	}
	double dmax=std::max_element(d_net.begin(),d_net.end(),[](std::pair<particle_id,double> p1,std::pair<particle_id,double> p2){ return p1.second<p2.second; })->second;
	for(const auto& [id,network]: this->forecast){
		d_net[id]-=dmax;
		l[id]=std::exp(d_net[id]);
	}
	normalize(l);
	this->likelihood=l;
}

void Particles::calc_analysis_weight(){
	for(auto&& [id,weight]: this->forecast_weight){
		this->analysis_weight[id]=this->likelihood[id]*weight;
	}
	normalize(this->analysis_weight);
}

void Particles::update(const std::map<node_id,Node> y,const double thres,const std::map<node_id,double> cent){
	assert(!this->forecast.empty());
//	std::cout<<this->t<<std::endl;
	this->likelihood.clear();
	this->analysis.clear();
	this->analysis_weight.clear();
/*
	for(const auto& [net_id,net]: this->forecast){
		net.cout_state();
	}
*/
	assert(!this->forecast.empty());
	calc_likelihood(y,cent);
//	cout_likelihood();
	//std::cin.get();	
	calc_analysis_weight();
//	cout_forecast_weight();
//	cout_analysis_weight();
	std::cout<<std::endl;
	std::cout<<Neff()<<std::endl;
	std::cout<<std::endl;
	bool condition=(Neff()<thres*this->size);
	if(condition){
		resample();
	}else{
		this->analysis=this->forecast;
	}
	this->t=this->t+1;
	std::cout<<this->t<<std::endl;
}

double Particles::Neff(){
	double neff_inv=std::accumulate(this->analysis_weight.begin(),this->analysis_weight.end(),0.0,[](double acc,std::pair<particle_id,double> pair){ return acc+pair.second*pair.second; });
	return 1.0/neff_inv;
}

void Particles::resample(){
	//based on my previous code. EDITED BY HAJIME KOIKE on 1st Dec.2019
	std::cout<<"resample start"<<std::endl;
	double ind=0.0;
	std::vector<double> cum_w(this->size);
	for(particle_id id=0;id<this->size;id++){
		if(id>0){
			cum_w.at(id)=cum_w.at(id-1)+this->analysis_weight.at(id);
		}else{
			cum_w.at(id)=this->analysis_weight.at(id);
		}
	}
	for(particle_id id=0;id<this->size;id++){
		ind+=1.0/(this->size+2);
		int k=0;
		if(ind==1.0){
			k=this->size-1;
		}else{
			while(cum_w.at(k)<=ind){
				k++;
			}
		}
		this->analysis[id]=this->forecast[k];
		this->analysis_weight[id]=1.0/this->size;
	}
}

Network Particles::get_analysis() const{
	std::map<node_id,Node> nodes;
	for(auto node_id: this->id_list){
		Node node(node_id);
		double state=0.0;
		double transmission_power=0.0;
		int infectious_period;

		for(particle_id id=0;id<this->size;id++){
			state+=this->analysis.at(id).nodes.at(node_id).get_state()*this->analysis_weight.at(id);
			transmission_power+=this->analysis.at(id).nodes.at(node_id).get_transmission_power()*this->analysis_weight.at(id);		
		}
		node.set_state(round(state));
		node.set_transmission_power(transmission_power);
		node.set_infectious_period(10);//adopt majority
		nodes[node_id]=node;
	}
	Network analysis(nodes);
	return analysis;
}


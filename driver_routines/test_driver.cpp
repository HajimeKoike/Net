#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "generate.h"
#include "Particles.h"
#include "error.h"

int main(){
	std::map<node_id,std::vector<node_id> > adjs;
	std::vector<std::vector<node_id> > adj{{1,2},{0,2},{0,1,3},{2}};

	adj_to_adjs(adj,adjs);

	adjs.clear();	
	int size=40;
	double p=0.3;
	int mean_degree=4;
	int new_add=2;
	std::vector<std::pair<int,int> > edges;
	ws(size,mean_degree,p,adjs);
	Network network(adjs);
	network.nodes[int(network.size/2)].get_infected();
	std::map<node_id,double> transmission_power;
	std::map<node_id,int> infectious_period;
	for(int k=0;k<adjs.size();k++){
		transmission_power[k]=0.3;
		infectious_period[k]=10;
	}
	network.set_parameter(transmission_power,infectious_period);


	int Tend=20;
	Particles nets(1000,network);


	Network_Dynamics networkdyn(network);
	std::map<node_id,Node> y;

	for(int t=0;t<Tend;t++){


		networkdyn.run(1,false);

		y.clear();
		
		double obs_error=0.1;
		for(int k=0;k<networkdyn.now.size;k+=1){
			Node obs(networkdyn.now.nodes[k]);
			state_type obs_state=obs.get_state();
			obs.set_state(add_error(obs_state,obs_error));
			y[k]=obs;

		}
		nets.set_obs_error(obs_error);


		for(auto&& [id,net]: nets.forecast){
			Network_Dynamics netdyn(net);
			netdyn.step();
			net=netdyn.next;
		}
		assert(!nets.forecast.empty());


		nets.update(y);

		Network anal=nets.get_analysis();

		std::cout<<t<<" "<<rmse(networkdyn.now,anal)<<" "<<nets.Neff()<<std::endl;
	}
		
	return 0;
}

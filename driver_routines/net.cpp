#include "com_driver.h"

#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "generate.h"

int main(){
	std::map<node_id,std::vector<node_id> > adjs;	
	std::ifstream fin(GRAPH_FILE);
	std::pair<node_id,node_id> edge;
	std::vector<std::pair<node_id,node_id> > edges;
	assert(!fin.fail());
	while(fin>>edge.first>>edge.second){
		edges.push_back(edge);
	}
	fin.close();

	edge_to_adj(edges,adjs);

	Network network(adjs);
	network.nodes[int(network.size/2)].get_infected();
	std::map<node_id,double> transmission_power;
	std::map<node_id,int> infectious_period;
	for(int k=0;k<adjs.size();k++){
		transmission_power[k]=0.3;
		infectious_period[k]=10;
	}
	network.set_parameter(transmission_power,infectious_period);

	std::cout<<"NETWORK_TEST"<<std::endl;
	std::cout<<"SIS dynamics"<<std::endl;

	//statistics
	std::ofstream sir_file("./test_sir.csv");
	
	std::ofstream fout("./test.csv");
	std::streambuf* strbuf;
	strbuf=std::cout.rdbuf(fout.rdbuf());

//	network.cout_adjacent();
	for(int i=0;i<40;i++) std::cout<<i<<",";
	std::cout<<std::endl;	

	Network_Dynamics netdyn(network,0.0);//0.0=recovering rate by vaccutintion
	int Tend=1000;
	bool record=true;
	netdyn.run(Tend,record);
	
	std::cout.rdbuf(strbuf);
	
	return 0;	
}

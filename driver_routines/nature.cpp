#include "com_driver.h"

#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "generate.h"

int main(){
	std::map<node_id,std::vector<node_id> > adjs;

	const std::string DATE_DIR_PATH = "presen/";//"27012020/";
	const std::string OUT_DIR_PATH = "../out/" + DATE_DIR_PATH;
	const std::string GRAPH_FILE = OUT_DIR_PATH + "ba.csv";
	std::ifstream fin(GRAPH_FILE);
	std::pair<node_id,node_id> edge;
	std::vector<std::pair<node_id,node_id> > edges;
	assert(!fin.fail());
	while(fin>>edge.first>>edge.second){
		edges.push_back(edge);
	}
	fin.close();
	edge_to_adj(edges,adjs);
	int i;
	for(i=0;i<1;i++){
		Network network(adjs);
		network.cout_adjacent();

		for(auto&& [id,node]: network.nodes){
			std::cout<<double(node.get_adjacent().size())/double(size)<<std::endl;
			node.set_transmission_power(double(node.get_adjacent().size())/double(size)); //influence to be proportional to degree
			node.set_infectious_period(infectious_period);
		}
		std::random_device rd;
		std::mt19937 mt(rd());
		std::uniform_int_distribution<> random(0,size-1);
		network.nodes[int(random(mt))].get_infected();
		std::cout<<network.size<<std::endl;

		Network_Dynamics netdyn(network,recovering);
		std::cout<<"ready"<<std::endl;
		const std::string NATURE_FILE = OUT_DIR_PATH + "nature.csv";
		std::cout<<NATURE_FILE<<std::endl;
		std::ofstream fout(NATURE_FILE);
		std::streambuf* strbuf;
		strbuf=std::cout.rdbuf(fout.rdbuf());

		netdyn.run(Tend,true);
		
		std::cout.rdbuf(strbuf);
		fout.close();
	}
	return 0;
}	

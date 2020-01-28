#include "com_driver.h"

#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "generate.h"

int main(){
        std::map<node_id,std::vector<node_id> > adjs;
	std::vector<std::vector<node_id> > adj{{1,2},{0,2},{0,1,3},{2}};

	adj_to_adjs(adj,adjs);

	//adjs.clear();	
	std::vector<std::pair<int,int> > edges;
	//ws(size,mean_degree,p_wire,adjs);
	ba(size,int(mean_degree/2),adjs);

	for(auto [node_id,adj]: adjs){
			for(auto nbd: adj){
				std::cout<<"nb "<<nbd;
			}
	}
    
	adj_to_edge(adjs,edges);
	const std::string DATE_DIR_PATH = "presen/"; //"27012020/";
	const std::string OUT_DIR_PATH = "../out/" + DATE_DIR_PATH;
	const std::string GRAPH_FILE = OUT_DIR_PATH + "ba.csv";
	std::ofstream fout(GRAPH_FILE);
	std::streambuf* strbuf;
	strbuf=std::cout.rdbuf(fout.rdbuf());
	for(auto [id1,id2]: edges){
			std::cout<<id1<<" "<<id2<<std::endl;
	}
	std::cout.rdbuf(strbuf);
        cout_edges(edges);

        return 0;
}

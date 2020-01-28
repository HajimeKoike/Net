#include "com_driver.h"

#include "com.h"
#include "generate.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"

#include "Particles.h"
int main(){

	/* Step 0. PATH */
	const std::string DATE_DIR_PATH = "presen/";//"obs/ba/1"; //"27012020/";
	const std::string OUT_DIR_PATH = "../out/" + DATE_DIR_PATH;
	/* Step 1. read network structure and construct particles*/
	const std::string GRAPH_FILE = OUT_DIR_PATH +"ba.csv"; //"ws.csv";
	std::ifstream graph_file(GRAPH_FILE);
	assert(!graph_file.fail());
	std::pair<node_id,node_id> edge;
	std::vector<std::pair<node_id,node_id> > edges;
	while(graph_file>>edge.first>>edge.second){
		edges.push_back(edge);
	}
	graph_file.close();
	std::map<node_id,std::vector<node_id> > adjs;
	edge_to_adj(edges,adjs);
	Network network(adjs);
	std::cout<<network.t<<std::endl;

	std::map<node_id,double> transmission_power;
	std::map<node_id,int> infectious_period;
	/* Step 1.5. set initial value*/
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution u(0,network.size-1);
	int size=500;
	std::vector<double> obserr_list({0.1,0.2});//,0.01,0.02,0.05,0.1,0.2,0.5});
	Particles nets(size,network);
	for(const auto& [id,net]: nets.analysis){
		std::cout<<net.t<<std::endl;
	}
	std::list<node_id> id_list = nets.id_list;
	for(auto&& [id,net]: nets.analysis){
		for (auto&& [node_id,node]: net.nodes){
			node.set_transmission_power(double(node.get_adjacent().size())/double(net.size));
			node.set_infectious_period(double(1)/double(recovering));
		}
		net.nodes[int(u(mt))].get_infected();
	}

	/* Step 2. DA cycle*/
	for(const auto OBS_ERROR: obserr_list){
		const std::string NATURE_FILE = OUT_DIR_PATH + "nature.csv";
		const std::string PARAM_DIR_PATH = std::to_string(int(OBS_ERROR*1000))+"/";
		const std::string OBS_FILE = OUT_DIR_PATH + PARAM_DIR_PATH + "obs.csv";
		std::cout<<"Working on "<<OBS_FILE<<std::endl;
		std::ifstream nature_file(NATURE_FILE);
		std::ifstream obs_file(OBS_FILE);
		assert(!nature_file.fail() && !obs_file.fail());
		std::string nature_tmp,obs_tmp;
		std::string nature_seq,obs_seq;
		std::string nature_str,obs_str;
		std::vector<state_type> nature;
		std::map<node_id,Node> obs;

		int Tend=99;

		std::map<node_id,Node> y;
		std::getline(nature_file,nature_tmp);
		std::cout<<"node_id,S,I,pf_state,nature,obs"<<std::endl;
		std::getline(obs_file,obs_tmp);
		for(int t=0;t<Tend;t++){
			const std::string PF_FILE = OUT_DIR_PATH + PARAM_DIR_PATH  + std::to_string(t) + "_cpf.csv";
			std::cout<<PF_FILE<<std::endl;
			std::ofstream fout(PF_FILE);
			std::cout<<"time step "<<t<<std::endl;
			fout<<"ID,S,I,State,Nature,Obs"<<std::endl;
			/* 1. reading data */
			nature.clear();
			obs.clear();
			std::getline(nature_file,nature_tmp);
			std::getline(obs_file,obs_tmp);
			std::stringstream nature_seq(nature_tmp);
			std::stringstream obs_seq(obs_tmp);
			while(std::getline(nature_seq,nature_str,',')){
				nature.push_back(std::stoi(nature_str));
			}
			
			int i=0;
			while(std::getline(obs_seq,obs_str,',')){
				Node node(i);
				obs[i]=node;
				obs[i].set_state(std::stoi(obs_str));
				i++;
			}

			/* 2. updating forecast */
			nets.set_obs_error(OBS_ERROR);
			for(auto&& [id,net]: nets.analysis){
				assert(&net==&nets.analysis.at(id)); 
				Network_Dynamics netdyn(net);
				netdyn.run(1,false);
				net=netdyn.next;
				nets.forecast[id]=net;
			}
			assert(!nets.forecast.empty());

			/* 3. updating by PF */
			//observation dependency
			std::string CENT_NAME = OUT_DIR_PATH+"cc.csv";
			std::ifstream centfile(CENT_NAME);
			assert(!centfile.fail());
			std::map<node_id,double> cent;
			std::pair<node_id,double> c;
			while(centfile>>c.first>>c.second){
				std::cout<<c.first<<","<<c.second<<std::endl;
				cent.insert(c);
			}
			nets.update(obs,0.5,cent);
			for(const auto& node_id: id_list){
				int s=0;
				int i=0;
				double ss;
				for(const auto& [net_id,net]: nets.analysis){
					state_type state = net.nodes.at(node_id).get_state();
					if(state==0){
						s+=1;//*nets.get_analysis_weight()[net_id];
					}else if(state==1){
						i+=1;//*nets.get_analysis_weight()[net_id];
					}
				}
				if(s>i){
					ss=0;
				}else if(s<i){
					ss=1;
				}else{
					ss=0.5;
				}
				fout<<node_id<<","<<s<<","<<i<<","<<ss<<","<<nature[node_id]<<","<<obs[node_id].get_state()<<std::endl;
			}
			fout.close();
		}
		nature_file.close();
		obs_file.close();
			
	}

	return 0;
}

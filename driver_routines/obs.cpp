#include "com_driver.h"

#include "com.h"
#include "Node.h"
#include "Network.h"
#include "Network_Dynamics.h"
#include "error.h"

int main(){
	for(int i=0;i<1;i++){
	const std::string DATE_DIR_PATH = "presen/";//"27012020/";
	const std::string OUT_DIR_PATH = "../out/" + DATE_DIR_PATH;

	std::cout<<"NETWORK OBS"<<std::endl;
	std::cout<<"STATE"<<std::endl;
	state_type state_int;
	int obs_size=40;
	std::string state_string;
	std::string state;
	std::vector<state_type> nature;
	std::vector<state_type> obs;
	std::vector<double> obserr_list({0.1,0.2});//({0.005,0.01,0.02,0.05,0.1,0.2,0.5});
	for(const auto OBS_ERROR: obserr_list){
		const std::string PARAM_DIR_PATH = std::to_string(int(OBS_ERROR*1000))+"/";
		const std::string OBS_FILE = OUT_DIR_PATH + PARAM_DIR_PATH + "obs.csv";
		const std::string NATURE_FILE = OUT_DIR_PATH + "nature.csv";
		std::ifstream fin(NATURE_FILE);
		assert(!fin.fail());
		std::cout<<OBS_FILE<<std::endl;
		std::cin.get();
		std::ofstream fout(OBS_FILE);
		assert(!fout.fail());
		while(std::getline(fin,state_string)){
			nature.clear();
			obs.clear();
			std::cout<<state_string<<std::endl;
			std::stringstream state_seq(state_string);
			while(std::getline(state_seq,state,',')){
				state_int=std::stoi(state);
				nature.push_back(state_int);	
				obs.push_back(add_error(state_int,OBS_ERROR));
			}
			for(const auto state_int: nature){
				std::cout<<state_int;
			}
			std::cout<<std::endl;
			int k=0;
			for(const auto obs_int: obs){
				fout<<obs_int;
				k++;
				if(k<obs_size){
					fout<<",";
				}
			}
			fout<<std::endl;
		}
		fin.close();
		fout.close();
		}
	}
	return 0;
}

#include "agg.h"
#include <string>
#include <sstream>
#include <fstream>

int main(){
	for(int i=0;i<1000;i++){
		std::string finname=std::to_string(i)+"obs.csv";
		std::ifstream fin(finname);
		assert(!fin.fail());
		std::string foutname=std::to_string(i)+"obsagg.csv";
		std::ofstream fout(foutname);

		int state_int;
		std::string state_string;
		std::string state;
		std::vector<int> nature;
		fout<<"time,S,I,R"<<std::endl;
		int t=0;
		while(std::getline(fin,state_string)){
			nature.clear();
			std::cout<<state_string<<std::endl;
			std::stringstream state_seq(state_string);
			while(std::getline(state_seq,state,',')){
				state_int=std::stoi(state);
				nature.push_back(state_int);	
			}
			int s,i,r;
			s=s_count(nature);
			i=i_count(nature);
			r=r_count(nature);
			fout<<t<<","<<s<<","<<i<<","<<r<<std::endl;
			t=t+1;
		}
		fin.close();
		fout.close();
	}
	return 0;
}

#include "agg.h"

int s_count(std::vector<int> vec){
	int s=0;
	for(auto elem: vec){
		if(elem==0){
			s+=1;
		}
	}
	return s;
}

int i_count(std::vector<int> vec){
	int i=0;
	for(auto elem: vec){
		if(elem==1){
			i+=1;
		}
	}
	return i;
}

int r_count(std::vector<int> vec){
	int r=0;
	for(auto elem: vec){
		if(elem==-1){
			r+=1;
		}
	}
	return r;
}

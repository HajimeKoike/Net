#ifndef ERROR_H
#define ERROR_H

#include "com.h"
#include "Node.h"
#include "Network.h"

double rmse(const Network& n1,const Network& n2);
double rmse(const std::vector<state_type> s1, const std::vector<state_type> s2);
state_type add_error(state_type& state,const double& p);


#endif

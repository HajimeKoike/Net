#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <random>
#include <map>
#include <fstream>
#include <numeric>
#include <cassert>
#include <boost/numeric/odeint.hpp>
#include <string>
#include <sstream>

#ifndef ID_TYPE
#define ID_TYPE
using node_id = int;
using particle_id = int;
using state_type = int;
#endif

#ifndef PARTICLES_H
#define PARTICLES_H

#include "com.h"
#include "Node.h"
#include "Network.h"
#include "error.h"

class Particles{
	public:
		int size;
		std::list<node_id> id_list;
		std::map<particle_id,Network> forecast;
		std::map<particle_id,Network> analysis;
		int t;

		Particles(int size, Network analysis);
		Particles(std::map<particle_id,Network> analysis,std::map<particle_id,double> analysis_weight);

		void set_id_list(const std::list<node_id> id_list){ this->id_list = id_list;};
		void set_obs_error(const double& obs_error) {this->obs_error=obs_error;};//globally defined constant obs_error on "./driver_routines/com_driver.h"
		std::map<particle_id,double> get_likelihood() const {return this->likelihood;};
		std::map<particle_id,double> get_forecast_weight() const { return this->forecast_weight;};
		std::map<particle_id,double> get_analysis_weight() const { return this->analysis_weight;};
		void cout_likelihood() const;
		void cout_forecast_weight() const;
		void cout_analysis_weight() const;
		void cout_state() const;
		Network get_analysis() const;
		//std::vector<double> get_analysis() const;

		void update(const std::map<node_id,Node> y,const double thres,const std::map<node_id,double> cent);
		//void update(std::vector<double> agg);
		double Neff();
		void resample();

	private:
		double obs_error;
		std::map<particle_id,double> forecast_weight;
		std::map<particle_id,double> likelihood;
		std::map<particle_id,double> analysis_weight;
		void normalize(std::map<particle_id,double>& mp);
		void calc_likelihood(const std::map<node_id,Node> y,const std::map<node_id,double> cent);
		//void calc_likelihood(const std::vector<double> agg);
		void calc_analysis_weight();
	
};
#endif

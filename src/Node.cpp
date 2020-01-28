#include "Node.h"

void Node::set_state(const state_type state){
	this->state=state;
}

void Node::set_transmission_power(const double transmission_power){
	this->transmission_power=transmission_power;
}

void Node::set_infectious_period(const int infectious_period){
	this->infectious_period=infectious_period;
}

void Node::set_adjacent(const std::vector<node_id> adj){
	this->adj=adj;
}

node_id Node::get_id() const {
	return this->id;
}

state_type Node::get_state() const {
	return this->state;
}

double Node::get_transmission_power() const {
	return this->transmission_power;
}

int Node::get_infectious_period() const {
	return this->infectious_period;
}

std::vector<node_id> Node::get_adjacent() const {
	return this->adj;
}

void Node::cout_id() const {
	std::cout<<this->id<<std::endl;
}

void Node::cout_state() const {
		std::cout<<this->state;
}

void Node::cout_adjacent() const {
	std::cout<<this->id;
	for(const auto& id: this->adj){
		std::cout<<" "<<id;
	}
	std::cout<<std::endl;
}

void Node::cout_transmission_power() const {
	std::cout<<this->transmission_power<<std::endl;
}

void Node::cout_infectious_period() const {
	std::cout<<this->infectious_period<<std::endl;
}

void Node::get_infected(){
	this->state=1;
	this->t=1;
}

void Node::step(){
	if(this->state!=-1 && this->state!=0){
		this->state=this->state+0;//+1;
		this->t=this->t+1;
		
		if(this->t==this->infectious_period){
			this->state=0;//-1;
		}
		
	}
}

#include "group.hpp"

#include <iostream>
#include <cstdlib>
#include <climits>
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

/* public */
Group::Group(int size): _population(size) {
	indivs = new Individual[_population];
	_bestIndivIndex = -1;
	_bestDiameter = INF_DIAMETER;
	_bestAspl     = INF_ASPL;
	_averageAspl  = INF_ASPL;
	_worstAspl    = INF_ASPL;
	_indivVariation = -1;
}

Group::Group(const Group& obj): _population(obj._population) {
	indivs = new Individual[_population];
	*this = obj;
}

Group::Group(Group&& obj): _population(obj._population) {
	*this = std::move(obj);
}

Group::~Group() {
	if(indivs != nullptr) delete[] indivs;
}

Group& Group::operator=(const Group& obj) {
	if(this->_population != obj._population) {
		this->_population = obj._population;

		delete[] this->indivs;
		this->indivs = new Individual[obj._population];
	}

	for(int i = 0; i < this->_population; ++i) {
		this->indivs[i] = obj.indivs[i];
	}

	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;
	return *this;
}

void Group::operator=(Group&& obj) {
	this->indivs          = obj.indivs;
	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;

	obj.indivs = nullptr;
}

/// @brief 集団内の最良直径, 最良ASPL, 平均ASPL, 最悪ASPLを探索
void Group::tally() {
	int best = 0;
	for(int i = 1; i < this->population(); ++i) {
		if(indivs[i].betterThan(indivs[best])) best = i;
	}

	int worst = 0;
	for(int i = 1; i < this->population(); ++i) {
		if(indivs[i].worseThan(indivs[worst])) worst = i;
	}

	double sumAspl = 0;
	for(int i = 0; i < this->population(); ++i) {
		sumAspl += indivs[i].aspl();
	}

	this->_bestIndivIndex = best;
	this->_bestDiameter = indivs[best].diameter();
	this->_bestAspl     = indivs[best].aspl();
	this->_worstAspl    = indivs[worst].aspl();
	this->_averageAspl  = sumAspl / this->population();
	this->_indivVariation = countIndivVariation();
}

int Group::countIndivVariation() const {
	int variation = 0;
	for(int i = 0; i < _population; ++i) {

		bool duplicate = false;
		for(int j = 0; j < i; ++j) {
			if(indivs[i].matchGraph(indivs[j])) {
				duplicate = true;
				break;
			}
		}

		if(!duplicate) variation++;
	}
	return variation;
}

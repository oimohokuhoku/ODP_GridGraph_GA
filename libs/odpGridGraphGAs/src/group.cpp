#include "group.hpp"
#include <iostream>
#include <cstdlib>
#include <climits>
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;

/* public */
Group::Group(int size): _population(size) {
	_indivs = new GridGraph[_population];
	_bestIndivIndex = -1;
	_bestDiameter = INF_DIAMETER;
	_bestAspl     = INF_ASPL;
	_averageAspl  = INF_ASPL;
	_worstAspl    = INF_ASPL;
	_indivVariation = -1;
}

Group::Group(const Group& obj): _population(obj._population) {
	_indivs = new GridGraph[_population];
	*this = obj;
}

Group::Group(Group&& obj): _population(obj._population) {
	*this = std::move(obj);
}

Group::~Group() {
	if(_indivs != nullptr) delete[] _indivs;
}

Group& Group::operator=(const Group& obj) {
	if(this->_population != obj._population) {
		this->_population = obj._population;

		delete[] this->_indivs;
		this->_indivs = new GridGraph[obj._population];
	}

	for(int i = 0; i < this->_population; ++i) {
		this->_indivs[i] = obj._indivs[i];
	}

	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;
	return *this;
}

Group& Group::operator=(Group&& obj) {
	this->_indivs          = obj._indivs;
	this->_population     = obj._population;
	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;

	obj._indivs = nullptr;

	return *this;
}

GridGraph& Group::operator[](int index) {
	return _indivs[index];
}

const GridGraph& Group::operator[](int index) const {
	return _indivs[index];
}

/// @brief 集団内の最良直径, 最良ASPL, 平均ASPL, 最悪ASPLを探索
void Group::tally() {
	int best = 0;
	for(int i = 1; i < this->population(); ++i) {
		if(_indivs[i].betterThan(_indivs[best])) best = i;
	}

	int worst = 0;
	for(int i = 1; i < this->population(); ++i) {
		if(_indivs[i].worseThan(_indivs[worst])) worst = i;
	}

	double sumAspl = 0;
	for(int i = 0; i < this->population(); ++i) {
		sumAspl += _indivs[i].aspl();
	}

	this->_bestIndivIndex = best;
	this->_bestDiameter = _indivs[best].diameter();
	this->_bestAspl     = _indivs[best].aspl();
	this->_worstAspl    = _indivs[worst].aspl();
	this->_averageAspl  = sumAspl / this->population();
	this->_indivVariation = countIndivVariation();
}

const GridGraph& Group::bestIndiv() const {
	return _indivs[_bestIndivIndex];
}

int Group::countIndivVariation() const {
	int variation = 0;
	for(int i = 0; i < _population; ++i) {

		bool duplicate = false;
		for(int j = 0; j < i; ++j) {
			if(_indivs[i].matchGraph(_indivs[j])) {
				duplicate = true;
				break;
			}
		}

		if(!duplicate) variation++;
	}
	return variation;
}

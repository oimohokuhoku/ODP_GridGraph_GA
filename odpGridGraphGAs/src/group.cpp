#include "group.hpp"

#include <iostream>
#include <cstdlib>
#include <climits>
#include "odpGridGraphs/include/gridGraphs.hpp"
#include "commonLib/collections/dynamicArray.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using Collections::DynamicArray;

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
	DynamicArray<Individual>::safetyDeleteArray(indivs);
}

Group& Group::operator=(const Group& obj) {
	DynamicArray<Individual>::copy(obj.indivs, this->indivs, _population);
	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;
	return *this;
}

Group& Group::operator=(Group&& obj) {
	DynamicArray<Individual>::safetyDeleteArray(this->indivs);
	this->indivs          = obj.indivs;
	this->_bestIndivIndex = obj._bestIndivIndex;
	this->_averageAspl    = obj._averageAspl;
	this->_worstAspl      = obj._worstAspl;
	this->_indivVariation = obj._indivVariation;

	obj.indivs = nullptr;

	return *this;
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

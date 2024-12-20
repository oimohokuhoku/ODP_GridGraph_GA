#include "group.hpp"
#include <iostream>
#include <cstdlib>
#include <climits>
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::optional;

/* public */
Group::Group(int size) : 
	_population(size),
	_indivs(new optional<GridGraph>[size]),
	_bestIndivIndex(_UNCALCULATED),
	_worstIndivIndex(_UNCALCULATED),
	_averageDiameter(_UNCALCULATED),
	_averageAspl(_UNCALCULATED),
	_indivVariation(_UNCALCULATED)
{
	for(int i = 0; i < size; ++i) {
		_indivs[i] = std::nullopt;
	}
}

Group::Group(const Group& obj): _population(obj._population) {
	_indivs = new optional<GridGraph>[_population];
	*this = obj;
}

Group::Group(Group&& obj): _population(obj._population) {
	*this = std::move(obj);
}

Group::~Group() {
	if(_indivs != nullptr) {
		delete[] _indivs;
		_indivs = nullptr;
	}
}

Group& Group::operator=(const Group& rhs) {
	if(this->_population != rhs._population) {
		std::cerr << "Cannot substitute group with difference population" << std::endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 0; i < this->_population; ++i) {
		this->_indivs[i] = rhs._indivs[i];
	}

	this->_bestIndivIndex  = rhs._bestIndivIndex;
	this->_worstIndivIndex = rhs._worstIndivIndex;
	this->_averageDiameter = rhs._averageDiameter;
	this->_averageAspl     = rhs._averageAspl;
	this->_indivVariation  = rhs._indivVariation;
	
	return *this;
}

Group& Group::operator=(Group&& rhs) {
	if(this->_population != rhs._population) {
		std::cerr << "Cannot substitute group with difference population" << std::endl;
		exit(EXIT_FAILURE);
	}

	this->_indivs          = rhs._indivs;
	this->_bestIndivIndex  = rhs._bestIndivIndex;
	this->_worstIndivIndex = rhs._worstIndivIndex;
	this->_averageDiameter = rhs._averageDiameter;
	this->_averageAspl     = rhs._averageAspl;
	this->_indivVariation  = rhs._indivVariation;

	rhs._indivs = nullptr;

	return *this;
}

std::optional<GridGraph>& Group::operator[](int index) {
	_bestIndivIndex  = _UNCALCULATED;
	_worstIndivIndex = _UNCALCULATED;
	_averageAspl     = _UNCALCULATED;
	_averageDiameter = _UNCALCULATED;
	_indivVariation  = _UNCALCULATED;

	if(_indivs[index].has_value() && _indivs[index]->adjacent == nullptr) {
		_indivs[index] = std::nullopt;
	}

	return _indivs[index];
}

const std::optional<GridGraph>& Group::operator[](int index) const {
	if(!_indivs[index]) {
		std::cerr << "Group[" << index << "] is empty object." << std::endl;
		exit(EXIT_FAILURE);
	}

	if(_indivs[index].has_value() && _indivs[index]->adjacent == nullptr) {
		_indivs[index] = std::nullopt;
	}
	
	return _indivs[index];
}

const GridGraph& Group::bestIndiv() const {
	if(_bestIndivIndex == _UNCALCULATED) _bestIndivIndex = findBestIndivIndex();
	return *(_indivs[_bestIndivIndex]);
}

int Group::bestDiameter() const {
	if(_bestIndivIndex == _UNCALCULATED) _bestIndivIndex = findBestIndivIndex();
	return _indivs[_bestIndivIndex]->diameter();
}

int Group::worstDiameter() const {
	if(_worstIndivIndex == _UNCALCULATED) _worstIndivIndex = findWorstIndivIndex();
	return _indivs[_worstIndivIndex]->diameter();
}

double Group::averageDiameter() const {
	if(_averageDiameter == _UNCALCULATED) _averageDiameter = calcAverageDiameter();
	return _averageDiameter;
}

double Group::bestAspl() const {
	if(_bestIndivIndex == _UNCALCULATED) _bestIndivIndex = findBestIndivIndex();
	return _indivs[_bestIndivIndex]->aspl();
}

double Group::worstAspl() const {
	if(_worstIndivIndex == _UNCALCULATED) _worstIndivIndex = findWorstIndivIndex();
	return _indivs[_worstIndivIndex]->aspl();
}

double Group::averageAspl() const {
	if(_averageAspl == _UNCALCULATED) _averageAspl = calcAverageAspl();
	return _averageAspl;
}

int Group::indivVariation() const {
	if(_indivVariation == _UNCALCULATED) _indivVariation = countIndivVariation();
	return _indivVariation;
}

/* private */
int Group::findBestIndivIndex() const {
	int firstValidIndex = -1;
	for(int i = 0; i < this->population(); ++i) {
		if(_indivs[i]) {
			firstValidIndex = i;
			break;
		}
	}

	if(firstValidIndex == -1) {
		std::cerr << "Failed to find best graph because Group has no instances." << std::endl;
		exit(EXIT_FAILURE);
	}

	int bestIndex = firstValidIndex;
	for(int i = firstValidIndex + 1; i < this->population(); ++i) {
		if(!_indivs[i]) continue;
		if(_indivs[i]->betterThan(*(_indivs[bestIndex]))) bestIndex = i;
	}

	return bestIndex;
}

int Group::findWorstIndivIndex() const {
	int firstValidIndex = -1;
	for(int i = 0; i < this->population(); ++i) {
		if(_indivs[i]) {
			firstValidIndex = i;
			break;
		}
	}

	if(firstValidIndex == -1) {
		std::cerr << "Failed to find worst graph because Group has no instances." << std::endl;
		exit(EXIT_FAILURE);
	}

	int worstIndex = firstValidIndex;
	for(int i = firstValidIndex + 1; i < this->population(); ++i) {
		if(!_indivs[i]) continue;
		if(_indivs[i]->worseThan(*(_indivs[worstIndex]))) worstIndex = i;
	}

	return worstIndex;

}

double Group::calcAverageAspl() const {
	double sumAspl = 0;
	int numIndiv = 0;
	for(int i = 0; i < this->population(); ++i) {
		if(!_indivs[i]) continue;
		sumAspl += _indivs[i]->aspl();
		numIndiv++;
	}
	return sumAspl / static_cast<double>(numIndiv);
}

double Group::calcAverageDiameter() const {
	int sumDiam = 0;
	int numIndiv = 0;
	for(int i = 0; i < this->population(); ++i) {
		if(!_indivs[i]) continue;
		sumDiam += _indivs[i]->diameter();
		numIndiv++;
	}
	return static_cast<double>(sumDiam) / static_cast<double>(numIndiv);
}

int Group::countIndivVariation() const {
	int variation = 0;
	for(int i = 0; i < _population; ++i) {
		if(!_indivs[i]) continue;

		bool duplicate = false;
		for(int j = 0; j < i; ++j) {
			if(!_indivs[j]) continue;
			if(_indivs[i]->matchGraph(*(_indivs[j]))) {
				duplicate = true;
				break;
			}
		}

		if(!duplicate) variation++;
	}
	return variation;
}

#include "group.hpp"
#include <iostream>
#include <cstdlib>
#include <climits>
#include "odpGridGraphs.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::optional;

/* public */
Group::Group(int population) : 
	_population(population),
	_indivs(new optional<GridGraph>[population]),
	_bestIndivIndexCache(_UNCALCULATED),
	_worstIndivIndexCache(_UNCALCULATED),
	_averageDiameterCache(_UNCALCULATED),
	_averageAsplCache(_UNCALCULATED),
	_indivVariationCache(_UNCALCULATED) 
{
	for(int i = 0; i < population; ++i) _indivs[i] = std::nullopt;
}

Group::Group(const Group& obj) : 
	_population(obj._population),
	_indivs(new optional<GridGraph>[obj._population])
{
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
	if(this->_population != rhs._population) throw std::invalid_argument("Cannot substitute group with difference population");

	for(int i = 0; i < this->_population; ++i) {
		this->_indivs[i] = rhs._indivs[i];
	}
	this->_bestIndivIndexCache  = rhs._bestIndivIndexCache;
	this->_worstIndivIndexCache = rhs._worstIndivIndexCache;
	this->_averageDiameterCache = rhs._averageDiameterCache;
	this->_averageAsplCache     = rhs._averageAsplCache;
	this->_indivVariationCache  = rhs._indivVariationCache;
	
	return *this;
}

Group& Group::operator=(Group&& rhs) {
	if(this->_population != rhs._population) throw std::invalid_argument("Cannot substitute group with difference population");

	this->_indivs          = rhs._indivs;
	this->_bestIndivIndexCache  = rhs._bestIndivIndexCache;
	this->_worstIndivIndexCache = rhs._worstIndivIndexCache;
	this->_averageDiameterCache = rhs._averageDiameterCache;
	this->_averageAsplCache     = rhs._averageAsplCache;
	this->_indivVariationCache  = rhs._indivVariationCache;

	rhs._indivs = nullptr;

	return *this;
}

optional<GridGraph>& Group::operator[](int index) {
	if(index < 0 || _population <= index) throw std::out_of_range("Index out of range");

	// If _indivs[index] is empty object for std::move()
	if(_indivs[index].has_value()) {
		if(!_indivs[index]->isValidObject()) _indivs[index] = std::nullopt;
	}
	
	this->_bestIndivIndexCache  = _UNCALCULATED;
	this->_worstIndivIndexCache = _UNCALCULATED;
	this->_averageDiameterCache = _UNCALCULATED;
	this->_averageAsplCache     = _UNCALCULATED;
	this->_indivVariationCache  = _UNCALCULATED;
	return _indivs[index];
}

const std::optional<GridGraph>& Group::operator[](int index) const {
	if(index < 0 || _population <= index) throw std::out_of_range("Index out of range");
	if(!_indivs[index]) throw std::invalid_argument("Group[" + std::to_string(index) + "] is empty object.");
	
	return _indivs[index];
}

std::optional<GridGraph>& Group::get(int index) {
	return (*this)[index];
}

const std::optional<GridGraph>& Group::get(int index) const {
	return (*this)[index];
}

const GridGraph& Group::bestIndiv() const {
	if(_bestIndivIndexCache == _UNCALCULATED) _bestIndivIndexCache = findBestIndivIndex();
	return *(_indivs[_bestIndivIndexCache]);
}

int Group::bestDiameter() const {
	if(_bestIndivIndexCache == _UNCALCULATED) _bestIndivIndexCache = findBestIndivIndex();
	return _indivs[_bestIndivIndexCache]->computeDiameter();
}

int Group::worstDiameter() const {
	if(_worstIndivIndexCache == _UNCALCULATED) _worstIndivIndexCache = findWorstIndivIndex();
	return _indivs[_worstIndivIndexCache]->computeDiameter();
}

double Group::averageDiameter() const {
	if(_averageDiameterCache == _UNCALCULATED) _averageDiameterCache = calcAverageDiameter();
	return _averageDiameterCache;
}

double Group::bestAspl() const {
	if(_bestIndivIndexCache == _UNCALCULATED) _bestIndivIndexCache = findBestIndivIndex();
	return _indivs[_bestIndivIndexCache]->computeAspl();
}

double Group::worstAspl() const {
	if(_worstIndivIndexCache == _UNCALCULATED) _worstIndivIndexCache = findWorstIndivIndex();
	return _indivs[_worstIndivIndexCache]->computeAspl();
}

double Group::averageAspl() const {
	if(_averageAsplCache == _UNCALCULATED) _averageAsplCache = calcAverageAspl();
	return _averageAsplCache;
}

int Group::indivVariation() const {
	if(_indivVariationCache == _UNCALCULATED) _indivVariationCache = countIndivVariation();
	return _indivVariationCache;
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
		sumAspl += _indivs[i]->computeAspl();
		numIndiv++;
	}
	return sumAspl / static_cast<double>(numIndiv);
}

double Group::calcAverageDiameter() const {
	int sumDiam = 0;
	int numIndiv = 0;
	for(int i = 0; i < this->population(); ++i) {
		if(!_indivs[i]) continue;
		sumDiam += _indivs[i]->computeDiameter();
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

#include "embeddMap.hpp"
#include <utility>
#include <iostream>
#include <vector>
using namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers;

EmbeddMap::EmbeddMap(int numRow, int numColumn) :
    _numRow(numRow),
    _numColumn(numColumn),
    _numNode(numRow * numColumn),
    _mapData(new bool[_numNode])
{
    for(int i = 0; i < _numNode; ++i) {
        _mapData[i] = false;
    }
}

EmbeddMap::EmbeddMap(const EmbeddMap& obj) :
    _numRow(obj._numRow),
    _numColumn(obj._numColumn),
    _numNode(obj._numRow * obj._numColumn),
    _mapData(new bool[_numNode])
{
    *this = obj;
}

EmbeddMap::EmbeddMap(EmbeddMap&& obj) :
    _numRow(obj._numRow),
    _numColumn(obj._numColumn),
    _numNode(obj._numRow * obj._numColumn),
    _mapData(nullptr)
{
    *this = std::move(obj);
}

 EmbeddMap::~EmbeddMap() {
    if(_mapData != nullptr) {
        delete[] _mapData;
        _mapData = nullptr;
    }
 }

void EmbeddMap::operator=(const EmbeddMap& obj) {
    for(int i = 0; i < _numNode; ++i) {
        _mapData[i] = obj._mapData[i];
    }
}

void EmbeddMap::operator=(EmbeddMap&& obj) {
    this->_mapData = obj._mapData;
    obj._mapData = nullptr;
}

bool EmbeddMap::at(int index) const {
    return _mapData[index];
}

bool EmbeddMap::at(int rowIndex, int columnIndex) const {
    return _mapData[toNodeIndex(rowIndex, columnIndex)];
}

void EmbeddMap::set(int index, bool value) {
    _mapData[index] = value;
}

void EmbeddMap::set(int rowIndex, int columnIndex, bool value) {
    _mapData[toNodeIndex(rowIndex, columnIndex)] = value;
}

EmbeddMap EmbeddMap::overlay(const EmbeddMap& embeddMap) const {
    EmbeddMap result(_numRow, _numColumn);
    for(int i = 0; i < _numNode; ++i) {
        result._mapData[i] = this->_mapData[i] | embeddMap._mapData[i];
    }
    return result;
}

std::vector<bool> EmbeddMap::borderNeighborMap(int neighborRange) const {
    std::vector<bool> borderNeighbor(_numNode, false);

    for(int r = 0; r < _numRow - neighborRange; ++r) {
        for(int c = 0; c < _numColumn; ++c) {
            if(this->at(r, c) != this->at(r + neighborRange, c)) {
                borderNeighbor[toNodeIndex(r, c)] = true;
            }
        }
    }

    for(int r = neighborRange; r < _numRow; ++r) {
        for(int c = 0; c < _numColumn; ++c) {
            if(this->at(r, c) != this->at(r - neighborRange, c)) {
                borderNeighbor[toNodeIndex(r, c)] = true;
            }
        }
    }

    for(int r = 0; r < _numRow; ++r) {
        for(int c = 0; c < _numColumn - neighborRange; ++c) {
            if(this->at(r, c) != this->at(r, c + neighborRange)) {
                borderNeighbor[toNodeIndex(r, c)] = true;
            }
        }
    }

    for(int r = 0; r < _numRow; ++r) {
        for(int c = neighborRange; c < _numColumn; ++c) {
            if(this->at(r, c) != this->at(r, c - neighborRange)) {
                borderNeighbor[toNodeIndex(r, c)] = true;
            }
        }
    }

    return borderNeighbor;
}

void EmbeddMap::showMap() const {
    for(int i = 0; i < _numRow; ++i) {
        for(int j = 0; j < _numColumn; ++j) {
            if(_mapData[toNodeIndex(i, j)]) std::cout << 1;
            else std::cout << 0;
        }
        std::cout << std::endl;
    }
}

int EmbeddMap::toNodeIndex(int row, int column) const {
    return (row * _numColumn) + column;
}

#include "gaConfiguration.hpp"

#include<iostream>
#include<string>
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::to_string;

void GAConfiguration::setGraphNumRow(int graphNumRow) { 
    _graphNumRow = graphNumRow; 
}

void GAConfiguration::setGraphNumColumn(int graphNumColumn) { 
    _graphNumColumn = graphNumColumn; 
}

void GAConfiguration::setGraphDegree(int graphDegree) { 
    _graphDegree = graphDegree; 
}

void GAConfiguration::setGraphMaxLength(int graphMaxLength) { 
    _graphMaxLength = graphMaxLength; 
}

void GAConfiguration::setMaxGeneration(int maxGeneration) { 
    _maxGeneration = maxGeneration; 
}

void GAConfiguration::setPopulation(int population) { 
    _population = population; 
}

void GAConfiguration::setIndivMutateProbability(double indivMutateProbability) { 
    _indivMutateProbability = indivMutateProbability; 
}

void GAConfiguration::setGeneMutateProbability(double geneMutateProbability) { 
    _geneMutateProbability = geneMutateProbability; 
}

void GAConfiguration::setGenerationChangeModel(const std::string &generationChangeModel) { 
    _generationChangeModel = generationChangeModel; 
}

void GAConfiguration::setSeed(int seed) { 
    _seed = seed; 
}

string GAConfiguration::toDirectoryNameString() const{
    string str = "";
    str += "r" + to_string(_graphNumRow) + "_";
    str += "c" + to_string(_graphNumColumn) + "_";
    str += "d" + to_string(_graphDegree) + "_";
    str += "l" + to_string(_graphMaxLength) + "_";
    str += "p" + to_string(_population) + "_";
    str += "g" + to_string(_maxGeneration) + "_";
    str += _generationChangeModel + "_";
    str += "im" + to_string(_indivMutateProbability) + "_";
    str += "gm" + to_string(_geneMutateProbability) + "_";
    str += "seed" + to_string(_seed);
    return str;
}

void GAConfiguration::showConfigList() const {
    cout << "[Graph Constraints]" << endl;
    cout << "- Node        : " << _graphNumRow << "x" << _graphNumColumn << endl;
    cout << "- Degree      : " << _graphDegree    << endl;
    cout << "- Edge length : " << _graphMaxLength << endl;
    cout << "[GA Configuration]" << endl;
    cout << "- Population : " << _population << endl;
    cout << "- Max generation : " << _maxGeneration << endl;
    cout << "- Generation change model : " << _generationChangeModel << endl;
    cout << "- Mutation probability : (individual)" << _indivMutateProbability << ", (gene)" << _geneMutateProbability << endl;
    cout << "[Other]" << endl;
    cout << "- Seed : " << _seed << endl;
}

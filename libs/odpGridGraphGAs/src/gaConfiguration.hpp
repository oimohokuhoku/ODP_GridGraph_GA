#pragma once

#include <string>

namespace Cselab23Kimura::OdpGridGraphs::GA {
    class GAConfiguration {
    public:
        std::string toDirectoryNameString() const;
        void showConfigList() const;

        void setGraphNumRow(int graphNumRow);
        void setGraphNumColumn(int graphNumColumn);
        void setGraphDegree(int graphDegree);
        void setGraphMaxLength(int graphMaxLength);
        void setMaxGeneration(int maxGeneration);
        void setPopulation(int population);
        void setIndivMutateProbability(double indivMutateProbability);
        void setGeneMutateProbability(double geneMutateProbability);
        void setSeed(int seed);

        inline int graphNumColumn() const { return _graphNumColumn; }
        inline int graphNumRow() const { return _graphNumRow; }
        inline int graphDegree() const { return _graphDegree; }
        inline int graphMaxLength() const { return _graphMaxLength; }
        inline int maxGeneration() const { return _maxGeneration; }
        inline int population() const { return _population; }
        inline double indivMutateProbability() const { return _indivMutateProbability; }
        inline double geneMutateProbability() const { return _geneMutateProbability; }
        inline int seed() const { return _seed; }

    private:
        int _graphNumRow;
        int _graphNumColumn;
        int _graphDegree;
        int _graphMaxLength;
        int _maxGeneration;
        int _population;
        double _indivMutateProbability;
        double _geneMutateProbability;
        int _seed;
    };

}
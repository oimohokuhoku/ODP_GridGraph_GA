#pragma once

namespace Cselab23Kimura::OdpGridGraphs::GA::Crossovers {
    class EmbeddMap {
    public:
        EmbeddMap(int numRow, int numColumn);
        EmbeddMap(const EmbeddMap& obj);
        EmbeddMap(EmbeddMap&& obj);
        ~EmbeddMap();

        void operator=(const EmbeddMap& obj);
        void operator=(EmbeddMap&& obj);
        bool at(int index) const;
        bool at(int rowIndex, int columnIndex) const;
        void set(int index, bool value);
        void set(int rowIndex, int columnIndex, bool value);
        EmbeddMap overlay(const EmbeddMap& embeddMap) const;
        void showMap() const;

        inline int numRow() const { return _numRow; }
        inline int numColumn() const { return _numColumn; }
        inline int numNode() const { return _numNode; }

    private:
        const int _numRow;
        const int _numColumn;
        const int _numNode;
        bool *_mapData;

        int toNodeIndex(int row, int column) const;
    };
}

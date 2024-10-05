#pragma once

#include "odpGridGraphs/include/gridGraphs.hpp"
namespace Cselab23Kimura::OdpGridGraphs { class GridGraph; }

namespace Cselab23Kimura::OdpGridGraphs::GA
{
	using Individual = Cselab23Kimura::OdpGridGraphs::GridGraph;

	///@brief Individualオブジェクトのコレクションクラス.
	struct Group {
	public:
		Individual *indivs;

		Group(int size);
		Group(const Group &obj);
		Group(Group &&obj);
		~Group();

		Group &operator=(const Group &obj);
		Group &operator=(Group &&obj);

		void tally();

		inline int population() const { return _population; }
		inline Individual bestIndiv() const { return indivs[_bestIndivIndex]; }
		inline int bestDiameter() const { return _bestDiameter; }
		inline double bestASPL() const { return _bestAspl; }
		inline double averageASPL() const { return _averageAspl; }
		inline double worstASPL() const { return _worstAspl; }
		inline int indivVariation() const { return _indivVariation; }

	private:
		const int _population;
		int _bestIndivIndex;
		int _bestDiameter;
		double _bestAspl;
		double _averageAspl;
		double _worstAspl;
		int _indivVariation;

		int countIndivVariation() const;
	};
}

#pragma once
#include "../externalLib/odpGridGraphs/include/odpGridGraphs.hpp"

namespace Cselab23Kimura {
	namespace OdpGridGraphs {
		class GridGraph;
		namespace GA {
			using Individual = GridGraph;

			///@brief Individualオブジェクトのコレクションクラス.
			struct Group {
			public:
				Individual *indivs;

				Group(int size);
				Group(const Group &obj);
				Group(Group &&obj);
				~Group();

				Group& operator=(const Group &obj);
				void   operator=(Group &&obj);

				void tally();

				inline int population() const { return _population; }
				inline Individual bestIndiv() const { return indivs[_bestIndivIndex]; }
				inline int bestDiameter() const { return _bestDiameter; }
				inline double bestASPL() const { return _bestAspl; }
				inline double averageASPL() const { return _averageAspl; }
				inline double worstASPL() const { return _worstAspl; }
				inline int indivVariation() const { return _indivVariation; }

			private:
				int _population;
				int _bestIndivIndex;
				int _bestDiameter;
				double _bestAspl;
				double _averageAspl;
				double _worstAspl;
				int _indivVariation;

				int countIndivVariation() const;
			};
		}
	}
}

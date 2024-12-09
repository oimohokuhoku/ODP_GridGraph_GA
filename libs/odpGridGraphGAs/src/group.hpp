#pragma once

namespace Cselab23Kimura::OdpGridGraphs {
	class GridGraph;
	
	namespace GA {
		///@brief GridGraphオブジェクトのコレクションクラス.
		struct Group {
		public:
			Group(int size);
			Group(const Group &obj);
			Group(Group &&obj);
			~Group();

			Group& operator=(const Group &obj);
			Group& operator=(Group &&obj);
			GridGraph& operator[](int index);
			const GridGraph& operator[](int index) const;

			void tally();
			const GridGraph& bestIndiv() const;

			inline int population() const { return _population; }
			inline int bestDiameter() const { return _bestDiameter; }
			inline double bestASPL() const { return _bestAspl; }
			inline double averageASPL() const { return _averageAspl; }
			inline double worstASPL() const { return _worstAspl; }
			inline int indivVariation() const { return _indivVariation; }

		private:
			GridGraph *_indivs;
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

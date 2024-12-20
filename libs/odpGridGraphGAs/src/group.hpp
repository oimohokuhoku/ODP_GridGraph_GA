#pragma once
#include <optional>

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

			std::optional<GridGraph>& operator[](int index);
			const std::optional<GridGraph>& operator[](int index) const;

			const GridGraph& bestIndiv() const;
			int bestDiameter() const;
			int worstDiameter() const;
			double averageDiameter() const;
			double bestAspl() const;
			double worstAspl() const;
			double averageAspl() const;
			int indivVariation() const;

			inline int population() const { return _population; }

		private:
			static constexpr int _UNCALCULATED = -1;
			std::optional<GridGraph> *_indivs;
			const int _population;
			mutable int _bestIndivIndex;
			mutable int _worstIndivIndex;
			mutable double _averageDiameter;
			mutable double _averageAspl;
			mutable int _indivVariation;

			int findBestIndivIndex() const;
			int findWorstIndivIndex() const;
			double calcAverageAspl() const;
			double calcAverageDiameter() const;
			int countIndivVariation() const;
		};
	}
}

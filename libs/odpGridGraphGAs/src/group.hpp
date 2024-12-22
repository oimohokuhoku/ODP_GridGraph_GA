#pragma once
#include <optional>

namespace Cselab23Kimura::OdpGridGraphs {
	class GridGraph;
	
	namespace GA {
		///@brief std::optional<GridGraph>の配列を管理するコレクションクラス
		struct Group {
		public:
			Group(int population);
			Group(const Group &obj);
			Group(Group &&obj);
			~Group();

			Group& operator=(const Group &obj);
			Group& operator=(Group &&obj);

			std::optional<GridGraph>& operator[](int index);
			const std::optional<GridGraph>& operator[](int index) const;
			std::optional<GridGraph>& get(int index);
			const std::optional<GridGraph>& get(int index) const;

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
			const int _population;
			std::optional<GridGraph> *_indivs;
			mutable int _bestIndivIndexCache;
			mutable int _worstIndivIndexCache;
			mutable double _averageDiameterCache;
			mutable double _averageAsplCache;
			mutable int _indivVariationCache;

			int findBestIndivIndex() const;
			int findWorstIndivIndex() const;
			double calcAverageAspl() const;
			double calcAverageDiameter() const;
			int countIndivVariation() const;
		};
	}
}

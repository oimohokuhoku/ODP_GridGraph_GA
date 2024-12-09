#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
#include "../../unitTest.hpp"
#include <random>
#include <vector>
#include <string>
#include <memory>
using namespace Cselab23Kimura;
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::vector;
using std::unique_ptr;

class SurvivorSelectMock: public SurvivorSelects::SurvivorSelect {
private:
    const vector<int> _pickUpChildIndexes;
    const vector<int> _pickUpParentIndexes;
    
public:
    SurvivorSelectMock(const vector<int> pickupChildIndexes, const vector<int> pickupParentIndexes): 
        _pickUpChildIndexes(pickupChildIndexes),
        _pickUpParentIndexes(pickupParentIndexes)
    {}
    ~SurvivorSelectMock() = default;

    Group moveSurvivors(Group& childs, Group& parents, std::mt19937& random) override {
        int numPickUp = _pickUpChildIndexes.size() + _pickUpParentIndexes.size();
        int index = 0;
        Group result(numPickUp);
        
        for(size_t i = 0; i < _pickUpChildIndexes.size(); ++i) {
            result[index++] = std::move(childs[_pickUpChildIndexes[i]]);
        }
        for(size_t i = 0; i < _pickUpParentIndexes.size(); ++i) {
            result[index++] = std::move(parents[_pickUpParentIndexes[i]]);
        }

        return std::move(result);
    }
};

bool selected_individuals() {
    constexpr int population = 5;
    RandomInitialize randomGraphGenerate;
    std::mt19937 mt(42);


    Group parentSrc = randomGraphGenerate.genearteInitialGroup(population, mt);
    Group childSrc  = randomGraphGenerate.genearteInitialGroup(population, mt);

    Group parents = parentSrc;
    Group childs  = childSrc;
    
    UnitTest unitTest("select elitist individual");

    vector<SurvivorSelects::SurvivorSelect*> selects;
    selects.push_back(new SurvivorSelectMock(vector<int>{0, 1}, vector<int>{0}));
    selects.push_back(new SurvivorSelectMock(vector<int>{2},    vector<int>{1, 2}));
    SurvivorSelects::MixSelect select(selects);

    Group survivor = select.moveSurvivors(childs, parents, mt);

    unitTest.assertEqualInt("group size is correct" ,survivor.population(), 6);

    unitTest.assertTrue("moved1", survivor[0].matchGraph(childSrc[0]));
    unitTest.assertTrue("moved2", survivor[1].matchGraph(childSrc[1]));
    unitTest.assertTrue("moved3", survivor[2].matchGraph(parentSrc[0]));

    unitTest.assertTrue("moved4", survivor[3].matchGraph(childSrc[2]));
    unitTest.assertTrue("moved5", survivor[4].matchGraph(parentSrc[1]));
    unitTest.assertTrue("moved6", survivor[5].matchGraph(parentSrc[2]));

    unitTest.showResult();
    return unitTest.successAll();
}

int main(void) {
    bool success = true;
    GridGraph::setDefaultGraphCondition(5, 5, 4, 2);

    success &= selected_individuals();

    if(success) return EXIT_SUCCESS;
    else        return EXIT_FAILURE;
}



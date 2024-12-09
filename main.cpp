#include <iostream>
#include <memory>
#include <random>
#include "odpGridGraphGAs.hpp"
#include "commonLibraries.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::CommonLibrarys;

using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;
using std::make_unique;

static const string OPTION_NUM_ROW     = "-r";
static const string OPTION_NUM_COLUMN  = "-c";
static const string OPTION_DEGREE      = "-d";
static const string OPTION_MAX_LENGTH  = "-l";
static const string OPTION_POPULATION  = "-p";
static const string OPTION_MAX_GENERATION = "-g";
static const string OPTION_INDIV_MUTATE_PROBABILITY = "-im";
static const string OPTION_GENE_MUTATE_PROBABILITY   = "-gm";
static const string OPTION_RESULT_FILENAME = "-f";
static const string OPTION_SEED = "-seed";

int main(int argc, char* argv[]) {
    CommandLineArgument args(argc, argv);
    GAConfiguration gaConfig;
    gaConfig.setGraphNumRow(args.getValue<int>(OPTION_NUM_ROW)); 
    gaConfig.setGraphNumColumn(args.getValue<int>(OPTION_NUM_COLUMN)); 
    gaConfig.setGraphDegree(args.getValue<int>(OPTION_DEGREE)); 
    gaConfig.setGraphMaxLength(args.getValue<int>(OPTION_MAX_LENGTH)); 
    gaConfig.setMaxGeneration(args.getValue<int>(OPTION_MAX_GENERATION));
    gaConfig.setPopulation(args.getValue<int>(OPTION_POPULATION));
    gaConfig.setIndivMutateProbability(args.getValue<double>(OPTION_INDIV_MUTATE_PROBABILITY));
    gaConfig.setGeneMutateProbability(args.getValue<double>(OPTION_GENE_MUTATE_PROBABILITY));
    gaConfig.setSeed(args.getValue<int>(OPTION_SEED)); 
    gaConfig.showConfigList();

    string resultDirName   = "result";
    string executedDirName = resultDirName + "/" + gaConfig.toDirectoryNameString();
    if(args.existOption(OPTION_RESULT_FILENAME)) {
        executedDirName = resultDirName + "/" + args.getValue<string>(OPTION_RESULT_FILENAME);
    }
    string transFileName   = executedDirName + "/transition.csv";
    Directory::create(resultDirName);
    Directory::create(executedDirName);

    std::mt19937 random(gaConfig.seed());
    Crossovers::GenerateEmbeddMapUnits* embeddMapUnits = new Crossovers::GenerateOrthogonalBlockEmbeddMapUnits();

    Initialize* initialize = new RandomInitialize();
    CopySelects::CopySelect* copySelect = new CopySelects::RandomSelectWithoutReplacement(gaConfig.seed());
    Crossovers::Crossover*   crossover  = new Crossovers::BlockCrossover(embeddMapUnits);
    Mutates::Mutate*         mutate     = new Mutates::TwoChangeMutate(gaConfig.indivMutateProbability(), gaConfig.geneMutateProbability());

    std::vector<SurvivorSelects::SurvivorSelect*> survivorSelects;
    survivorSelects.push_back(new SurvivorSelects::ElitistSelect());
    survivorSelects.push_back(new SurvivorSelects::RankingSelect());
    SurvivorSelects::SurvivorSelect* survivorSelect = new SurvivorSelects::MixSelect(survivorSelects);
    
    GeneticAlgorithm ga(gaConfig, initialize, random);
    GAParameterTable paramTable;
    GaCsvRecorder csvRecorder(transFileName);
    
    cout << endl;
    paramTable.showHedder();
    paramTable.showParameter(ga);
    csvRecorder.record(ga);
    while(true) {
        ga.progressGeneration(
            copySelect,
            crossover,
            mutate,
            survivorSelect,
            random
        );
        paramTable.showParameter(ga);
        csvRecorder.record(ga);
        if(ga.end()) break;
    }

    ga.saveBestEverEdgeFile(executedDirName);

    delete embeddMapUnits;
    delete initialize;
    delete copySelect;
    delete crossover;
    delete mutate;
    for(size_t i = 0; i < survivorSelects.size(); ++i) {
        delete survivorSelects[i];
    }
    delete survivorSelect;
    return 0;
}
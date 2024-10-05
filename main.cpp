#include <iostream>
#include <memory>
#include <random>
#include "odpGridGraphGAs/include/odpGridGraphGAs.hpp"
#include "commonLib/programs/commandLineArgument.hpp"
#include "commonLib/systems/directory.hpp"
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using std::cout;
using std::endl;
using std::string;
using std::unique_ptr;

static const string OPTION_NUM_ROW     = "-r";
static const string OPTION_NUM_COLUMN  = "-c";
static const string OPTION_DEGREE      = "-d";
static const string OPTION_MAX_LENGTH  = "-l";
static const string OPTION_POPULATION  = "-p";
static const string OPTION_MAX_GENERATION = "-g";
static const string OPTION_GENERATION_CHANGE_MODEL  = "-m";
static const string OPTION_INDIV_MUTATE_PROBABILITY = "-im";
static const string OPTION_GENE_MUTATE_PROBABILITY   = "-gm";
static const string OPTION_SEED = "-seed";

int main(int argc, char* argv[]) {
    Programs::CommandLineArgument args(argc, argv);
    GAConfiguration gaConfig;
    gaConfig.setGraphNumRow(args.getValue<int>(OPTION_NUM_ROW)); 
    gaConfig.setGraphNumColumn(args.getValue<int>(OPTION_NUM_COLUMN)); 
    gaConfig.setGraphDegree(args.getValue<int>(OPTION_DEGREE)); 
    gaConfig.setGraphMaxLength(args.getValue<int>(OPTION_MAX_LENGTH)); 
    gaConfig.setMaxGeneration(args.getValue<int>(OPTION_MAX_GENERATION));
    gaConfig.setPopulation(args.getValue<int>(OPTION_POPULATION));
    gaConfig.setIndivMutateProbability(args.getValue<double>(OPTION_INDIV_MUTATE_PROBABILITY));
    gaConfig.setGeneMutateProbability(args.getValue<double>(OPTION_GENE_MUTATE_PROBABILITY)); 
    gaConfig.setGenerationChangeModel(args.getValue<std::string>(OPTION_GENERATION_CHANGE_MODEL));
    gaConfig.setSeed(args.getValue<int>(OPTION_SEED)); 
    gaConfig.showConfigList();

    string resultDirName   = "result";
    string executedDirName = resultDirName + "/" + gaConfig.toDirectoryNameString();
    string transFileName   = executedDirName + "/transition.csv";
    Systems::Directory::create(resultDirName);
    Systems::Directory::create(executedDirName);

    std::mt19937 random(gaConfig.seed());
    unique_ptr<Initialize> initialize(new RandomInitialize());
    unique_ptr<CopySelect> copySelect(new StairsSelect());
    unique_ptr<GenerateEmbeddMapUnits> embeddMapUnits(new GenerateOrthogonalBlockEmbeddMapUnits());
    unique_ptr<Crossover> crossover(new BlockCrossoverWithDMSXf(embeddMapUnits));
    unique_ptr<Mutate> mutate(new TwoChangeMutate(gaConfig.indivMutateProbability(), gaConfig.geneMutateProbability()));
    unique_ptr<SurvivorSelect> survivorSelect(new PassAllChild());
    
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
    return 0;
}
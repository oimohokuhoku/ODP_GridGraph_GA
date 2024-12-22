#include <iostream>
#include <random>
#include "odpGridGraphGAs.hpp"
#include "odpGridGraphs.hpp"
#include "commonLibraries.hpp"
using namespace Cselab23Kimura::OdpGridGraphs;
using namespace Cselab23Kimura::OdpGridGraphs::GA;
using namespace Cselab23Kimura::CommonLibrarys;
using std::cout;
using std::endl;
using std::string;

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
    #ifdef DEBUG
        cout << "Executing in Debug mode!" << endl;
    #endif

    CommandLineArgument args(argc, argv);
    int numRow    = args.getValue<int>(OPTION_NUM_ROW);
    int numColumn = args.getValue<int>(OPTION_NUM_COLUMN);
    int degree    = args.getValue<int>(OPTION_DEGREE);
    int length    = args.getValue<int>(OPTION_MAX_LENGTH);
    int maxGeneration = args.getValue<int>(OPTION_MAX_GENERATION);
    int population    = args.getValue<int>(OPTION_POPULATION);
    double indivMutateProbability = args.getValue<double>(OPTION_INDIV_MUTATE_PROBABILITY);
    double geneMutateProbability  = args.getValue<double>(OPTION_GENE_MUTATE_PROBABILITY);
    int seed = args.getValue<int>(OPTION_SEED);
    string experimentName = args.getValue<string>(OPTION_RESULT_FILENAME);

    cout << "[Graph Constraints]" << endl;
    cout << "- Node        : " << numRow << "x" << numColumn << endl;
    cout << "- Degree      : " << degree << endl;
    cout << "- Edge length : " << length << endl;
    cout << "[GA Configuration]"  << endl;
    cout << "- Population : "     << population     << endl;
    cout << "- Max generation : " << maxGeneration  << endl;
    cout << "- Mutation probability : (individual)" << indivMutateProbability << ", (gene)" << geneMutateProbability << endl;
    cout << "[Other]"   << endl;
    cout << "- Seed : " << seed << endl;
    cout << "- Experiment Name : " << experimentName << endl;

    string resultDirName     = "result";
    string experimentDirPath = resultDirName + "/" + experimentName;
    string transFileName     = experimentDirPath + "/transition.csv";
    Directory::create(resultDirName);
    Directory::create(experimentDirPath);

    std::mt19937 random(seed);
    Grid grid(numRow, numColumn, degree, length);

    Initialize*                         initialize     = new RandomInitialize(grid);
    CopySelects::CopySelect*            copySelect     = new CopySelects::DmsxfSelect(random);
    Crossovers::GenerateEmbeddMapUnits* embeddMapUnits = new Crossovers::GenerateOrthogonalBlockEmbeddMapUnits();
    Crossovers::Crossover*              crossover      = new Crossovers::BlockCrossoverWithDMSXf(embeddMapUnits, 0.0);
    Mutates::Mutate*                    mutate         = new Mutates::TwoChangeMutate(indivMutateProbability, geneMutateProbability);
    SurvivorSelects::SurvivorSelect*    survivorSelect = new SurvivorSelects::PassAllChild();
    
    GaParameterTable paramTable;
    GaCsvRecorder csvRecorder(transFileName);

    Group group = initialize->genearteInitialGroup(population, random);
    GeneticAlgorithm ga(group);
    
    cout << endl;
    paramTable.showHedder();
    paramTable.showRow(ga.generation(), group);
    csvRecorder.record(ga.generation(), group);
    while(true) {
        group = ga.progressGeneration(
            group, 
            copySelect,
            crossover,
            mutate,
            survivorSelect,
            random
        );

        paramTable.showRow(ga.generation(), group);
        csvRecorder.record(ga.generation(), group);
        if(
            ga.generation() == maxGeneration ||
            group.indivVariation() == 1
        ) break;
    }

    EdgesFileWriter::write(group.bestIndiv(), "result.edges");

    delete embeddMapUnits;
    delete initialize;
    delete copySelect;
    delete crossover;
    delete mutate;
    delete survivorSelect;
    return EXIT_SUCCESS;
}
#include "directory.hpp"
using namespace Cselab23Kimura::CommonLibrarys;

/// @brief ディレクトリが存在するか判定.
bool Directory::exist(std::string dirName) {
    struct stat statBuf;
    if(stat(dirName.c_str(), &statBuf) == 0) 
        return true;
    else 
        return false;
}

/// @brief ディレクトリを作成.
void Directory::create(std::string dirName) {
    if(Directory::exist(dirName)) return;
    mkdir(dirName.c_str(), 0777);
}
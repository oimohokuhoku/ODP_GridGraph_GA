#include "directory.hpp"
#include<string>
#include<sys/stat.h>
using namespace Systems;
using std::string;

//! @brief ディレクトリが存在するか判定.
bool Directory::exist(string dirName) {
    struct stat statBuf;
    if(stat(dirName.c_str(), &statBuf) == 0) 
        return true;
    else 
        return false;
}

//! @brief ディレクトリを作成.
void Directory::create(string dirName) {
    if(Directory::exist(dirName)) return;
    mkdir(dirName.c_str(), 0777);
}
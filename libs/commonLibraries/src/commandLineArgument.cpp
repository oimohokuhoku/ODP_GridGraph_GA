#include "commandLineArgument.hpp"
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace Cselab23Kimura::CommonLibrarys;
using std::string;
using std::vector;
using std::cout;
using std::endl;

/// @brief Initialize with loading command line argument.
/// @param argc The same as main(int argc, char* argv[])
/// @param argv The same as main(int argc, char* argv[])
CommandLineArgument::CommandLineArgument(int argc, char* argv[]) {
    int state = 0;
    string option = "";
    string value = "";
    
    for(int i = 1; i < argc; ++i) {
        if(state == 0) {
            if(argv[i][0] == '-') { 
                option = string(argv[i]);
                state = 1;
            }
            else {
                value = string(argv[i]);
                ArgSet argSet = {"", value, true};
                this->_argSet.push_back(argSet);

                option = "";
                value = "";
                state = 0;
            }
        }
        else if(state == 1) { //after reading option
            if(argv[i][0] == '-') {
                ArgSet argSet = {option, "", false};
                this->_argSet.push_back(argSet);

                option = string(argv[i]);
                value = "";
                state = 1;
            }
            else {
                value = string(argv[i]);
                ArgSet argSet = {option, value, true};
                this->_argSet.push_back(argSet);

                option = "";
                value = "";
                state = 0;
            }
        }
    }

    if(state == 1) {
        ArgSet argSet = {option, ""};
        this->_argSet.push_back(argSet);
    }
}

/// @brief Show consisted arguments on console
void CommandLineArgument::showArguments() const {
    const int NUM_ARG = _argSet.size();

    //show if is option
    for(int i = 0; i < NUM_ARG; ++i) {
        if(_argSet[i].option == "") continue;
        printf("%-10s %s\n", _argSet[i].option.c_str(), _argSet[i].value.c_str());
    }

    //show if is only value
    for(int i = 0; i < NUM_ARG; ++i) {
        if(_argSet[i].option != "") continue;
        cout << _argSet[i].value << endl;
    }
}

/// @brief Check whether the option is included in arguments
bool CommandLineArgument::existOption(const string& option) const {
    const int NUM_ARG = _argSet.size();
    for(int i = 0; i < NUM_ARG; ++i) {
        if(_argSet[i].option == option) return true;
    }
    return false;
}

/// @brief Get value as "string" with option specification.
template<> std::string CommandLineArgument::getValue<std::string>(const std::string& option) const {
    const int NUM_ARG = _argSet.size();
    for(int i = 0; i < NUM_ARG; ++i) {
        if(_argSet[i].option == option) {
            if(_argSet[i].hasValue) return _argSet[i].value;

            std::cout << "Option \"" << option << "\" doesn't be designated argument" << std::endl;
            exit(1);
        }
    }

    std::cout << "Option \"" << option << "\" doesn't exist" << std::endl;
    exit(1); return "";
}

/// @brief Get value as "int" with option specification.
template<> int CommandLineArgument::getValue<int>(const std::string& option) const {
    return std::stoi(this->getValue<std::string>(option));
}

/// @brief Get value as "double" with option specification.
template<> double CommandLineArgument::getValue<double>(const std::string& option) const {
    return std::stod(this->getValue<std::string>(option));
}

/// @brief Get value as "bool" with option specification.
template<> bool CommandLineArgument::getValue<bool>(const std::string& option) const {
    std::string value = getValue<std::string>(option);

    bool isNumber = std::all_of(value.begin(), value.end(), [](char c) { return std::isdigit(c); });
    if(isNumber) return (value != "0");

    transform(value.begin(), value.end(), value.begin(), ::tolower);
    if(value == "true") return true;
    if(value == "false") return false;

    std::cout << option << " " << value << " can't regard as bool" << std::endl;
    exit(0); return false;
}

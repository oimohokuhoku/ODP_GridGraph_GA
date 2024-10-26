#pragma once

#include <string>
#include <vector>
#include<iostream>
#include<cstring>
#include<algorithm>

namespace Cselab23Kimura::CommonLibrarys
{
    class CommandLineArgument {
    public:
        CommandLineArgument(int argc, char* argv[]);
        void showArguments() const;
        bool existOption(const std::string& option) const;
        template <class T>
        T getValue(const std::string& option) const;

    private:
        struct ArgSet {
            std::string option;
            std::string value;
            bool hasValue;
        };

        std::vector<ArgSet> _argSet;
        CommandLineArgument() = delete;
    };
}

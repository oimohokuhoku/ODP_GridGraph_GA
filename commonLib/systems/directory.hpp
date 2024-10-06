#pragma once
#include <string>

namespace Systems {
    //! @brief [Static Class] ディレクトリ操作
    class Directory {
    public:
        static bool exist(std::string dirName);
        static void create(std::string dirName);
        static void tryCreate(std::string dirName);

    private:
        Directory() = delete;
    };
}
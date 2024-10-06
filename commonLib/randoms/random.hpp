#pragma once

#include <random>

class Random {
public:
    static void initialize();
    static void initialize(int seed);
    static int randInt();
    static int randInt(int min, int max);
    static double randDouble(double min, double max);
    static bool roulette(double probability);
    static inline std::mt19937 engine() { return mt; };

private:
    static std::mt19937 mt;

    Random() = delete;
};
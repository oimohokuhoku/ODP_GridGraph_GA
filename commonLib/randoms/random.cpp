#include "random.hpp"

#include <random>

/// @brief ランダムなシード値によって初期化
void Random::initialize() {
    std::random_device rnd;
    mt = std::mt19937(rnd());
}

/// @brief 指定したシート値によって初期化
/// @param seed 
void Random::initialize(int seed) {
    mt = std::mt19937(seed);
}

/// @brief ランダムな整数を取得 (min以上, max未満)
int Random::randInt() {
    return mt(); 
}

/// @brief ランダムな整数を取得 (min以上, max未満)
int Random::randInt(int min, int max) {
    return (int)((mt() % (max - min)) + min); 
}

/// @brief ランダムな実数を取得 (min以上, max未満)
double Random::randDouble(double min, double max) {
    double r = (double)mt() / mt.max();
    return (r * (max - min)) + min;
}

/// @brief 指定した確率に応じてtrueかfalseを返す
bool Random::roulette(double probability) {
    double rand = randDouble(0, 1);
    if(rand <= probability) return true;
    else                    return false;
}

std::mt19937 Random::mt;

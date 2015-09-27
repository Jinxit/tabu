
#include <iostream>
#include <random>
#include <math.h>
#include "tabu_search.hpp"

int main(int argc, const char* argv[])
{
    auto fitness = [](int x) {
        if (x >= 8)
            return -1000;
        return (int)(std::pow(x*0.25, 5) - 10 * std::pow(0.25*x, 3) + 7.5 * x);
    };
    std::default_random_engine gen;
    std::uniform_int_distribution<int> uniform_dist(-10, 10);
    auto random = [&]() {
        return uniform_dist(gen);
    };
    auto neighbours = [](int x) {
        return std::vector<int>{x - 1, x + 1};
    };
    auto best = tabu::search<int>(20, 5, fitness, random, neighbours);

    std::cout << best << std::endl;
    std::cout << fitness(best) << std::endl;
}
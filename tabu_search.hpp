#pragma once
 
#include <vector>
#include <deque>
#include <map>
#include <utility>
#include <functional>
 
#include <iostream>
 
namespace MotionPlanning
{
    template<class T>
    class TabuSearch
    {
        int short_memory_size;
        std::deque<T> short_memory;
        std::function<float(T)> fitness;
        std::function<T()> random;
        std::function<std::vector<T>(T)> neighbours;
    public:
        TabuSearch(int short_memory_size, std::function<float(T)> fitness, std::function<T()> random, std::function<std::vector<T>(T)> neighbours)
            : short_memory_size(short_memory_size),  short_memory(short_memory_size, random()), fitness(fitness), random(random), neighbours(neighbours) { };
 
        T explore(int max_attempts)
        {
            T current = short_memory.front();
            T best = current;
            float best_fitness = fitness(best);
            for (int i = 0; i < max_attempts; i++)
            {
                auto possibles = neighbours(current);
                 
                for (auto& sm : short_memory)
                {
                    auto it = std::find(possibles.begin(), possibles.end(), sm);
                    if (it != possibles.end())
                    {
                        possibles.erase(it);
                    }
                }
                if (possibles.size() == 0)
                {
                    break;
                }
 
                std::vector<std::pair<float, T>> scores;
                std::transform(possibles.begin(), possibles.end(), std::inserter(scores, scores.begin()), [&](T p) { return std::pair<float, T>(fitness(p), p); });
                std::sort(scores.begin(), scores.end(), std::greater<std::pair<float, T>>());
 
                for (auto& kvp : scores)
                {
                    short_memory.pop_back();
                    short_memory.push_front(kvp.second);
                    if (kvp.first > best_fitness)
                    {
                        best = kvp.second;
                        best_fitness = kvp.first;
                    }
                    current = kvp.second;
                }
            }
 
            return best;
        }
    };
}
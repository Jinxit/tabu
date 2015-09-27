#pragma once
 
#include <vector>
#include <deque>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
 
namespace tabu
{
    template<class T>
    T search(int max_attempts,
             int short_memory_size,
             std::function<float(T)> fitness,
             std::function<T()> random,
             std::function<std::vector<T>(T)> neighbours)
    {
        std::deque<T> short_memory(short_memory_size, random());
        T current = short_memory.front();
        T best = current;
        float best_fitness = fitness(best);
        for (int i = 0; i < max_attempts; i++)
        {
            auto possibles = neighbours(current);

            possibles.erase(std::remove_if(possibles.begin(), possibles.end(), [&](T val) {
                return std::find(short_memory.begin(), short_memory.end(), val) != short_memory.end();
            }), possibles.end());
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
                break;
            }
        }

        return best;
    }
}
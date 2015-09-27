#pragma once
 
#include <vector>
#include <deque>
#include <map>
#include <utility>
#include <functional>
#include <algorithm>
 
namespace tabu
{
    // attempts to maximize fitness(T) while exploring greedily
    // but also keeping a short memory to (hopefully) avoid
    // local maxima
    template<class T>
    std::pair<float, T> search(
             int max_attempts,
             int short_memory_size,
             std::function<float(T)> fitness,
             std::function<T()> random,
             std::function<std::vector<T>(T)> neighbours)
    {
        std::deque<T> short_memory(short_memory_size, random());
        T current = short_memory.front();
        auto best = std::make_pair(fitness(current), current);
        for (int i = 0; i < max_attempts; i++)
        {
            auto possibles = neighbours(current);

            // computes possibles ∖ short_memory
            possibles.erase(
                std::remove_if(possibles.begin(), possibles.end(),
                               [&](T val) {
                                   auto it = std::find(short_memory.begin(),
                                                       short_memory.end(), val);
                                   return it != short_memory.end();
                               }
                ), possibles.end());
            if (possibles.size() == 0)
            {
                break;
            }

            // transforms T -> {fitness(T), T}
            std::vector<std::pair<float, T>> scores;
            std::transform(possibles.begin(), possibles.end(),
                           std::back_inserter(scores),
                           [&](T p) {
                                return std::make_pair(fitness(p), p);
                           }
            );

            // a maximum element will always exist because possibles isn't empty,
            // so we can dereference right away
            auto challenger = *std::max_element(scores.begin(), scores.end());

            short_memory.pop_back();
            short_memory.push_front(challenger.second);

            best = std::max(best, challenger);

            current = challenger.second;
        }

        return best;
    }
}
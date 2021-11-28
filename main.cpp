#include <iostream>
#include <cassert>
#include <vector>
#include <array>
#include <cmath>

template <std::size_t Size> std::array<std::vector<unsigned int>, Size> Conway(unsigned int seed = 1) {

    return {};

}

std::vector<unsigned int> Next(std::vector<unsigned int> series) {

    std::vector<unsigned int> n;
    unsigned int id{series[0]}, count{1};

    for (std::size_t i{1}; i < series.size(); i++) {

        if (series[i] == id) {

            count++;

        } else {

            n.push_back(count);
            n.push_back(id);
            id = series[i];
            count = 1;

        }

    }

    if (count != 1 || id == 1 || series.size() <= 2) {
        
        n.push_back(count);
        n.push_back(id);
    
    }

    return n;

}

std::vector<std::vector<unsigned int>> Conway(std::size_t size, unsigned int seed = 1) {

    if (size == 0) {

        return {};

    } else if (size == 1) {

        if (seed > 9) {

            std::vector<unsigned int> first;

            while (seed > 9) {

                const auto l{log10l(seed)+1};
                first.insert(first.begin(), (seed/static_cast<double>(powl(10, l))-seed/powl(10, l))*powl(10, l));
                std::cout << first[0] << " ";

                seed -= l*powl(10, l+1);

            }

            return {first};

        } else {
            
            return {{{seed}}};

        }

    } else {

        std::vector<std::vector<unsigned int>> v{Conway(size-1, seed)};
        v.push_back(Next(v.back()));

        return v;

    }

}

void Add(std::vector<std::vector<unsigned int>> &v) { v.push_back(Next(v.back())); }

int main() {
 
    std::vector<std::vector<unsigned int>> v{Conway(30, 42)};

    for (auto s : v) {

        for (auto n : s) std::cout << n << ", ";
        std::cout << std::endl;

    }

    return 0;

}
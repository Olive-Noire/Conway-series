#include <iostream>
#include <cassert>
#include <string>
#include <vector>
#include <array>

using Series_Type = unsigned int;
using Series = std::vector<Series_Type>;
using Conway_Series = std::vector<Series>;
template <std::size_t Size> using Static_Conway_Series = std::array<Series, Size>;

template <std::size_t Size> Static_Conway_Series<Size> Conway(Series_Type seed = 1) {

    if (Size == 0) return {};

    Static_Conway_Series<Size> s;
    s[0] = seed;

    for (std::size_t i{1}; i < Size; i++) s[i] = Next(s[i-1]);

    return s;

}

template <std::size_t Size> Static_Conway_Series<Size+1> Add(const Static_Conway_Series<Size> &s) {

    Static_Conway_Series<Size+1> n;
    for (std::size_t i{0}; i < Size; i++) n[i] = s[i];
    n[n.size()-1] = Next(s.back());

    return n;

}

template <std::size_t Size> Static_Conway_Series<Size-1> Remove(const Static_Conway_Series<Size> &s) {

    Static_Conway_Series<Size-1> n;
    for (std::size_t i{0}; i < Size-1; i++) n[i] = s[i];

    return n;

}

Series Next(Series s) {

    Series n;
    Series_Type id{series[0]}, count{0};

    for (std::size_t i{1}; i < s.size(); i++) {

        count++;

        if (s[i] != id || i == s.size()-1) {

            n.push_back(count);
            n.push_back(id);
            id = s[i];
            count = 0;

        }

    }

    if (count == 0) {

        n.push_back(1);
        n.push_back(id);

    }

    return n;

}

Series Before(Series s, bool strict = false) {

    if (s.size() <= 1 || !(s.size()%2)) return {};
    
    if (strict) {

        for (const auto n : s) {

            if (n > 3) return {};

        }

    }

    Series b;

    for (std::size_t i{0}; i < s.size(); i++) {

        for (std::size_t index{0}; index < s[i]; index++) b[i].push_back(s[i+1]);
        
    }

    return b;

}

Conway_Series Conway(std::size_t size, Series_Type seed = 1) {

    if (size == 0) {

        return {};

    } else if (size == 1) {

        Series v;
        for (char c : std::to_string(seed)) v.push_back(static_cast<Series_Type>(c-'0'));

        return {v};

    } else {

        Conway_Series v{Conway(size-1, seed)};
        v.push_back(Next(v.back()));

        return v;

    }

}

void Add(Conway_Series &v) { v.push_back(Next(v.back())); }
void Remove(Conway_Series &v) { v.pop_back(); }

std::size_t TotalSize(Conway_Series &v) {

    std::size_t s{0};
    for (const auto& buffer : v) s += buffer.size();

    return s;

}

int main() {
 
    Conway_Series v{Conway(10, 42)};

    for (const auto s : v) {

        for (std::size_t i{0}; i < s.size(); i++) {
            
            std::cout << s[i];
            if (i != s.size()-1) std::cout << ", ";

        }

        std::cout << std::endl;

    }

    return 0;

}
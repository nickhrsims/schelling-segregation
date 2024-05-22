#pragma once

#include "rng.h"
#include <cstddef>
#include <vector>

template <typename T> struct grid {

    struct position {
        const int row;
        const int col;
    };

    grid(int size, const T base);
    int size();
    const position find_random(const T& value);
    void swap(const position& a, const position& b);
    const T& get(const position& where);
    void set(const position& where, const T value);
    std::vector<T> neighbors(const position& origin, int radius = 1);

  private:
    static constexpr int rng_failure_tolerance = 256;

    int size_;
    std::vector<T> table_;
    random_number_generator rng;
};

#include "grid.ipp"

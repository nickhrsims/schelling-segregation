#pragma once

#include <stdexcept>

#include "grid.h"

template <typename T>
grid<T>::grid(int p_size, const T p_base) : size_{p_size}, rng{0, p_size - 1} {
    for (int count = 0; count < (p_size * p_size); ++count) {
        table_.push_back(p_base);
    }
}

template <typename T> int grid<T>::size() { return size_; }

template <typename T> const grid<T>::position grid<T>::find_random(const T& p_value) {
    for (int iterations = 0; iterations < rng_failure_tolerance; ++iterations) {
        position selection{rng(), rng()};
        if (get(selection) == p_value) {
            return selection;
        }
    }

    throw std::logic_error("Limit reached before vacancy could be found!");
}

template <typename T>
void grid<T>::swap(const position& p_first, const position& p_second) {
    T a_prev{get(p_first)};
    set(p_first, get(p_second));
    set(p_second, a_prev);
}

template <typename T> const T& grid<T>::get(const position& p_position) {
    return table_[(p_position.row * size_) + p_position.col];
}

template <typename T> void grid<T>::set(const position& p_position, const T p_value) {
    table_[(p_position.row * size_) + p_position.col] = p_value;
}

template <typename T>
std::vector<T> grid<T>::neighbors(const position& p_position, int p_radius) {
    std::vector<T> neighbor_list;
    for (auto row_mutation = -p_radius; row_mutation <= p_radius; ++row_mutation) {
        for (auto col_mutation = -p_radius; col_mutation <= p_radius; ++col_mutation) {
            if (p_position.row + row_mutation < 0 ||
                size_ <= p_position.col + col_mutation) {
                continue;
            }
            position neighbor_position{p_position.col + col_mutation,
                                       p_position.row + row_mutation};
            neighbor_list.push_back(get(neighbor_position));
        }
    }
    return neighbor_list;
}

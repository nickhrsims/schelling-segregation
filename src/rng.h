#pragma once

#include <random>

// src: https://stackoverflow.com/a/7560564
class random_number_generator {
  public:
    random_number_generator(int low, int high);
    int operator()();

  private:
    std::mt19937 generator;
    std::uniform_int_distribution<> distribution;
};

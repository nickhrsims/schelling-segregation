#include "rng.h"

random_number_generator::random_number_generator(int low, int high) {
    std::random_device random_device;
    generator    = std::mt19937{random_device()};
    distribution = std::uniform_int_distribution<>(low, high);
}

int random_number_generator::operator()() { return distribution(generator); }

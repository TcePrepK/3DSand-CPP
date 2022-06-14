//
// Created by Shrimp on 1/5/2022.
//

#include "RNG.h"

int RNG::randomInt(int lower, int upper) {
    std::uniform_real_distribution<double> dist(lower, upper + 1);
    return (int) dist(rng);
}

float RNG::randomFloat(int lower, int upper) {
    std::uniform_real_distribution<double> dist(lower, upper + 1);
    return (float) dist(rng);
}

//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_MATHS_H
#define INC_2DSAND_MATHS_H


#include <random>

static float lerp(float v0, float v1, float t) {
    return (1.f - t) * v0 + t * v1;
}

static float clamp(float val, float min, float max) {
    if (val < min)
        return min;
    if (val > max)
        return max;
    return val;
}


#endif //INC_2DSAND_MATHS_H

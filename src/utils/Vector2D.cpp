//
// Created by Shrimp on 4/10/2022.
//

#include <cmath>
#include "Vector2D.h"

Vector2D::Vector2D() : x(0), y(0) {}

Vector2D::Vector2D(float x, float y) : x(x), y(y) {}

float Vector2D::length() const {
    return std::sqrt(x * x + y * y);
}

float Vector2D::dot(const Vector2D &vec) const {
    return x * vec.x + y * vec.y;
}

Vector2D Vector2D::normalize() const {
    Vector2D vec;
    const float len = length();
    if (len == 0) {
        return vec;
    }

    return vec / len;
}

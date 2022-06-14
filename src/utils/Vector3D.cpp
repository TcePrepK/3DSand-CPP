//
// Created by Shrimp on 12/30/2021.
//

#include <cmath>
#include <sstream>
#include "Vector3D.h"
#include "glm/common.hpp"

float Vector3D::length() const {
    return std::sqrt(x * x + y * y + z * z);
}

float Vector3D::dot(const Vector3D &vec) const {
    return x * vec.x + y * vec.y + z * vec.z;
}

Vector3D Vector3D::cross(const Vector3D &vec) const {
    return {y * vec.z - z * vec.y, z * vec.x - x * vec.z, x * vec.y - y * vec.x};
}

Vector3D Vector3D::abs() const {
    return {glm::abs(x), glm::abs(y), glm::abs(z)};
}

Vector3D Vector3D::floor() const {
    return {glm::floor(x), glm::floor(y), glm::floor(z)};
}

Vector3D Vector3D::normalize() const {
    Vector3D vec;
    const float len = length();
    if (len == 0) {
        return vec;
    }

    return vec / len;
}

std::string Vector3D::toString() const {
    std::ostringstream ostr;
    ostr << "(X: " << x << ", Y: " << y << ", Z: " << z << ")";
    return ostr.str();
}

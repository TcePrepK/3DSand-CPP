//
// Created by Shrimp on 12/30/2021.
//

#ifndef INC_2DSAND_VECTOR3D_H
#define INC_2DSAND_VECTOR3D_H


#include <string>

class Vector3D {
public:
    float x, y, z;

    Vector3D() : x(0), y(0), z(0) {}

    Vector3D(float x, float y, float z) : x(x), y(y), z(z) {}

    explicit Vector3D(float v) : x(v), y(v), z(v) {}

    Vector3D(int x, int y, int z) : x((float) x), y((float) y), z((float) z) {}

    explicit Vector3D(int v) : x((float) v), y((float) v), z((float) v) {}

    Vector3D(unsigned int x, unsigned int y, unsigned int z) : x((float) x), y((float) y), z((float) z) {}

    explicit Vector3D(unsigned int v) : x((float) v), y((float) v), z((float) v) {}

    Vector3D operator+(const Vector3D &vec) const {
        return {x + vec.x, y + vec.y, z + vec.z};
    }

    void operator+=(const Vector3D &vec) {
        x += vec.x;
        y += vec.y;
        z += vec.z;
    }

    Vector3D operator-(const Vector3D &vec) const {
        return {x - vec.x, y - vec.y, z - vec.z};
    }

    Vector3D operator-(const int v) const {
        return {x - (float) v, y - (float) v, z - (float) v};
    }

    void operator-=(const Vector3D &vec) {
        x -= vec.x;
        y -= vec.y;
        z -= vec.z;
    }

    Vector3D operator*(const Vector3D &vec) const {
        return {x * vec.x, y * vec.y, z * vec.z};
    }

    Vector3D operator*(const float &num) const {
        return {x * num, y * num, z * num};
    }

    Vector3D operator/(const Vector3D &vec) const {
        return {x / vec.x, y / vec.y, z / vec.z};
    }

    Vector3D operator/(const float &num) const {
        return {x / num, y / num, z / num};
    }

    Vector3D operator%(const int &num) const {
        return {(int) x % num, (int) y % num, (int) z % num};
    }

    bool operator==(const Vector3D &vector) const {
        return x == vector.x && y == vector.y && z == vector.z;
    }

    bool operator!=(const Vector3D &vector) const {
        return !(x == vector.x && y == vector.y && z == vector.z);
    }

    [[nodiscard]] float length() const;

    [[nodiscard]] float dot(const Vector3D &vec) const;

    [[nodiscard]] Vector3D cross(const Vector3D &vec) const;

    [[nodiscard]] Vector3D abs() const;

    [[nodiscard]] Vector3D floor() const;

    [[nodiscard]] Vector3D normalize() const;

    [[nodiscard]] std::string toString() const;
};


#endif //INC_2DSAND_VECTOR3D_H

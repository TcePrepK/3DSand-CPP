//
// Created by Shrimp on 4/10/2022.
//

#ifndef INC_2DSAND_VECTOR2D_H
#define INC_2DSAND_VECTOR2D_H


class Vector2D {
public:
    float x, y;

    Vector2D();

    Vector2D(float x, float y);

    Vector2D operator+(const Vector2D &vec) const {
        return {x + vec.x, y + vec.y};
    }

    Vector2D operator-(const Vector2D &vec) const {
        return {x - vec.x, y - vec.y};
    }

    Vector2D operator*(const Vector2D &vec) const {
        return {x * vec.x, y * vec.y};
    }

    Vector2D operator/(const Vector2D &vec) const {
        return {x / vec.x, y / vec.y};
    }

    Vector2D operator*(const float &num) const {
        return {x * num, y * num};
    }

    Vector2D operator/(const float &num) const {
        return {x / num, y / num};
    }

    [[nodiscard]] float length() const;

    [[nodiscard]] float dot(const Vector2D &vec) const;

    [[nodiscard]] Vector2D normalize() const;
};


#endif //INC_2DSAND_VECTOR2D_H

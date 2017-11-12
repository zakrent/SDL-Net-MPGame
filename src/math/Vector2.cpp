//
// Created by zakrent on 9/26/17.
//

#include "Vector2.h"

namespace math {
    Vector2::Vector2(long double x, long double y) : x(x), y(y) {}

    Vector2::~Vector2() = default;

    void Vector2::normalize() {
        auto length = (long double) (sqrt(pow((double)x, 2) + pow((double)y, 2)));
        x /= length;
        y /= length;
    }

    Vector2 Vector2::operator+(Vector2 SecVector) {
        return Vector2(this->x + SecVector.x, this->y + SecVector.y);
    }

    Vector2 Vector2::operator-(Vector2 SecVector) {
        return Vector2(this->x - SecVector.x, this->y - SecVector.y);
    }

    Vector2 Vector2::operator*(long double mul) {
        return Vector2(this->x * mul, this->y * mul);
    }

    void Vector2::operator+=(Vector2 SecVector) {
        this->x += SecVector.x;
        this->y += SecVector.y;
    }

    void Vector2::operator-=(Vector2 SecVector) {
        this->x -= SecVector.x;
        this->y -= SecVector.y;
    }

    void Vector2::operator*=(long double mul) {
        this->x *= mul;
        this->y *= mul;
    }
}


//
// Created by zakrent on 9/26/17.
//

#ifndef GAME_MP_SERVER_VECTOR2_H
#define GAME_MP_SERVER_VECTOR2_H

namespace math {

    class Vector2 {
    public:
        long double x, y;

        void normalize();

        Vector2 operator+(Vector2 SecVector);

        Vector2 operator-(Vector2 SecVector);

        Vector2 operator*(long double mul);

        void operator+=(Vector2 SecVector);

        void operator-=(Vector2 SecVector);

        void operator*=(long double mul);

        Vector2(long double x, long double y);

        ~Vector2();
    };

    inline bool operator==(const Vector2 &first, const Vector2 &second) {
        return first.x == second.x && first.y == second.y;
    }

}
#endif //GAME_MP_SERVER_VECTOR2_H

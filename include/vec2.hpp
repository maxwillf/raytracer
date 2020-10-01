#ifndef __VEC2_H_
#define __VEC2_H_
//==================================================================================================
// Written in 2016 by Peter Shirley <ptrshrl@gmail.com>
//
// To the extent possible under law, the author(s) have dedicated all copyright and related and
// neighboring rights to this software to the public domain worldwide. This software is distributed
// without any warranty.
//
// You should have received a copy (see file COPYING.txt) of the CC0 Public Domain Dedication along
// with this software. If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
//==================================================================================================

#include <math.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

class vec2
{
    public:
        vec2() {}
        vec2(std::vector<float> vec)
        {
            if (vec.size() == 2)
            {
                e[0] = vec[0];
                e[1] = vec[1];
            }
            else
            {
                throw std::runtime_error("Vector cannot be converted to vec2");
            }
        }
        vec2(float e0, float e1)
        {
            e[0] = e0;
            e[1] = e1;
        }
        inline float x() const { return e[0]; }
        inline float y() const { return e[1]; }

        inline const vec2 &operator+() const { return *this; }
        inline vec2 operator-() const { return vec2(-e[0], -e[1]); }
        inline float operator[](int i) const { return e[i]; }
        inline float &operator[](int i) { return e[i]; }

        inline vec2 &operator+=(const vec2 &v2);
        inline vec2 &operator-=(const vec2 &v2);
        inline vec2 &operator*=(const vec2 &v2);
        inline vec2 &operator/=(const vec2 &v2);
        inline vec2 &operator*=(const float t);
        inline vec2 &operator/=(const float t);
        inline bool operator==(vec2 const &v) const;
        inline bool operator!=(vec2 const &v) const;

        inline float length() const { return sqrt(e[0] * e[0] + e[1] * e[1]); }
        inline float squared_length() const { return e[0] * e[0] + e[1] * e[1]; }
        inline void make_unit_vector();

        float e[3];
};

inline std::istream &operator>>(std::istream &is, vec2 &t)
{
    is >> t.e[0] >> t.e[1];
    return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec2 &t)
{
    os << int(t.e[0]) << " " << int(t.e[1]);
    return os;
}

inline void vec2::make_unit_vector()
{
    float k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1]);
    e[0] *= k;
    e[1] *= k;
}

inline vec2 operator+(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1]);
}

inline vec2 operator-(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1]);
}

inline vec2 operator*(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1]);
}

inline vec2 operator/(const vec2 &v1, const vec2 &v2)
{
    return vec2(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1]);
}

inline vec2 operator*(float t, const vec2 &v)
{
    return vec2(t * v.e[0], t * v.e[1]);
}

inline vec2 operator/(vec2 v, float t)
{
    return vec2(v.e[0] / t, v.e[1] / t);
}

inline vec2 operator*(const vec2 &v, float t)
{
    return vec2(t * v.e[0], t * v.e[1]);
}

inline float dot(const vec2 &v1, const vec2 &v2)
{
    return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

//inline vec2 cross(const vec2 &v1, const vec2 &v2)
//{
//    return vec2(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
//                v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
//                v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
//}

inline vec2 &vec2::operator+=(const vec2 &v)
{
    e[0] += v.e[0];
    e[1] += v.e[1];
    return *this;
}

inline vec2 &vec2::operator*=(const vec2 &v)
{
    e[0] *= v.e[0];
    e[1] *= v.e[1];
    return *this;
}

inline vec2 &vec2::operator/=(const vec2 &v)
{
    e[0] /= v.e[0];
    e[1] /= v.e[1];
    return *this;
}

inline vec2 &vec2::operator-=(const vec2 &v)
{
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    return *this;
}

inline vec2 &vec2::operator*=(const float t)
{
    e[0] *= t;
    e[1] *= t;
    return *this;
}

inline vec2 &vec2::operator/=(const float t)
{
    float k = 1.0f / t;

    e[0] *= k;
    e[1] *= k;
    return *this;
}

inline bool vec2::operator==(vec2 const &v) const
{
    for (size_t i = 0; i < 2; i++)
    {
        if (e[i] != v[i])
        {
            return false;
        }
    }
    return true;
}

inline bool vec2::operator!=(vec2 const &v) const
{
  return !(*this == v);
}

inline vec2 unit_vector(vec2 v)
{
  return v / v.length();
}

using Point2 = vec2;

#endif // __VEC2_H_

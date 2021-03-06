#ifndef VEC3H
#define VEC3H
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

class vec3
{
public:
  vec3() {}
  vec3(std::vector<double> vec)
  {
    if (vec.size() == 3)
    {
      e[0] = vec[0];
      e[1] = vec[1];
      e[2] = vec[2];
    }
    else
    {
      throw std::runtime_error("Vector cannot be converted to vec3");
    }
  }
  vec3(double e0, double e1, double e2)
  {
    e[0] = e0;
    e[1] = e1;
    e[2] = e2;
  }
  inline double x() const { return e[0]; }
  inline double y() const { return e[1]; }
  inline double z() const { return e[2]; }
  inline double r() const { return e[0]; }
  inline double g() const { return e[1]; }
  inline double b() const { return e[2]; }

  inline const vec3 &operator+() const { return *this; }
  inline vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
  inline double operator[](int i) const { return e[i]; }
  inline double &operator[](int i) { return e[i]; }

  inline vec3 &operator+=(const vec3 &v2);
  inline vec3 &operator-=(const vec3 &v2);
  inline vec3 &operator*=(const vec3 &v2);
  inline vec3 &operator/=(const vec3 &v2);
  inline vec3 &operator*=(const double t);
  inline vec3 &operator/=(const double t);

  inline double length() const { return sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]); }
  inline double squared_length() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
  inline void make_unit_vector();

  double e[3];
};

inline std::istream &operator>>(std::istream &is, vec3 &t)
{
  is >> t.e[0] >> t.e[1] >> t.e[2];
  return is;
}

inline std::ostream &operator<<(std::ostream &os, const vec3 &t)
{
  os << int(t.e[0]) << " " << int(t.e[1]) << " " << int(t.e[2]);
  return os;
}

inline void vec3::make_unit_vector()
{
  double k = 1.0 / sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
}

inline vec3 operator+(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] + v2.e[0], v1.e[1] + v2.e[1], v1.e[2] + v2.e[2]);
}

inline vec3 operator-(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] - v2.e[0], v1.e[1] - v2.e[1], v1.e[2] - v2.e[2]);
}

inline vec3 operator*(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] * v2.e[0], v1.e[1] * v2.e[1], v1.e[2] * v2.e[2]);
}

inline vec3 operator/(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[0] / v2.e[0], v1.e[1] / v2.e[1], v1.e[2] / v2.e[2]);
}

inline vec3 operator*(double t, const vec3 &v)
{
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline vec3 operator/(vec3 v, double t)
{
  return vec3(v.e[0] / t, v.e[1] / t, v.e[2] / t);
}

inline vec3 operator*(const vec3 &v, double t)
{
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

inline double dot(const vec3 &v1, const vec3 &v2)
{
  return v1.e[0] * v2.e[0] + v1.e[1] * v2.e[1] + v1.e[2] * v2.e[2];
}

inline vec3 cross(const vec3 &v1, const vec3 &v2)
{
  return vec3(v1.e[1] * v2.e[2] - v1.e[2] * v2.e[1],
              v1.e[2] * v2.e[0] - v1.e[0] * v2.e[2],
              v1.e[0] * v2.e[1] - v1.e[1] * v2.e[0]);
}

inline vec3 &vec3::operator+=(const vec3 &v)
{
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

inline vec3 &vec3::operator*=(const vec3 &v)
{
  e[0] *= v.e[0];
  e[1] *= v.e[1];
  e[2] *= v.e[2];
  return *this;
}

inline vec3 &vec3::operator/=(const vec3 &v)
{
  e[0] /= v.e[0];
  e[1] /= v.e[1];
  e[2] /= v.e[2];
  return *this;
}

inline vec3 &vec3::operator-=(const vec3 &v)
{
  e[0] -= v.e[0];
  e[1] -= v.e[1];
  e[2] -= v.e[2];
  return *this;
}

inline vec3 &vec3::operator*=(const double t)
{
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

inline vec3 &vec3::operator/=(const double t)
{
  double k = 1.0f / t;

  e[0] *= k;
  e[1] *= k;
  e[2] *= k;
  return *this;
}

inline vec3 unit_vector(vec3 v)
{
  return v / v.length();
}

#endif
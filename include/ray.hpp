#pragma once
#include "vec3.hpp"
#include <climits>
#include <limits>

class Ray
{
public:
  Ray(const Point &o, const vec3 &d) : o{o}, d{d}
    { /*empty*/
      tMin = 0;
      tMax = std::numeric_limits<double>::max();
    }
    Point operator()(float t) const
    {
      return o + d * t;
    }
    vec3 origin() const { return o; }
    vec3 direction() const { return d; }
    double mutable tMin; //!< origin
    double mutable tMax; //!< origin

  private:
  vec3 o; //!< origin
  vec3 d; //!< direction
  // ... the methods goes here
};

#pragma once
#include "vec3.h"

class Ray
{
public:
  Ray(const Point &o, const vec3 &d) : o{o}, d{d}
  { /*empty*/
  }
  Point operator()(float t) const
  {
    return o + d * t;
  }

private:
  vec3 o; //!< origin
  vec3 d; //!< direction
  // ... the methods goes here
};

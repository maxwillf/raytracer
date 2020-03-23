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
  vec3 origin() const { return o; }
  vec3 direction() const { return d; }

private:
  vec3 o; //!< origin
  vec3 d; //!< direction
  // ... the methods goes here
};

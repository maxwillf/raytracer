#pragma once
#include "vec3.h"

class Ray
{
public:
  Ray(const vec3 &o, const vec3 &d) : o{o}, d{d}
  { /*empty*/
  }

private:
  vec3 o; //!< origin
  vec3 d; //!< direction
  // ... the methods goes here
  vec3 operator()(float t) const
  {
    return o + d * t;
  }
};

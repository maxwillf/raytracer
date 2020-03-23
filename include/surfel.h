#include "vec3.h"

class Surfel
{
public:
  Surfel(const Point &p, const vec3 &n, const vec3 &wo, float time,
         const Point2f &uv, const Primitive *pri)
      : p{p}, n{n}, wo{wo}, time{time}, uv{uv}, primitive{pri} {/* empty */};

  Point p;                              //!< Contact point.
  vec3 n;                               //!< The surface normal.
  vec3 wo;                              //!< Outgoing direction of light, which is -ray.
  float time;                           //!< Time of contact.
  Point2f uv;                           //!< Parametric coordinate (u,v) of the hit surface.
  const Primitive *primitive = nullptr; //!< Pointer to the primitive.
};
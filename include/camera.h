#ifndef __CAMERA__
#define __CAMERA__

#include "vec3.h"
#include "film.h"
#include "argument.h"
#include <memory>
#include "factory.hpp"

class Camera
{
public:
  std::shared_ptr<Film> film;
  // camera frame
  vec3 gaze;
  vec3 w;
  vec3 u;
  vec3 v;
  Point e;

  Camera(){};
  static Camera *Make(Arguments args) { return nullptr; };
  void setFilm(std::shared_ptr<Film> film)
  {
    this->film = film;
  }
  void setFrame(Arguments args)
  {
    if (get<0>(args) == "lookat")
    {
      auto arguments = get<1>(args);
      vec3 look_from = findAttribute(arguments, "look_from").getValues<float>();
      vec3 look_at = findAttribute(arguments, "look_at").getValues<float>();
      vec3 up = findAttribute(arguments, "up").getValues<float>();

      gaze = look_at - look_from;
      w = unit_vector(gaze);
      u = unit_vector(cross(up, w));
      v = unit_vector(cross(w, u));
      e = look_from;
    }
  };
  // Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  friend DerivedRegistrar<Camera, Camera>;
};

#endif
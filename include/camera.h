#ifndef __CAMERA__
#define __CAMERA__

#include "vec3.h"
#include "argument.h"
#include "factory.hpp"

class Camera
{
private:
  // vec3 position;
  // vec3 target;
  // vec3 up;

public:
  Camera(){};
  static Camera *Make(Arguments args) { return nullptr; };
  // Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  ~Camera();

  //  friend DerivedRegistrar<Camera, Camera>;
};

#endif
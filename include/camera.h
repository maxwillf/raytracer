#pragma once

#include "vec3.h"
#include "argument.h"
#include "Factory.hpp"

class Camera
{
private:
  // vec3 position;
  // vec3 target;
  // vec3 up;

public:
  Camera(){};
  static Camera *Make(Arguments args){return nullptr;};
  // Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  ~Camera();

//  friend DerivedRegistrar<Camera, Camera>;
};

//DerivedRegistrar<Camera,Camera> ___initCamera;
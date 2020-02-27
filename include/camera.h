#pragma once

#include "vec3.h"
#include "argument.h"

class Camera
{
private:
  // vec3 position;
  // vec3 target;
  // vec3 up;

public:
  Camera(){};
  virtual Camera *Make(Argument args) = 0;
  // Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  ~Camera();
};
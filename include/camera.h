#include "vec3.h"

class Camera
{
private:
  vec3 position;
  vec3 target;
  vec3 up;

public:
  Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  ~Camera();
};
#include "camera.h"

class OrtographicCamera : Camera
{
private:
  // vec3 position;
  // vec3 target;
  // vec3 up;

public:
  OrtographicCamera(){};

  Camera *Make(Arguments args)
  {
    if (get<0>(args) == "ortographic")
    {
      return new OrtographicCamera();
    }
    else
    {
      return nullptr;
    }
  };
  // ~OrtographicCamera();
};
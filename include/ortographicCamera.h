#include "camera.h"

class OrtographicCamera : Camera
{
private:
  // vec3 position;
  // vec3 target;
  // vec3 up;

public:
  OrtographicCamera(){};

  static Camera *Make(Arguments args)
  {
    if (get<1>(args)[0].getKey() == "orthographic")
    {
      return new OrtographicCamera();
    }
    else
    {
      return nullptr;
    }
  };
  // ~OrtographicCamera();
  friend DerivedRegistrar<Camera, OrtographicCamera>;
};

DerivedRegistrar<Camera, OrtographicCamera> __initOrtographic;
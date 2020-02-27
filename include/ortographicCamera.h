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
    if (get<0>(args) == "orthographic")
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

template <>
std::vector<Factory<Camera,Arguments>::ReadFunPtr> Factory<Camera,Arguments>::registeredFuns = std::vector<Factory<Camera,Arguments>::ReadFunPtr>();
DerivedRegistrar<Camera,OrtographicCamera> __initOrtographic;
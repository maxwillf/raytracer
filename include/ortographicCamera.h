#include "camera.h"

class OrtographicCamera : Camera
{
private:
  std::vector<float> screenWindow;

public:
  OrtographicCamera(){};

  static Camera *Make(Arguments args)
  {
    if (get<1>(args)[0].getValue<std::string>() == "orthographic")
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

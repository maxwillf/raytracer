#include "camera.h"

class PerspectiveCamera : Camera
{
private:
    int fovy;

public:
  PerspectiveCamera(std::vector<Argument> attributes){
    fovy = findAttribute(attributes, "fovy").getValue<int>();
  };

  static Camera *Make(Arguments args)
  {
    if (get<1>(args)[0].getValue<std::string>() == "perspective")
    {
      return new PerspectiveCamera(get<1>(args));
    }
    else
    {
      return nullptr;
    }
  };
  // ~PerspectiveCamera();
  friend DerivedRegistrar<Camera, PerspectiveCamera>;
};

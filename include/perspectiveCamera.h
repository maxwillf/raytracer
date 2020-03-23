#include "camera.h"

class PerspectiveCamera : Camera
{
private:
  int fovy;

public:
  PerspectiveCamera(std::vector<Argument> attributes)
  {
    fovy = findAttribute(attributes, "fovy").getValue<int>();
  };

  Ray generate_ray(int x, int y)
  {
    float u = screenWindow[0] + (screenWindow[1] - screenWindow[0]) * (float(x) + 0.5) / float(film->getWidth());
    float v = screenWindow[2] + (screenWindow[3] - screenWindow[2]) * (float(y) + 0.5) / float(film->getHeight());
    return Ray(this->e, this->w + u * this->u + v * this->v);
  }

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

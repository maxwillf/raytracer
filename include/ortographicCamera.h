#include "camera.h"
#include "ray.h"

class OrtographicCamera : Camera
{
private:
  // l r b t

public:
  OrtographicCamera(){};

  Ray generate_ray(int x, int y)
  {
    float u = screenWindow[0] + (screenWindow[1] - screenWindow[0]) * (x + 0.5) / film->getWidth();
    float v = screenWindow[3] + (screenWindow[4] - screenWindow[3]) * (y + 0.5) / film->getHeight();
    return Ray(this->e + u * this->u + v * this->v, this->w);
  }

  static Camera *Make(Arguments args)
  {
    if (get<1>(args)[0].getValue<std::string>() == "orthographic")
    {
      OrtographicCamera *camera = new OrtographicCamera();
      for (auto &&arg : get<1>(args))
      {
        if (arg.getKey() == "screen_window")
        {
          camera->screenWindow = arg.getValues<float>();
        }
      }
      return camera;
    }
    else
    {
      return nullptr;
    }
  };
  // ~OrtographicCamera();
  friend DerivedRegistrar<Camera, OrtographicCamera>;
};

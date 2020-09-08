#include "camera.h"
#include "math.h"

class PerspectiveCamera : public Camera
{
private:
  int fovy;

public:
  PerspectiveCamera(std::vector<Argument> attributes)
  {
    std::cout << "creating perspective camera" << std::endl;
    fovy = findAttribute(attributes, "fovy").getValue<int>();
    // float h = tan(fovy);
    // float aspectRatio = wid
    // screen_window[0] =
  };

  void setFilm(std::shared_ptr<Film> film) override
  {
    this->film = film;
    float h = tan(fovy);
    float aspectRatio = (float)film->getWidth() / (float)film->getHeight();

    std::cout << h << " " << aspectRatio << std::endl;

    screenWindow = std::vector<float>{-aspectRatio * h, aspectRatio * h, -h, h};

    for (size_t i = 0; i < screenWindow.size(); i++)
    {
      std::cout << screenWindow[i] << std::endl;
    }
  }
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

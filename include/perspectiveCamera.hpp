#include "camera.hpp"
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
    // double h = tan(fovy);
    // double aspectRatio = wid
    // screen_window[0] =
  };

  void setFilm(std::shared_ptr<Film> film) override
  {
    this->film = film;
    double h = std::tan(M_PI / 180.0 * fovy / 2.0);
    double aspectRatio = (double)film->getWidth() / (double)film->getHeight();

    std::cout << h << " " << aspectRatio << std::endl;

    screenWindow = std::vector<double>{-aspectRatio * h, aspectRatio * h, -h, h};

    for (size_t i = 0; i < screenWindow.size(); i++)
    {
      std::cout << screenWindow[i] << std::endl;
    }
  }
  Ray generate_ray(int x, int y) const override
  {
    double u = screenWindow[0] + (screenWindow[1] - screenWindow[0]) * (double(x) + 0.5) / double(film->getWidth());
    double v = screenWindow[2] + (screenWindow[3] - screenWindow[2]) * (double(y) + 0.5) / double(film->getHeight());
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

#include "camera.hpp"
#include "ray.hpp"

class OrtographicCamera : Camera
{
private:
  // l r b t

public:
  OrtographicCamera(std::vector<Argument> args)
  {
    for (auto &&arg : args)
    {
      if (arg.getKey() == "screen_window")
      {
        screenWindow = arg.getValues<float>();
      }
    }
  };

    Ray generate_ray(int x, int y) const
    {
      float u = screenWindow[0] + (x + 0.5) * (screenWindow[1] - screenWindow[0]) / film->getWidth();
      float v = screenWindow[2] + (y + 0.5) * (screenWindow[3] - screenWindow[2]) / film->getHeight();
      return Ray(this->e + u * this->u + v * this->v, this->w);
    }

  static Camera *Make(Arguments args)
  {
    if (get<1>(args)[0].getValue<std::string>() == "orthographic")
    {
      return new OrtographicCamera(get<1>(args));
    }
    else
    {
      return nullptr;
    }
  };
  // ~OrtographicCamera();
  void setFilm(std::shared_ptr<Film> film)
  {
    this->film = film;

    if (screenWindow.empty())
    {

      float xratio, yratio;
      yratio = std::max(film->getHeight(), film->getWidth()) / float(film->getWidth());
      xratio = std::max(film->getHeight(), film->getWidth()) / float(film->getHeight());
      screenWindow = std::vector<float>{-xratio, xratio, -yratio, yratio};
    }
    //    std::cout << "common setFilm" << std::endl;
  }
  friend DerivedRegistrar<Camera, OrtographicCamera>;
};

#ifndef __CAMERA__
#define __CAMERA__

#include "vec3.hpp"
#include "film.hpp"
#include "ray.hpp"
#include "argument.hpp"
#include <memory>
#include "factory.hpp"
#include "algorithm"

class Camera
{
public:
  std::shared_ptr<Film> film;
  // camera frame
  vec3 gaze;
  vec3 w;
  vec3 u;
  vec3 v;
  Point e;
  std::vector<float> screenWindow;

    virtual Ray generate_ray (int x, int y) const = 0;

    Camera(){};
    static Camera *Make(Arguments args) { return nullptr; };
    virtual void setFilm(std::shared_ptr<Film> film)
  {
    this->film = film;

    if (screenWindow.empty())
    {

      float xratio, yratio;
      yratio = std::max(film->getHeight(), film->getWidth()) / float(film->getWidth());
      xratio = std::max(film->getHeight(), film->getWidth()) / float(film->getHeight());
      screenWindow = std::vector<float>{-xratio, xratio, -yratio, yratio};
    }
    std::cout << "common setFilm" << std::endl;
  }
  void setFrame(Arguments args)
  {
    if (get<0>(args) == "lookat")
    {
      auto arguments = get<1>(args);
      vec3 look_from = findAttribute(arguments, "look_from").getValues<float>();
      vec3 look_at = findAttribute(arguments, "look_at").getValues<float>();
      vec3 up = findAttribute(arguments, "up").getValues<float>();

      gaze = look_at - look_from;
      w = unit_vector(gaze);
      u = unit_vector(cross(up, w));
      v = unit_vector(cross(w, u));
      e = look_from;
    }
  };
  // Camera(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  friend DerivedRegistrar<Camera, Camera>;
};

#endif

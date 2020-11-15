#include "argument.hpp"
#include "include/material.hpp"
#include "include/vec2.hpp"
#include "primitive.hpp"
#include <cmath>
#include <memory>
class Sphere : Primitive
{
private:
  double radius;
  vec3 center;

public:
  //  virtual ~Primitive();
  bool intersect(const Ray &r, Surfel *sf) const;
  // Simpler & faster version of intersection that only return true/false.
  // It does not compute the hit point information.
  bool intersect_p(const Ray &r) const;

  //  virtual const Material *get_material(void) const = {return material;}
  Sphere(std::vector<Argument> args)
  {
    radius = findAttribute(args, "radius").getValue<double>();
    center = findAttribute(args, "center").getValues<double>();
  }

  static Primitive *Make(Arguments args)
  {
    if (get<1>(args)[0].getValue<std::string>() == "sphere")
    {
      return new Sphere(get<1>(args));
    }
    else
    {
      return nullptr;
    }
  };
  std::shared_ptr<Material> material;

  friend DerivedRegistrar<Primitive, Sphere>;
};

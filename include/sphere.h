#include "argument.h"
#include "primitive.h"

class Sphere : Primitive
{
private:
  float radius;
  vec3 center;

public:
  //  virtual ~Primitive();
  //  virtual bool intersect(const Ray &r, Surfel *sf) const = 0;
  // Simpler & faster version of intersection that only return true/false.
  // It does not compute the hit point information.
  virtual bool intersect_p(const Ray &r) const
  {
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discrimant = b * b - 4 * a * c;
    return (discrimant > 0);
  };
  //  virtual const Material *get_material(void) const = {return material;}
  Sphere(std::vector<Argument> args)
  {
    radius = findAttribute(args, "radius").getValue<float>();
    center = findAttribute(args, "center").getValues<float>();
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

  //  std::shared_ptr<Material> material;
};
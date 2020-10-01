#pragma once

#include "ray.hpp"
#include "factory.hpp"

class Surfel;

class Primitive
{
  public:
      //virtual ~Primitive(){};
      virtual bool intersect(const Ray &r, Surfel *sf) const = 0;
      // Simpler & faster version of intersection that only return true/false.
      // It does not compute the hit point information.
      virtual bool intersect_p(const Ray &r) const = 0;
      static Primitive *Make(Arguments args)
      {
        return nullptr;
      }
      //  virtual const Material *get_material(void) const = {return material;}
    private:
      //  std::shared_ptr<Material> material;

      friend DerivedRegistrar<Primitive, Primitive>;
  };


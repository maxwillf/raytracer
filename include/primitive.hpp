#pragma once

#include "ray.hpp"
#include "factory.hpp"
#include "material.hpp"
#include <memory>
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
    virtual const std::shared_ptr<Material> material_get(void) const {return material;}
    virtual void setMaterial(std::shared_ptr<Material> mat) {material = mat;}

  private:
       std::shared_ptr<Material> material;

    friend DerivedRegistrar<Primitive, Primitive>;
  };


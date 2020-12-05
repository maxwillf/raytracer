#ifndef __AGGREGATE_H_
#define __AGGREGATE_H_

#include "ray.hpp"
#include "primitive.hpp"
#include "surfel.hpp"
#include "factory.hpp"
#include <memory>
#include <tuple>
#include <vector>

class Aggregate : public Primitive
{
public:
    Aggregate()
    {
        primitives = std::vector<shared_ptr<Primitive>>();
    }

    std::vector<shared_ptr<Primitive>> getPrimitives()
    {
        return primitives;
    }

    void addPrimitive(shared_ptr<Primitive> obj)
    {
        primitives.push_back(obj);
    }

    bool intersect_p(const Ray &r) const
    {
        for (auto &primitive : primitives)
        {

            if (primitive->intersect_p(r))
            {
                return true;
            }
        }
        return false;
    };

    bool intersect(const Ray &r, Surfel *sf) const
    {
        bool intersected = false;
        for (auto &primitive : primitives)
        {

            if (primitive->intersect(r, sf))
            {
                intersected = true;
            }
        }
        return intersected;
    }
    bool bounding_box(double time0, double time1, aabb &output_box) const;
    //        Material *get_material(void) const = {return material ;}
private:
    std::vector<shared_ptr<Primitive>> primitives;
    //  std::shared_ptr<Material> material;
    friend DerivedRegistrar<Primitive, Primitive>;
};

#endif // __AGGREGATE_H_

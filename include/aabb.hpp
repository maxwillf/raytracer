#ifndef AABB_H
#define AABB_H
#include "vec3.hpp"
#include "primitive.hpp"
#include "ray.hpp"

// class Primitive;

class aabb
{
public:
    aabb() {}
    aabb(const vec3 &a, const vec3 &b)
    {
        minimum = a;
        maximum = b;
    }

    vec3 min() const { return minimum; }
    vec3 max() const { return maximum; }

    bool hit(const Ray &r) const
    {
        for (int a = 0; a < 3; a++)
        {
            auto invD = 1.0f / r.direction()[a];
            auto t0 = (min()[a] - r.origin()[a]) * invD;
            auto t1 = (max()[a] - r.origin()[a]) * invD;
            if (invD < 0.0f)
                std::swap(t0, t1);
            r.tMin = t0 > r.tMin ? t0 : r.tMin;
            r.tMax = t1 < r.tMax ? t1 : r.tMax;
            if (r.tMax <= r.tMin)
                return false;
        }
        return true;
    }

    vec3 minimum;
    vec3 maximum;
};

inline aabb surrounding_box(aabb box0, aabb box1)
{
    vec3 small(fmin(box0.min().x(), box1.min().x()),
               fmin(box0.min().y(), box1.min().y()),
               fmin(box0.min().z(), box1.min().z()));

    vec3 big(fmax(box0.max().x(), box1.max().x()),
             fmax(box0.max().y(), box1.max().y()),
             fmax(box0.max().z(), box1.max().z()));

    return aabb(small, big);
}
inline bool list_bounding_box(std::vector<Primitive> objects, double time0, double time1, aabb &output_box)
{
    if (objects.empty())
        return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto &object : objects)
    {
        if (!object.bounding_box(time0, time1, temp_box))
            return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}
// bool list_bounding_box(std::vector<Primitive> objects, double time0, double time1, aabb &output_box);
// aabb surrounding_box(aabb box0, aabb box1);

#endif
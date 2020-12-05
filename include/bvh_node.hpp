#ifndef BVH_H
#define BVH_H

#include "primitive.hpp"
#include "aabb.hpp"
#include "surfel.hpp"
#include "ray.hpp"

class bvh_node : public Primitive
{
public:
    bvh_node();

    // bvh_node(const Primitive_list &list, double time0, double time1)
    //     : bvh_node(list.objects, 0, list.objects.size(), time0, time1)
    // {
    // }

    bvh_node(
        const std::vector<shared_ptr<Primitive>> &src_objects,
        size_t start, size_t end, double time0, double time1);

    bool intersect(
        const Ray &r, Surfel *rec) const;

    bool intersect_p(
        const Ray &r) const;

    bool bounding_box(double time0, double time1, aabb &output_box) const;
    // bool bvh_node::bounding_box(double time0, double time1, aabb &output_box) const;

    // bool bvh_node::intersect(const Ray &r, Surfel &rec) const;

    // bool bvh_node::intersect_p(const Ray &r) const;

public:
    shared_ptr<Primitive> left;
    shared_ptr<Primitive> right;
    aabb box;
};

inline bool box_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b, int axis)
{
    aabb box_a;
    aabb box_b;

    if (!a->bounding_box(0, 0, box_a) || !b->bounding_box(0, 0, box_b))
        std::cerr << "No bounding box in bvh_node constructor.\n";

    return box_a.min().e[axis] < box_b.min().e[axis];
}

inline bool box_x_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b)
{
    return box_compare(a, b, 0);
}

inline bool box_y_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b)
{
    return box_compare(a, b, 1);
}

inline bool box_z_compare(const shared_ptr<Primitive> a, const shared_ptr<Primitive> b)
{
    return box_compare(a, b, 2);
}

inline double random_double()
{
    // Returns a random real in [0,1).
    return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
    // Returns a random real in [min,max).
    return min + (max - min) * random_double();
}

inline int random_int(int min, int max)
{
    // Returns a random integer in [min,max].
    return static_cast<int>(random_double(min, max + 1));
}

#endif
#include "include/aggregate.hpp"
#include "include/aabb.hpp"

bool Aggregate::bounding_box(double time0, double time1, aabb &output_box) const
{
    if (primitives.empty())
        return false;

    aabb temp_box;
    bool first_box = true;

    for (const auto &object : primitives)
    {
        if (!object->bounding_box(time0, time1, temp_box))
            return false;
        output_box = first_box ? temp_box : surrounding_box(output_box, temp_box);
        first_box = false;
    }

    return true;
}
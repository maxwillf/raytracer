#include "include/bvh_node.hpp";

bvh_node::bvh_node(
    const std::vector<shared_ptr<Primitive>> &src_objects,
    size_t start, size_t end, double time0, double time1)
{
    auto objects = src_objects; // Create a modifiable array of the source scene objects

    int axis = random_int(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;

    size_t object_span = end - start;

    if (object_span == 1)
    {
        left = right = objects[start];
    }
    else if (object_span == 2)
    {
        if (comparator(objects[start], objects[start + 1]))
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);

        auto mid = start + object_span / 2;
        left = make_shared<bvh_node>(objects, start, mid, time0, time1);
        right = make_shared<bvh_node>(objects, mid, end, time0, time1);
    }

    aabb box_left, box_right;

    if (!left->bounding_box(time0, time1, box_left) || !right->bounding_box(time0, time1, box_right))
        std::cerr << "No bounding box in bvh_node constructor.\n";
    box = surrounding_box(box_left, box_right);
}
bool bvh_node::bounding_box(double time0, double time1, aabb &output_box) const
{
    output_box = box;
    return true;
}

bool bvh_node::intersect(const Ray &r, Surfel *rec) const
{
    if (!box.hit(r, r.tMin, r.tMax))
        return false;

    bool hit_left = left->intersect(r, rec);
    // Ray rightRay = Ray(r.origin(), r.direction());
    // rightRay.tMax = hit_left ? rec->t : r.tMax;
    //bool hit_right = right->intersect(rightRay, rec);
    bool hit_right = right->intersect(r, rec);
    bool hit = hit_left || hit_right;
    if (hit)
    {
        int x = 2;
    }

    return hit;
}

bool bvh_node::intersect_p(const Ray &r) const
{
    if (!box.hit(r, r.tMin, r.tMax))
        return false;

    bool hit_left = left->intersect_p(r);
    bool hit_right = right->intersect_p(r);
    return hit_left || hit_right;
}

// void bvh_node::debugPrint()
// {
//     // BlinnPhongMaterial *bm = static_cast<BlinnPhongMaterial *>(isect.primitive->material_get().get());
//     if (left != nullptr)
//     {
//         debugPrint(left);
//     }
// }
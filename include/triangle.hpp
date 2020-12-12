#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <vector>
#include <memory>
#include "vec2.hpp"
#include "vec3.hpp"
#include "primitive.hpp"
#include "aabb.hpp"
#include "surfel.hpp"
#include "include/tiny_obj_loader.hpp"
// #include "rt3.h"
// #include "../ext/tiny_obj_loader.h"
using namespace std;

/// This struct implements an indexd triangle mesh database.
struct TriangleMesh
{
    int n_triangles; //!< # of triangles in the mesh.
    // The size of the three lists below should be 3 * nTriangles. Every 3 values we have a triangle.
    std::vector<int> vertex_indices;  //!< The list of indices to the vertex list, for each individual triangle.
    std::vector<int> normal_indices;  //!< The list of indices to the normals list, for each individual triangle.
    std::vector<int> uvcoord_indices; //!< The list of indices to the UV coord list, for each individual triangle.

    // Here comes the data associated with each vertex. WARNING: The length of the std::vectors below may differ.
    std::vector<vec3> vertices; //!< The 3D geometric coordinates
    std::vector<vec3> normals;  //!< The 3D normals.
    std::vector<vec2> uvcoords; //!< The 2D texture coordinates.

    // Regular constructor (almost all data is imported via move semantics).
    TriangleMesh(){/*empty*/};
    /// Copy constructor disabled
    TriangleMesh(const TriangleMesh &) = delete;
    /// Assign operator disabled.
    TriangleMesh &operator=(const TriangleMesh &) = delete;
    /// Move constructor.
    TriangleMesh(TriangleMesh &&other) = delete;
};

/// Represents a single triangle.
class Triangle : public Primitive
{
private:
    int *v; //!< Pointer to the vertex index array stored in the triangle mesh database.
    // After the proper triangle initialization, we may access vertices with v[0], v[1], and v[2]
    int *n; //!< Pointer to the normal index array stored in the triangle mesh database.
    // After the proper triangle initialization, we may access normals with n[0], n[1], and n[2]
    int *uv; //!< Pointer to the UV coord index array stored in the triangle mesh database.
    // After the proper triangle initialization, we may access UV coords with uv[0], uv[1], and uv[2]

    shared_ptr<TriangleMesh> mesh; //!< This is the **indexed triangle mesh database** this triangle is linked to.
    bool backface_cull;            //!< Set it `true` to activate backface culling.

public:
    // The single constructor, that receives the mesh, this triangle id, and an indication for backface culling.
    Triangle(shared_ptr<TriangleMesh> mesh, int tri_id, bool bfc = true)
        : Primitive(), mesh{mesh}, backface_cull{bfc}
    {
        // This is just a shortcut to access this triangle's data stored in the mesh database.
        v = &mesh->vertex_indices[3 * tri_id];
        n = &mesh->normal_indices[3 * tri_id];
        uv = &mesh->uvcoord_indices[3 * tri_id];
    }

    bool bounding_box(double time0, double time1, aabb &output_box) const;

    /// Return the triangle's bounding box.
    // Bounds3f object_bound() const;
    /// The regular intersection methods, as defined in the Primitive parent class.
    bool intersect(const Ray &ray, Surfel *isect) const
    {
        const float EPSILON = 0.0000001;
        int v0 = v[0];
        int v1 = v[1];
        int v2 = v[2];
        vec3 vertex0 = mesh->vertices[v[0]];
        vec3 vertex1 = mesh->vertices[v[1]];
        vec3 vertex2 = mesh->vertices[v[2]];
        vec3 edge1, edge2, h, s, q;
        float a, f, u, v;
        edge1 = vertex1 - vertex0;
        edge2 = vertex2 - vertex0;
        h = cross(ray.direction(), edge2);
        a = dot(edge1, h);
        if (backface_cull)
        {
            if (a < EPSILON)
            {
                return false;
            }

            vec3 tvec = ray.origin() - vertex0;
            u = dot(tvec, ray.direction());
            if (u < 0.0 || u > a)
            {
                return false;
            }
            double t = dot(edge2, q);
            double inv_det = 1.0 / a;
            t *= inv_det;
            u *= inv_det;
            v *= inv_det;
            if (t > EPSILON) // ray intersection
            {
                if (t < ray.tMax && t >= ray.tMin)
                {
                    ray.tMax = t;
                    //if(sf){
                    //    free(sf);
                    //}
                    vec3 p = ray(t);
                    // TODO: normal
                    //*isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
                    *isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
                    //*isect = Surfel(p, unit_vector(p - center), -ray.direction(), 0.0, Point2(0, 0), this);
                    return true;
                }
            }
        }
        if (a > -EPSILON && a < EPSILON)
        {
            return false; // This ray is parallel to this triangle.
        }
        f = 1.0 / a;
        s = ray.origin() - vertex0;
        u = f * dot(s, h);
        if (u < 0.0 || u > 1.0)
            return false;
        q = cross(s, edge1);
        v = f * dot(ray.direction(), q);
        if (v < 0.0 || u + v > 1.0)
            return false;
        // At this stage we can compute t to find out where the intersection point is on the line.
        float t = f * dot(edge2, q);
        if (t > EPSILON) // ray intersection
        {
            if (t < ray.tMax && t >= ray.tMin)
            {
                ray.tMax = t;
                //if(sf){
                //    free(sf);
                //}
                auto p = ray(t);
                // TODO: normal
                //*isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
                *isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
                //*isect = Surfel(p, unit_vector(p - center), -ray.direction(), 0.0, Point2(0, 0), this);
                return true;
            }
            else
            {
                return false;
            }
        }
        else // This means that there is a line intersection but not a ray intersection.
            return false;
    }
    // bool intersect(const Ray &ray, Surfel *isect) const
    // {
    //     const float EPSILON = 0.0000001;
    //     vec3 vertex0 = mesh->vertices[v[0]];
    //     vec3 vertex1 = mesh->vertices[v[1]];
    //     vec3 vertex2 = mesh->vertices[v[2]];
    //     vec3 edge1, edge2, h, s, q;
    //     float a, f, u, v;
    //     edge1 = vertex1 - vertex0;
    //     edge2 = vertex2 - vertex0;
    //     h = cross(ray.direction(), edge2);
    //     a = dot(edge1, h);
    //     if (a > -EPSILON && a < EPSILON)
    //         return false; // This ray is parallel to this triangle.
    //     f = 1.0 / a;
    //     s = ray.origin() - vertex0;
    //     u = f * dot(s, h);
    //     if (u < 0.0 || u > 1.0)
    //         return false;
    //     q = cross(s, edge1);
    //     v = f * dot(ray.direction(), q);
    //     if (v < 0.0 || u + v > 1.0)
    //         return false;
    //     // At this stage we can compute t to find out where the intersection point is on the line.
    //     float t = f * dot(edge2, q);
    //     if (t > EPSILON) // ray intersection
    //     {
    //         if (t < ray.tMax && t >= ray.tMin)
    //         {
    //             ray.tMax = t;
    //             //if(sf){
    //             //    free(sf);
    //             //}
    //             auto p = ray(t);
    //             // TODO: normal
    //             //*isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
    //             *isect = Surfel(p, unit_vector(mesh->normals[n[0]]), -ray.direction(), 0.0, Point2(0, 0), this);
    //             //*isect = Surfel(p, unit_vector(p - center), -ray.direction(), 0.0, Point2(0, 0), this);
    //             return true;
    //         }
    //     }
    //     else // This means that there is a line intersection but not a ray intersection.
    //         return false;
    // }
    bool intersect_p(const Ray &ray) const { return false; }

    /// This friend function helps us debug the triangles, if we want to.
    friend std::ostream &operator<<(std::ostream &os, const Triangle &t);
};

/// This is the entry point for the client. This function begins the process of reading a triangle mesh.
std::vector<shared_ptr<Primitive>>
create_triangle_mesh_primitive(bool flip_normals, const std::vector<Argument> &ps);

// /// This is the function that actually creates the mesh database and the triangles, ans store them in a Primitive list.
std::vector<shared_ptr<Primitive>> create_triangle_mesh(shared_ptr<TriangleMesh>, bool);

// /// Internal function that calls the tinyobjloader api to read the OBJ data into memory.
bool load_mesh_data(const std::string &filename, bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md);

// /// This function essentially convertes the mesh data from the tinyobjloader internal data structure to our mesh data structure.
void extract_obj_data(const tinyobj::attrib_t &attrib,
                      const std::vector<tinyobj::shape_t> &shapes,
                      bool rvo, bool cn, bool fn, shared_ptr<TriangleMesh> md);

#endif
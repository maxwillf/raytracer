#include "include/sphere.hpp"
#include "include/surfel.hpp"

bool Sphere::intersect(const Ray &r, Surfel *sf) const {
    // stub
    //      sf = new Surfel(Point(0,0,0),)
    vec3 oc = r.origin() - center;
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(oc, r.direction());
    float c = dot(oc, oc) - radius * radius;
    float discrimant = b * b - 4 * a * c;
    if(discrimant < 0){
        return false;
    }
    else {
        float t1 = -b + sqrt(discrimant) / 2 * a;
        float t2 = -b - sqrt(discrimant) / 2 * a;
        float t = t1 < t2 ? t1 : t2;
        if(t < r.tMax){
            r.tMax = t;
            //if(sf){
            //    free(sf);
            //}
            vec3 p = r(t);
            *sf = Surfel(p,p - r.origin(), -r.direction(),0.0, Point2(0,0),this);
        }
        return true;
    }
}

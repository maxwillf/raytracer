#include "include/sphere.hpp"
#include "include/surfel.hpp"

bool Sphere::intersect(const Ray &r, Surfel *sf) const
{
    // stub
    //      sf = new Surfel(Point(0,0,0),)
    vec3 oc = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2.0 * dot(oc, r.direction());
    double c = dot(oc, oc) - (radius * radius);
    double discrimant = b * b - (4.0 * a * c);
    if (discrimant < 0)
    {
        return false;
    }
    else
    {
        // double t1 = (-b + sqrt(discrimant)) / 2.0 * a;
        // double t2 = (-b - sqrt(discrimant)) / 2.0 * a;
        double ocd = dot(oc, r.direction());
        double delta = sqrt((ocd * ocd) - (a * (dot(oc, oc) - radius * radius)));
        double t1 = ((-dot(oc, r.direction())) - delta) / a;
        double t2 = ((-dot(oc, r.direction())) + delta) / a;
        double t = t1 < t2 ? t1 : t2;
        if (t < r.tMax && t >= r.tMin)
        {
            r.tMax = t;
            //if(sf){
            //    free(sf);
            //}
            vec3 p = r(t);
            *sf = Surfel(p, unit_vector(p - center), -r.direction(), 0.0, Point2(0, 0), this);
            return true;
        }
        else
        {
            return false;
        }
    }
}

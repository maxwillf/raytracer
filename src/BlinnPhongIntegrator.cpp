#include "include/BlinnPhongIntegrator.hpp"
#include "include/BlinnPhongMaterial.hpp"
#include "include/lightSource.hpp"
#include <algorithm>
#include <cmath>
#include <tuple>

Color24 BlinnPhongIntegrator::Li(const Ray &ray, const Scene &scene, Color24 bkg, int depth) const
{
    Color24 L = Color24(0, 0, 0);
    // Find closest ray intersection or return background radiance.
    Surfel isect; // Intersection information.
    if (!scene.intersect(ray, &isect))
    {
        L = bkg;
        return L;
        // return depth == 0 ? L : L / 255.0;
    }
    else
    {
        double epsilon = 0.05;
        BlinnPhongMaterial *bm = static_cast<BlinnPhongMaterial *>(isect.primitive->material_get().get());
        // if there is an ambient light
        if (scene.ambientLight)
        {
            L = L + bm->ka() * scene.ambientLight->L;
        }

        // vec3 wi = unit_vector(vec3(1, 0.8, -2));
        // vec3 n = vec3(unit_vector(isect.n));
        // vec3 Li = vec3(0.9, 0.9, 0.9); // Intensidade da luz direcional temporária.
        // double angle = dot(n, wi);
        // L = bm->kd() * std::max(angle, 0.0) * Li;
        // std::cout << "n " << n << std::endl;
        // std::cout << "angle " << angle << std::endl;
        // return L * vec3(255, 255, 255);
        for (auto &&light : scene.lights)
        {
            auto pointLight = std::dynamic_pointer_cast<PointLight>(light);
            if (pointLight)
            {
                vec3 wi = unit_vector(pointLight->from - isect.p);
                Ray lightShadowRay = Ray(isect.p + wi * epsilon, wi);
                lightShadowRay.tMax = 1;
                if (!scene.intersect_p(lightShadowRay))
                {
                    vec3 wo = unit_vector(wi);
                    //vec3 h = ray.direction() + directionalLight->direction / (ray.direction() + directionalLight->direction).length();
                    //vec3 h = -unit_vector(unit_vector(ray.origin() - isect.p) + (wi));
                    // vec3 h = -unit_vector(ray.direction() + directionalLight->direction);
                    // vec3 h = -unit_vector(unit_vector(ray.origin() - isect.p) + (wi));
                    L += bm->kd() * pointLight->L * std::max(0.0, dot(isect.n, wo));
                    // std::cout << dot(isect.n, h) << std::endl;
                    // L += bm->ks() * directionalLight->L * pow(std::max(0.0, dot(isect.n, h)), bm->g());
                }
            }

            auto directionalLight = std::dynamic_pointer_cast<DirectionalLight>(light);
            if (directionalLight)
            {
                vec3 wi = unit_vector(directionalLight->from - isect.p);
                //                vec3 wi = unit_vector(directionalLight->direction);
                Ray lightShadowRay = Ray(isect.p + wi * epsilon, wi);
                lightShadowRay.tMax = 1;
                if (!scene.intersect_p(lightShadowRay))
                {
                    vec3 wo = unit_vector(-directionalLight->direction);
                    //vec3 h = ray.direction() + directionalLight->direction / (ray.direction() + directionalLight->direction).length();
                    //vec3 h = -unit_vector(unit_vector(ray.origin() - isect.p) + (wi));
                    vec3 h = -unit_vector(ray.direction() + directionalLight->direction);
                    // vec3 h = -unit_vector(unit_vector(ray.origin() - isect.p) + (wi));
                    L += bm->kd() * directionalLight->L * std::max(0.0, dot(isect.n, wo));
                    // std::cout << dot(isect.n, h) << std::endl;
                    // L += bm->ks() * directionalLight->L * pow(std::max(0.0, dot(isect.n, h)), bm->g());
                }
            }

            auto spotLight = std::dynamic_pointer_cast<SpotLight>(light);
            if (spotLight)
            {
                vec3 wi = unit_vector(spotLight->from - isect.p);
                Ray lightShadowRay = Ray(isect.p + wi * epsilon, wi);
                // vec3 wi = unit_vector(spotLight->from - isect.p);
                // Ray lightShadowRay = Ray(isect.p + wi * epsilon, wi);
                lightShadowRay.tMax = 1;
                if (!scene.intersect_p(lightShadowRay))
                {
                    // vec3 wo = unit_vector(wi);
                    vec3 wo = unit_vector(-spotLight->direction);
                    //vec3 wo = unit_vector(wi);
                    // double cosAngle = dot(spotLight->direction, wi) * 100;
                    double cosAngle = std::abs(dot(spotLight->direction, wi)) * 100;
                    // maybe do 1 - cosAngle ??? idk
                    //std::cout << cosAngle << std::endl;
                    auto spotL = spotLight->L;
                    if (cosAngle > spotLight->cutoff)
                    {
                        continue;
                        // spotL *= 0;
                    }
                    else if (spotLight->falloff < cosAngle && cosAngle < spotLight->cutoff)
                    {
                        double newMaxAngle = spotLight->cutoff - spotLight->falloff;
                        double falloffL = ((cosAngle - spotLight->falloff) / newMaxAngle);
                        // double falloffL = 100 * cosAngle / newMaxAngle;
                        spotL *= falloffL;
                    }
                    else if (cosAngle < spotLight->falloff)
                    {
                        // do nothing
                    }
                    L += bm->kd() * spotL * std::max(0.0, dot(isect.n, wo));
                    // L += bm->kd() * spotLight->L * std::max(0.0, dot(isect.n, wo));
                    // std::cout << dot(isect.n, h) << std::endl;
                    // L += bm->ks() * directionalLight->L * pow(std::max(0.0, dot(isect.n, h)), bm->g());
                }
            }
        }
        // if (depth < this->max_depth)
        // {
        //     vec3 reflectedRayDirection = ray.direction() - (2 * dot(ray.direction(), isect.n) * isect.n);
        //     Ray reflectedRay = Ray(ray.origin() + reflectedRayDirection * epsilon, reflectedRayDirection);
        //     L += bm->km() * Li(reflectedRay, scene, bkg, depth + 1);
        //     // stub
        //     //        L = bm->kd * light_I * std::max( 0.f, Dot( n, l ) );
        // }
        return depth == 0 ? L * vec3(255, 255, 255) : L;
        // return L * vec3(255, 255, 255);
    }
}
// [0] FIRST STEP TO INITIATE `L` WITH THE COLOR VALUE TO BE RETURNED.
// [1] FIND CLOSEST RAY INTERSECTION OR RETURN BACKGROUND RADIANCE
// [2] SPECIAL SITUATION: IF THE RAY HITS THE SURFACE FROM "BEHIND" (INSIDE), WE DO NOT COLOR.
// After the ray hits the object, send another ray in the contrary direction to see if it can be seen
// [3] GET THE MATERIAL ASSOCIATED WITH THE HIT SURFACE
// [4] INITIALIZE COMMON VARIABLES FOR BLINNPHONG INTEGRATOR (COEFFICIENTS AND VECTORS L, N, V, ETC.)
// [5] CALCULATE & ADD CONTRIBUTION FROM EACH LIGHT SOURCE
// [6] ADD AMBIENT CONTRIBUTION HERE (if there is any).
// [7] ADD MIRROR REFLECTION CONTRIBUTION

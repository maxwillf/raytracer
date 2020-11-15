#include "include/flatIntegrator.hpp"
#include "include/flatMaterial.hpp"
#include "include/surfel.hpp"

// This method must be overridden by all classes derived from SamplerIntegrator.
/// Determines a color for the incoming ray.
Color24 FlatIntegrator::Li(const Ray& ray, const Scene& scene, Color24 bkg_color, int depth ) const
{
    Color24 L(0,0,0); // The radiance
    // Find closest ray intersection or return background radiance.
    Surfel isect; // Intersection information.
    if (!scene.intersect(ray, &isect)) {
        // This might be just:
        L = bkg_color;
    }
    else {
        // std::cout << "did touch object" << std::endl;
// Some form of determining the incoming radiance at the ray's origin.
        // For this integrator, it might just be:
        // Polymorphism in action.
                FlatMaterial *fm = static_cast< FlatMaterial *>( isect.primitive->material_get().get());
                // Assign diffuse color to L.
         L = fm->kd(); // Call a method present only in FlatMaterial.
         //L = Color24(255,255,255);
    }
    return L;
}

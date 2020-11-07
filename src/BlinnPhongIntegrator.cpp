#include "include/BlinnPhongIntegrator.hpp"
#include "include/BlinnPhongMaterial.hpp"

Color24 BlinnPhongIntegrator::Li( const Ray &ray, const Scene &scene, Color24 bkg, int depth ) const
{
    Color24 L(0,0,0);
    // Find closest ray intersection or return background radiance.
    Surfel isect; // Intersection information.
    if (!scene.intersect(ray, &isect)) {
        // This might be just:
        L = bkg;
    }
    else {
        if(!scene.intersect_p(Ray(isect.p,isect.wo))){
            return L;
        }
        else {
            BlinnPhongMaterial *bm = static_cast< BlinnPhongMaterial *>( isect.primitive->material_get().get());
            //            L = scene
        }
        // stub
            //        L = bm->kd * light_I * std::max( 0.f, Dot( n, l ) );
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
	return L;
}

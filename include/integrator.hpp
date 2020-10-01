#ifndef __INTEGRATOR_H_
#define __INTEGRATOR_H_
#include "include/camera.h"
#include <memory>
#include "include/scene.hpp"

class Integrator {
	public:
		virtual ~Integrator();
		virtual void render( const Scene& scene ) =0;
};

class SamplerIntegrator : public Integrator {
        //=== Public interface
	public:
		virtual ~SamplerIntegrator();
		SamplerIntegrator( std::shared_ptr<const Camera> cam ) : camera{cam};

		virtual Color24 Li( const Ray& ray, const Scene& scene ) const = 0;
		virtual void render( const Scene& scene );
		virtual void preprocess( const Scene& scene )

            protected:
             std::shared_ptr<const Camera> camera;
};

#endif // __INTEGRATOR_H_

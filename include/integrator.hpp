#ifndef __INTEGRATOR_H_
#define __INTEGRATOR_H_

#include "include/camera.hpp"
#include "include/factory.hpp"
#include <memory>
#include "include/scene.hpp"

typedef vec3 Color24;

class Integrator {
	public:
		//virtual ~Integrator();
		virtual void render( const Scene& scene ) =0;
        friend DerivedRegistrar<Integrator, Integrator>;
        static Integrator* Make(Arguments args) {
            return nullptr;
        }

        void setCamera( std::shared_ptr<const Camera> cam){
            camera = cam;
        }
     protected:
        std::shared_ptr<const Camera> camera;
};


class SamplerIntegrator : public Integrator {
        //=== Public interface
	public:
		//virtual ~SamplerIntegrator();
		SamplerIntegrator( std::shared_ptr<const Camera> cam )  {
            this->camera = cam;
        }

        virtual Color24 Li( const Ray& ray, const Scene& scene, Color24 bkg_color, int depth = 0 ) const = 0;
        virtual void render( const Scene& scene );
        virtual void preprocess( const Scene& scene );
        static Integrator* Make(Arguments args) {
            return nullptr;
        }

friend DerivedRegistrar<Integrator, SamplerIntegrator>;
};

#endif // __INTEGRATOR_H_

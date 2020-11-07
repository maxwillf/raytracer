#ifndef __LIGHTSOURCE_H_
#define __LIGHTSOURCE_H_

#include "include/primitive.hpp"
#include "include/scene.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "argument.hpp"
#include <memory>
#include "factory.hpp"
#include "algorithm"

// Verifica se há oclusão entre dois pontos de contato.
class VisibilityTester {
	public:
        VisibilityTester() =default;
		VisibilityTester( const Surfel&, const Surfel& );
		bool unoccluded( const Scene& scene );
	public:
		Surfel p0, p1;
};


class LightSource
{
    public:
        vec3 L;
        //LightSource(){};
        //        virtual ColorXYZ sample_Li( const Surfel& hit /*in*/,
//                                             Vector3f *wi/*out*/,
//            VisbilityTester *vis/*out*/ ) = 0;
        virtual void preprocess( const Scene & ) {};

static LightSource *Make(Arguments args) { return nullptr; };
friend DerivedRegistrar<LightSource, LightSource>;
};

class AmbientLight : public LightSource
{
    public:
        int flux;
        vec3 scale;

        AmbientLight(std::vector<Argument> args){
            for (auto &&arg : args)
            {
                if (arg.getKey() == "L")
                {
                    L = arg.getValues<float>();
                }

                if (arg.getKey() == "flux")
                {
                    flux = arg.getValue<int>();
                }
                if (arg.getKey() == "scale")
                {
                    scale = arg.getValues<float>();
                }
            }
        };
        //
        static LightSource *Make(Arguments args) {

            if (get<1>(args)[0].getValue<std::string>() == "ambient")
            {
                return new AmbientLight(get<1>(args));
            }
            else
            {
                return nullptr;
            }
 };
        friend DerivedRegistrar<LightSource, LightSource>;
};

bool is_ambient( LightSource source ) {
	return typeid(source) == typeid(AmbientLight);
}

#endif // __LIGHTSOURCE_H_

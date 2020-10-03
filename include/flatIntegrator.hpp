#ifndef __FLATINTEGRATOR_H_
#define __FLATINTEGRATOR_H_
#include "include/factory.hpp"
#include "include/integrator.hpp"
#include <memory>

class FlatIntegrator : public SamplerIntegrator{
    public:
        Color24 Li(const Ray& ray, const Scene& scene, Color24 bkg_color ) const;
        //FlatIntegrator()
        //{
        //}
        FlatIntegrator(std::vector<Argument> attributes) : SamplerIntegrator(std::shared_ptr<const Camera>(nullptr))
        {
            //            FlatIntegrator(shared_ptr<const Camera>(nullptr));
        }

        ~FlatIntegrator(){
        
        }

        static Integrator* Make(Arguments args){
            if (get<1>(args)[0].getValue<std::string>() == "flat")
            {
                        return new FlatIntegrator(get<1>(args));
            }
            else
            {
                return nullptr;
            }
        }
        friend DerivedRegistrar<Integrator, FlatIntegrator>;
};

#endif // __FLATINTEGRATOR_H_

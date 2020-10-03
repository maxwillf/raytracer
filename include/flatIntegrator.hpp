#ifndef __FLATINTEGRATOR_H_
#define __FLATINTEGRATOR_H_
#include "include/integrator.hpp"

class FlatIntegrator : public SamplerIntegrator{
    public:
        Color24 Li(const Ray& ray, const Scene& scene, Color24 bkg_color ) const;
        //FlatIntegrator(std::vector<Argument> attributes)
        //{
        //        SamplerIntegrator(make_shared<Camera>(nullptr));
        //};
        ~FlatIntegrator(){
        
        }

        static Integrator* Make(Arguments args){
            if (get<1>(args)[0].getValue<std::string>() == "flat")
            {
                //        return new FlatIntegrator(get<1>(args));
            }
            else
            {
                return nullptr;
            }
        }
};

#endif // __FLATINTEGRATOR_H_

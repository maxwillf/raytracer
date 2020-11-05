#ifndef __BLINNPHONGINTEGRATOR_H_
#define __BLINNPHONGINTEGRATOR_H_

#include "include/factory.hpp"
#include "include/integrator.hpp"
#include <memory>

class BlinnPhongIntegrator : public SamplerIntegrator {
    public:
        Color24 Li(const Ray& ray, const Scene& scene, Color24 bkg_color, int depth) const;
        //BlinnPhongIntegrator()
        //{
        //}
        BlinnPhongIntegrator(std::vector<Argument> attributes) : SamplerIntegrator(std::shared_ptr<const Camera>(nullptr))
        {
            //            BlinnPhongIntegrator(shared_ptr<const Camera>(nullptr));
        }

        ~BlinnPhongIntegrator(){

        }

        static Integrator* Make(Arguments args){
            if (get<1>(args)[0].getValue<std::string>() == "blinn")
            {
                return new BlinnPhongIntegrator(get<1>(args));
            }
            else
            {
                return nullptr;
            }
        }
        friend DerivedRegistrar<Integrator, BlinnPhongIntegrator>;
};

#endif // __BLINNPHONGINTEGRATOR_H_

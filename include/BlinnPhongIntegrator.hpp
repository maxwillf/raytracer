#ifndef __BLINNPHONGINTEGRATOR_H_
#define __BLINNPHONGINTEGRATOR_H_

#include "include/factory.hpp"
#include "include/integrator.hpp"
#include "include/lightSource.hpp"
#include <memory>

class BlinnPhongIntegrator : public SamplerIntegrator
{

public:
    Color24 Li(const Ray &ray, const Scene &scene, Color24 bkg_color, int depth) const;
    int max_depth = 0;
    BlinnPhongIntegrator(std::vector<Argument> attributes) : SamplerIntegrator(std::shared_ptr<const Camera>(nullptr))
    {
        max_depth = findAttribute(attributes, "depth").getValue<int>();
    }

    BlinnPhongIntegrator() : SamplerIntegrator(std::shared_ptr<const Camera>(nullptr))
    {
        //            BlinnPhongIntegrator(shared_ptr<const Camera>(nullptr));
    }

    ~BlinnPhongIntegrator()
    {
    }

    void preprocess(const Scene &scene);

    static Integrator *Make(Arguments args)
    {
        if (get<1>(args)[0].getValue<std::string>() == "blinn_phong")
        {
            return new BlinnPhongIntegrator(get<1>(args));
        }
        else
        {
            return nullptr;
        }
    }

    //void addLightSource(shared_ptr<LightSource> source){
    //    lights.push_back(source);
    //}

    friend DerivedRegistrar<Integrator, BlinnPhongIntegrator>;
};

#endif // __BLINNPHONGINTEGRATOR_H_

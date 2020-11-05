#ifndef __BLINNPHONGMATERIAL_H_
#define __BLINNPHONGMATERIAL_H_
#include "include/factory.hpp"
#include "include/integrator.hpp"
#include "include/material.hpp"
#include "include/vec3.hpp"

class BlinnPhongMaterial : public Material {
        vec3 ambient;
        vec3 diffuse;
        vec3 specular;
        unsigned int glossiness;

    public:
        BlinnPhongMaterial(std::vector<Argument> args)
        {
            for (auto &&arg : args)
            {
                if (arg.getKey() == "ambient")
                {
                    ambient = arg.getValues<float>();
                }
                if (arg.getKey() == "diffuse")
                {
                    diffuse = arg.getValues<float>();
                }
                if (arg.getKey() == "specular")
                {
                    specular = arg.getValues<float>();
                }
                if (arg.getKey() == "glossiness")
                {
                    glossiness = arg.getValue<int>();
                }
            }
        };

        Color24 kd(){
            return diffuse;
        }

        static Material *Make(Arguments args) {
            if (get<1>(args)[0].getValue<std::string>() == "blinn")
            {
                return new BlinnPhongMaterial(get<1>(args));
            }
            else
            {
                return nullptr;
            }
        }
        friend DerivedRegistrar<Material, BlinnPhongMaterial>;
};


#endif // __BLINNPHONGMATERIAL_H_

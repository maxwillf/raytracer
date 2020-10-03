#ifndef __FLATMATERIAL_H_
#define __FLATMATERIAL_H_
#include "include/factory.hpp"
#include "include/material.hpp"
#include "include/vec3.hpp"
#include "include/flatIntegrator.hpp"

class FlatMaterial : public Material {

        vec3 color;
    public:
        FlatMaterial(std::vector<Argument> args)
        {
            for (auto &&arg : args)
            {
                if (arg.getKey() == "color")
                {
                    color = arg.getValues<float>();
                }
            }
        };
        Color24 kd(){
            return color;
        }
        static Material *Make(Arguments args) {
            if (get<1>(args)[0].getValue<std::string>() == "flat")
            {
                return new FlatMaterial(get<1>(args));
            }
            else
            {
                return nullptr;
            }
        }
        friend DerivedRegistrar<Material, FlatMaterial>;
};

#endif // __FLATMATERIAL_H_

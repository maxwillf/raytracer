#ifndef __LIGHTSOURCE_H_
#define __LIGHTSOURCE_H_
#pragma once
#include "include/primitive.hpp"
#include "include/scene.hpp"
#include "vec3.hpp"
#include "ray.hpp"
#include "argument.hpp"
#include <memory>
#include "factory.hpp"
#include "algorithm"

// Verifica se há oclusão entre dois pontos de contato.
class VisibilityTester
{
public:
    VisibilityTester() = default;
    VisibilityTester(const Surfel &, const Surfel &);
    bool unoccluded(const Scene &scene)
    {

        // Surfel isect; // Intersection information.
        // // std::cout << "ray direction: " << ray.direction() << std::endl;
        // if (!scene.intersect(ray, &isect))
        // {
        //     return false;
        // }
        // else
        // {
        // }
    }

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
    virtual void preprocess(const Scene &){};

    static LightSource *Make(Arguments args) { return nullptr; };
    friend DerivedRegistrar<LightSource, LightSource>;
    /// Retorna a intensidade da luz, direção e o teste oclusão.
    // virtual Color24 sample_Li(const Surfel &hit /*in*/,
    //                           vec3 *wi /*out*/,
    //                           VisibilityTester *vis /*out*/) = 0;
};

class AmbientLight : public LightSource
{
public:
    int flux;
    vec3 scale;

    AmbientLight(std::vector<Argument> args)
    {
        for (auto &&arg : args)
        {
            if (arg.getKey() == "L")
            {
                L = arg.getValues<double>();
            }

            if (arg.getKey() == "flux")
            {
                flux = arg.getValue<int>();
            }
            if (arg.getKey() == "scale")
            {
                scale = arg.getValues<double>();
            }
        }
    };
    // Color24 sample_Li(const Surfel &hit /*in*/,
    //                   vec3 *wi /*out*/,
    //                   VisibilityTester *vis /*out*/)
    // {
    //     std::__throw_runtime_error("sample_Li not implemented for ambient light");
    // };
    //
    static LightSource *Make(Arguments args)
    {

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

class DirectionalLight : public LightSource
{

public:
    int flux;
    vec3 scale;
    vec3 to;
    vec3 from;
    // maybe we don't need the to and from if we already have the direction but just making sure
    vec3 direction;

    DirectionalLight(std::vector<Argument> args)
    {
        for (auto &&arg : args)
        {
            if (arg.getKey() == "L")
            {
                L = arg.getValues<double>();
            }

            if (arg.getKey() == "flux")
            {
                flux = arg.getValue<int>();
            }
            if (arg.getKey() == "scale")
            {
                scale = arg.getValues<double>();
            }
            to = findAttribute(args, "to").getValues<double>();
            from = findAttribute(args, "from").getValues<double>();
            direction = unit_vector(to - from);
        }
    };
    //
    static LightSource *Make(Arguments args)
    {

        if (get<1>(args)[0].getValue<std::string>() == "directional")
        {
            return new DirectionalLight(get<1>(args));
        }
        else
        {
            return nullptr;
        }
    };
    friend DerivedRegistrar<LightSource, LightSource>;
};

class PointLight : public LightSource
{

public:
    int flux;
    vec3 scale;
    vec3 from;
    PointLight(std::vector<Argument> args)
    {
        for (auto &&arg : args)
        {
            if (arg.getKey() == "I")
            {
                L = arg.getValues<double>();
            }
            if (arg.getKey() == "scale")
            {
                scale = arg.getValues<double>();
            }
            if (arg.getKey() == "from")
            {
                from = arg.getValues<double>();
            }
        }
    };
    //
    static LightSource *Make(Arguments args)
    {

        if (get<1>(args)[0].getValue<std::string>() == "point")
        {
            return new PointLight(get<1>(args));
        }
        else
        {
            return nullptr;
        }
    };
    friend DerivedRegistrar<LightSource, LightSource>;
};

class SpotLight : public LightSource
{
public:
    vec3 scale;
    vec3 from;
    vec3 to;
    vec3 direction;
    double cutoff;
    double falloff;
    SpotLight(std::vector<Argument> args)
    {
        for (auto &&arg : args)
        {
            if (arg.getKey() == "I")
            {
                L = arg.getValues<double>();
            }
            if (arg.getKey() == "scale")
            {
                scale = arg.getValues<double>();
            }
            if (arg.getKey() == "cutoff")
            {
                cutoff = arg.getValue<double>();
            }
            if (arg.getKey() == "falloff")
            {
                falloff = arg.getValue<double>();
            }
            to = findAttribute(args, "to").getValues<double>();
            from = findAttribute(args, "from").getValues<double>();
            direction = unit_vector(to - from);
        }
    };
    //
    static LightSource *Make(Arguments args)
    {

        if (get<1>(args)[0].getValue<std::string>() == "spot")
        {
            return new SpotLight(get<1>(args));
        }
        else
        {
            return nullptr;
        }
    };
    friend DerivedRegistrar<LightSource, LightSource>;
};

inline bool is_ambient(shared_ptr<LightSource> source)
{
    auto ambientLight = std::dynamic_pointer_cast<AmbientLight>(source);
    if (ambientLight)
    {
        return true;
    }
    return false;
}

#endif // __LIGHTSOURCE_H_

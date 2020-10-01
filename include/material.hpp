#ifndef __MATERIAL_H_
#define __MATERIAL_H_
#include "factory.hpp"

class Material {
    static Material *Make(Arguments args) { return nullptr; };
    friend DerivedRegistrar<Material,Material>;
};


#endif // __MATERIAL_H_

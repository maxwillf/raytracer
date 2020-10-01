#include "include/primitive.hpp"
#include "include/sphere.hpp"

template <>
std::vector<Factory<Primitive, Arguments>::ReadFunPtr> Factory<Primitive, Arguments>::registeredFuns = std::vector<Factory<Primitive, Arguments>::ReadFunPtr>();
DerivedRegistrar<Primitive, Primitive> __initPrimitive;
DerivedRegistrar<Primitive, Sphere> __initSphere;

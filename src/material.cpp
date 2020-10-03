#include "include/material.hpp"
#include "include/flatMaterial.hpp"

template <>
std::vector<Factory<Material, Arguments>::ReadFunPtr> Factory<Material, Arguments>::registeredFuns = std::vector<Factory<Material, Arguments>::ReadFunPtr>();
DerivedRegistrar<Material, Material> __initMaterial;
DerivedRegistrar<Material, FlatMaterial> __initFlatMaterial;

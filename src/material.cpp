#include "include/material.hpp"
#include "include/flatMaterial.hpp"
#include "include/BlinnPhongMaterial.hpp"

template <>
std::vector<Factory<Material, Arguments>::ReadFunPtr> Factory<Material, Arguments>::registeredFuns = std::vector<Factory<Material, Arguments>::ReadFunPtr>();
DerivedRegistrar<Material, Material> __initMaterial;
DerivedRegistrar<Material, FlatMaterial> __initFlatMaterial;
DerivedRegistrar<Material, BlinnPhongMaterial> __initBlinnPhongMaterial;

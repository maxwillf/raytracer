#include "include/lightSource.hpp"

template <>
std::vector<Factory<LightSource, Arguments>::ReadFunPtr> Factory<LightSource, Arguments>::registeredFuns = std::vector<Factory<LightSource, Arguments>::ReadFunPtr>();
DerivedRegistrar<LightSource, LightSource> __initLightSource;
DerivedRegistrar<LightSource, AmbientLight> __initAmbientLight;
DerivedRegistrar<LightSource, DirectionalLight> __initDirectionalLight;
DerivedRegistrar<LightSource, PointLight> __initPointLight;

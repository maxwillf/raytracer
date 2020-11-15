#include "include/integrator.hpp"
#include "include/BlinnPhongIntegrator.hpp"
#include "include/flatIntegrator.hpp"

template <>
std::vector<Factory<Integrator, Arguments>::ReadFunPtr> Factory<Integrator, Arguments>::registeredFuns = std::vector<Factory<Integrator, Arguments>::ReadFunPtr>();
DerivedRegistrar<Integrator, Integrator> __initIntegrator;
DerivedRegistrar<Integrator, SamplerIntegrator> __initSamplerIntegrator;
DerivedRegistrar<Integrator, FlatIntegrator> __initFlatIntegrator;
DerivedRegistrar<Integrator, BlinnPhongIntegrator> __BlinnPhongIntegrator;

#include "include/background.hpp"

template <>
std::vector<Factory<Background, Arguments>::ReadFunPtr> Factory<Background, Arguments>::registeredFuns = std::vector<Factory<Background, Arguments>::ReadFunPtr>();
DerivedRegistrar<Background, Background> ___initBg;

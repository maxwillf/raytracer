#include "camera.h"
template <>
std::vector<Factory<Camera, Arguments>::ReadFunPtr> Factory<Camera, Arguments>::registeredFuns = std::vector<Factory<Camera, Arguments>::ReadFunPtr>();
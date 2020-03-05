#include "camera.h"
#include "ortographicCamera.h"
template <>
std::vector<Factory<Camera, Arguments>::ReadFunPtr> Factory<Camera, Arguments>::registeredFuns = std::vector<Factory<Camera, Arguments>::ReadFunPtr>();
DerivedRegistrar<Camera, Camera> __initCamera;
DerivedRegistrar<Camera, OrtographicCamera> __initOrtographic;
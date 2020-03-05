#include "film.h"

template <>
std::vector<Factory<Film, Arguments>::ReadFunPtr> Factory<Film, Arguments>::registeredFuns = std::vector<Factory<Film, Arguments>::ReadFunPtr>();
DerivedRegistrar<Film, Film> ___initFilm;
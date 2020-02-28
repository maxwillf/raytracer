#include "factory.hpp"
#include "argument.h"
#include <algorithm>

class Film
{
private:
  int xres;
  int yres;
  string type;
  string filename; // auto it = std::find_if(attributes.begin(), attributes.end(), [](xmlAttribute attr) {
                   //   return get<0>(attr) == "xres";
                   // });
  string img_type;

public:
  Film(){};
  Film(vector<Argument> attributes)
  {
    xres = findAttribute(attributes, "x_res").getValue<int>();
    yres = findAttribute(attributes, "y_res").getValue<int>();
    filename = findAttribute(attributes, "filename").getValue<std::string>();
    img_type = findAttribute(attributes, "img_type").getValue<std::string>();
  };

  int getWidth() { return xres; }
  int getHeight() { return yres; }

  static Film *Make(Arguments args)
  {
    if (get<0>(args) == "film")
    {
      vector<Argument> arguments = get<1>(args);
      return new Film(arguments);
    }
    else
    {
      return nullptr;
    }
  };
  // virtual Film *Make(Arguments args) = 0;
  ~Film();

  friend DerivedRegistrar<Film, Film>;
};

template <>
std::vector<Factory<Film, Arguments>::ReadFunPtr> Factory<Film, Arguments>::registeredFuns = std::vector<Factory<Film, Arguments>::ReadFunPtr>();
DerivedRegistrar<Film, Film> ___initFilm;
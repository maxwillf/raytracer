#pragma once

#include "factory.hpp"
#include "argument.h"
#include <algorithm>

class Film
{
private:
  int xres;
  int yres;
  string type;
  std::vector<int> cropWindow;
  bool gammaCorrected;
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
  std::string getFilename() { return filename; }
  std::string getImgType() { return img_type; }

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

  friend DerivedRegistrar<Film, Film>;
};

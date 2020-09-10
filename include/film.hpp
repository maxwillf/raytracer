#pragma once

#include <algorithm>
#include "vec3.h"
#include "factory.hpp"
#include "argument.h"

class Film
 {
   private:
     int xres;
     int yres;
     string type;
     std::vector<int> cropWindow;
     bool gammaCorrected;
     string filename;
     string img_type;
     std::vector<std::vector<vec3>> buffer;

   public:
     Film(){};
     Film(vector<Argument> attributes)
     {
       xres = findAttribute(attributes, "x_res").getValue<int>();
       yres = findAttribute(attributes, "y_res").getValue<int>();
       filename = findAttribute(attributes, "filename").getValue<std::string>();
       img_type = findAttribute(attributes, "img_type").getValue<std::string>();
       buffer = std::vector<std::vector<vec3>>(yres, std::vector<vec3>(xres));
     };

     int getWidth() { return xres; }
     int getHeight() { return yres; }
     std::string getFilename() { return filename; }
     std::string getImgType() { return img_type; }
     void setPoint(int x, int y, vec3 color){
      buffer[yres - 1 -y][x] = color;
    }
    void writeToFile();

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

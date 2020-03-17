#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "vec3.h"
#include "argument.h"
#include "factory.hpp"
#include "lodepng.h"

class Background
{
private:
  string type;
  string mapping;
  string filename;
  vec3 color;
  vec3 bl;
  vec3 br;
  vec3 tl;
  vec3 tr;

  std::vector<std::vector<vec3>> image;

public:
  Background(){};
  vec3 getColor() { return color; };
  vec3 getColor(float i, float j)
  {
    if (color.squared_length() != 0)
    {
      return color;
    }
    else
    {
      vec3 xVal = (tl * (1 - i) + bl * i);
      vec3 yVal = (tr * (1 - i) + br * i);
      return xVal * (1 - j) + yVal * j;
    }
  }

  void loadBgFromFilename(std::string path)
  {
    std::vector<unsigned char> image;
    unsigned int width, height;
    std::cout << path << std::endl;
    unsigned error = lodepng::decode(image, width, height, path);
    if (error)
    {
      std::cout << "rip" << std::endl;
    }
    else
    {
      size_t imageLen = image.size();
      this->image = std::vector<std::vector<vec3>>(height,std::vector<vec3>(width));
      int imageIndex = 0;
      if (imageLen % 3 == 0)
      {
        for (size_t i = 0; i < height; i++)
        {
          for (size_t j = 0; j < width; j++)
          {
            this->image[height][width] = vec3{image[imageIndex], image[imageIndex+1], image[imageIndex+2]};
            imageIndex +=3;
          }
        }
      }
    }
    std::cout << image.size() << std::endl;
  }
  Background(vector<Argument> attributes)
  {
    type = "colors";
    mapping = "screen";
    color = vec3(0.0, 0.0, 0.0);
    bl = vec3(0.0, 0.0, 0.0);
    br = vec3(0.0, 0.0, 0.0);
    tl = vec3(0.0, 0.0, 0.0);
    tr = vec3(0.0, 0.0, 0.0);

    for (auto &&attr : attributes)
    {
      if (attr.getKey() == "type")
      {
        type = attr.getValue<std::string>();
      }
      if (attr.getKey() == "color")
      {
        color = vec3(attr.getValues<float>());
      }
      if (attr.getKey() == "mapping")
      {
        mapping = attr.getValue<std::string>();
      }
      if (attr.getKey() == "bl")
      {
        bl = attr.getValues<float>();
      }
      if (attr.getKey() == "br")
      {
        br = attr.getValues<float>();
      }
      if (attr.getKey() == "tl")
      {
        tl = attr.getValues<float>();
      }
      if (attr.getKey() == "tr")
      {
        tr = attr.getValues<float>();
      }
      if (attr.getKey() == "filename")
      {
        loadBgFromFilename(attr.getValue<std::string>());
      }
    }
  }
  static Background *Make(Arguments args)
  {
    if (get<0>(args) == "background")
    {
      return new Background(get<1>(args));
    }
    else
    {
      return nullptr;
    }
  }

  friend DerivedRegistrar<Background, Background>;
};

#endif
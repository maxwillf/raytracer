#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "vec3.h"
#include "argument.h"
#include "factory.hpp"

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

public:
  Background(){};
  vec3 getColor() { return color; };
  vec3 getColor(float i, float j)
  {
    vec3 xVal = (tl * (1 - i) + bl * i);
    vec3 yVal = (tr * (1 - i) + br * i);
    return xVal * (1 - j) + yVal * j;
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
      // std::cout << attr.getKey() << std::endl;
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
  // Background(vec3 position, vec3 target, vec3 up) : position(position), target(target), up(up){};
  ~Background();

  friend DerivedRegistrar<Background, Background>;
};

#endif
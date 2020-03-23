#pragma once
#ifndef __BACKGROUND__
#define __BACKGROUND__

#include "vec3.h"
#include "math.h"

#define PI 3.14159265
#define radToDegrees(x) 180 / PI *x

#include "ray.h"
#include "argument.h"
#include "factory.hpp"
#include "lodepng.h"

class Background
{
private:
  enum class ScreenMapping
  {
    screen,
    spherical,
  };

  string type;
  ScreenMapping mapping;
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
  vec3 getColor(float i, float j, Ray ray)
  {
    if (!image.empty())
    {
      switch (mapping)
      {
      case ScreenMapping::screen:
      {
        int height = image.size();
        int width = image[0].size();
        int newX = width * i;
        int newY = height * j;
        //        std::cout << newX << " " << newY << std::endl;
        return vec3(this->image[newY][newX]);
      }

      case ScreenMapping::spherical:
        Point pointInRay = ray(1.0);
        // correção dos eixos x,y z
        Point p = unit_vector(Point(-pointInRay[1], -pointInRay[0], pointInRay[2]));
        double convertFromRadians = 180.0 / PI;
        float radius = p.length();
        float phi = radToDegrees(atan2(p[1], p[0]) + PI);
        float theta = radToDegrees(acos(p[2] / radius));
        float newU = phi / 360.0;
        float newV = theta / 180.0;

        float height = image.size();
        float width = image[0].size();
        int newX = abs(width * newU);
        int newY = abs(height * newV);
        //        std::cout << newX << " " << newY << std::endl;
        return vec3(this->image[newY][newX]);
        break;
      }
    }
    else
    {

      if (color.squared_length() != 0)
      {
        return color;
      }
      else
      {
        vec3 xVal = (tl * (1 - j) + bl * j);
        vec3 yVal = (tr * (1 - j) + br * j);
        return xVal * (1 - i) + yVal * i;
      }
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
      std::cerr << "Failed to load xml png file, please check if the path was correct" << std::endl;
      exit(-1);
    }
    else
    {
      size_t imageLen = image.size();
      this->image = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));
      int imageIndex = 0;
      if (imageLen % 4 == 0)
      {
        for (size_t i = 0; i < height; i++)
        {
          for (size_t j = 0; j < width; j++)
          {
            this->image[i][j] = vec3{image[imageIndex], image[imageIndex + 1], image[imageIndex + 2]};
            // avançar 4 indices invés de 3 porque imagens png tem rgb e alpha
            imageIndex += 4;
          }
        }
      }
      else
      {
        std::cerr << "Image had malformed pixels, the amount of bytes wasn't a multiple of 3" << std::endl;
        exit(-1);
      }
    }
    //std::cout << image.size() << std::endl;
  }
  Background(vector<Argument> attributes)
  {
    type = "colors";
    color = vec3(0.0, 0.0, 0.0);
    bl = vec3(0.0, 0.0, 0.0);
    br = vec3(0.0, 0.0, 0.0);
    tl = vec3(0.0, 0.0, 0.0);
    tr = vec3(0.0, 0.0, 0.0);

    for (auto &&attr : attributes)
    {
      std::cout << attr.getKey() << std::endl;
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
        std::string mappingAttr = attr.getValue<std::string>();
        if (mappingAttr == "screen")
        {
          mapping = ScreenMapping::screen;
        }
        else if (mappingAttr == "spherical")
        {
          mapping = ScreenMapping::spherical;
        }
        else
        {
          std::cerr << "Wrong mapping type input for background" << std::endl;
          exit(-1);
        }
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
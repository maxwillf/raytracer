#pragma once

#include "tinyxml2.h"
#include "camera.h"
#include "ortographicCamera.h"
#include "background.h"
#include "film.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include "vec3.h"
#include "argument.h"
#include "primitive.h"
#include "sphere.h"

class Engine
{
private:
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Background> background;
  std::vector<std::vector<vec3>> buffer;
  std::vector<shared_ptr<Primitive>> obj_list;

  std::vector<Arguments> args;

  void loadObjects();

public:
  void readArguments(tinyxml2::XMLElement *element);
  void readCamera(tinyxml2::XMLNode *node);
  void render();
    Engine(std::string path);
  ~Engine();
};

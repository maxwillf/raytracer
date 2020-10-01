#pragma once

#include "tinyxml2.h"
#include "camera.hpp"
#include "ortographicCamera.hpp"
#include "background.hpp"
#include "film.hpp"
#include <iostream>
#include <fstream>
#include <memory>
#include "vec3.hpp"
#include "argument.hpp"
#include "primitive.hpp"
#include "sphere.hpp"

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
    void run();
    void render();
    void loadSceneFile(std::string path);
    Engine();
    ~Engine();
};

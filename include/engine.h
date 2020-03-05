#include "tinyxml2.h"
#include "camera.h"
#include "background.h"
#include "film.h"
#include <iostream> 
#include <fstream> 
#include <memory>
#include "vec3.h"
#include "argument.h"

class Engine
{
private:
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Film> film;
  std::shared_ptr<Background> background;
  std::vector<std::vector<vec3>> buffer;

  std::vector<Arguments> args;

  void loadObjects();

public:
  void readArguments(tinyxml2::XMLElement *element);
  void readCamera(tinyxml2::XMLNode *node);
  void writeToFile(std::string path);
  void render();
  Engine(std::string path);
  ~Engine();
};

#include "tinyxml2.h"
#include "camera.h"
#include "background.h"
#include "film.h"
#include "vec3.h"
#include "argument.h"
#include <memory>

class Engine
{
private:
  std::shared_ptr<Camera> camera;
  std::shared_ptr<Film> film;
  std::shared_ptr<Background> background;

  std::vector<Arguments> args;
  //  shared_ptr<Settings> settings;

public:
  void readArguments(tinyxml2::XMLElement *element);
  //  void readNode(tinyxml2::XMLNode *node);
  void readCamera(tinyxml2::XMLNode *node);
  Engine(std::string path);
  ~Engine();
};

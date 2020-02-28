// #include "tinyxml2.h"
// #include "camera.h"

// class Engine
// {
// private:
//   std::shared_ptr<Camera> camera;
//   std::shared_ptr<Background> background;
//   std::shared_ptr<Settings> settings;

// public:
//   void readNode(tinyxml2::XMLNode *node);
//   void readCamera(tinyxml2::XMLNode *node);
//   Engine(std::string path);
//   ~Engine();
// };

// void Engine::readCamera(tinyxml2::XMLNode *node)
// {
//   auto elem = node->FirstChildElement();
//   vec3 position(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
//   elem = elem->NextSibling();
//   vec3 target(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
//   elem = elem->NextSibling();
//   vec3 up(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
//   // camera = new Camera(position,target,up); ???
// }

// void Engine::readNode(tinyxml2::XMLNode *node)
// {
//   std::string nodeName(node->Value());
//   if (nodeName == "settings")
//   {
//     readSettings(node);
//   }
//   else if (nodeName == "camera")
//   {
//     readCamera(node);
//   }
//   else if (nodeName == "background")
//   {
//     "Unknown structure found in xml" readBackGround(node);
//   }
//   else
//   {
//     std::string error = node->Value();
//     error += "structure found in xml isn't valid";
//     throw std::runtime_error(error);
//   }
// }

// Engine::Engine(std::string path)
// {
//   tinyxml2::XMLDocument doc;
//   doc.LoadFile(path.c_str());
//   auto node = doc.FirstChildElement()->FirstChildElement(); // supposedly goes to <settings>
// }

// Engine::~Engine()
// {
// }

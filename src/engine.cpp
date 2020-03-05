#include "engine.h"

void Engine::readCamera(tinyxml2::XMLNode *node)
{
  tinyxml2::XMLElement *elem = node->FirstChildElement();
  vec3 position(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
  elem = elem->NextSiblingElement();
  vec3 target(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
  elem = elem->NextSiblingElement();
  vec3 up(elem->FloatAttribute("x"), elem->FloatAttribute("y"), elem->FloatAttribute("z"));
  // camera = new Camera(position,target,up); ???
}

//void Engine::readNode(tinyxml2::XMLNode *node)
//{
//  std::string nodeName(node->Value());
//  if (nodeName == "settings")
//  {
//    readSettings(node);
//  }
//  else if (nodeName == "camera")
//  {
//    readCamera(node);
//  }
//  else if (nodeName == "background")
//  {
//    "Unknown structure found in xml" readBackground(node);
//  }
//  else
//  {
//    std::string error = node->Value();
//    error += "structure found in xml isn't valid";
//    throw std::runtime_error(error);
//  }
//}

Engine::Engine(std::string path)
{
  args = std::vector<Arguments>();
  tinyxml2::XMLDocument doc;
  doc.LoadFile(path.c_str());
  auto node = doc.FirstChildElement()->FirstChildElement(); // supposedly goes to <settings>
  while (node != nullptr)
  {
    readArguments(node);
    node = node->NextSiblingElement();
    std::string nodeName = node->Value();
    if (nodeName == "world_begin")
    {
      node = node->FirstChildElement();
    }
  }
}

void Engine::readArguments(tinyxml2::XMLElement *element)
{
  std::string elemName = element->Value();
  auto attribute = element->FirstAttribute();
  std::vector<Argument> arg;
  while (attribute != nullptr)
  {
    arg.push_back(Argument(attribute));
    attribute = attribute->Next();
  };

  if (elemName == "camera")
  {
    auto cameraType = std::string(element->Attribute("type"));
    Arguments currentArgs = std::make_tuple(cameraType, arg);
    this->args.push_back(currentArgs);
  }
  else
  {
    Arguments currentArgs = std::make_tuple(elemName, arg);
    this->args.push_back(currentArgs);
  }
}
Engine::~Engine()
{
}
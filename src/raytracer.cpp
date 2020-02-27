/**
 * @file driver_dictionary.cpp
 * @brief File for DAL and DSAL classes tests .
 */

#include <iostream>   // cout, endl
#include <cassert>    // assert()
#include <algorithm>  // shuffle
#include <random>     // random_device, mt19937
#include <iterator>   // std::begin(), std::end()
#include "argument.h" // std::begin(), std::end()
#include "camera.h"   // std::begin(), std::end()
#include "ortographicCamera.h"   // std::begin(), std::end()
#include "film.h"
#include "tinyxml2.h"

int main(void)
{
  tinyxml2::XMLDocument doc;
  doc.LoadFile("resources/sample.xml");
  tinyxml2::XMLNode *root = doc.FirstChild();
  auto film = root->FirstChildElement("film");
  auto attribute = film->FirstAttribute();
  std::vector<Argument> arguments;
  while (attribute != nullptr)
  {
    // std::cout << Argument(attribute).getKey() << std::endl;
    arguments.push_back(Argument(attribute));
    attribute = attribute->Next();
  };
  Arguments args = std::make_tuple("film",arguments);
  Film* producedFilm = Factory<Film,Arguments>::Produce(args);
  std::cout << std::endl;
  
  auto cameraType = std::string(root->FirstChildElement("camera")->Attribute("type"));
  auto cameraArgs = std::make_tuple(cameraType,std::vector<Argument>());
  Camera* producedCamera = Factory<Camera,Arguments>::Produce(cameraArgs);
  return 0;
}
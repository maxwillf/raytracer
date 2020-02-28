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
#include "ortographicCamera.h"
#include "background.h"
#include "film.h"
#include "tinyxml2.h"

#include <fstream>

void writePpm(std::string path, std::vector<std::vector<vec3>> buffer)
{
  std::ofstream fs(path);

  int width = buffer[0].size();
  int height = buffer.size();
  int maxColorValue = 255;
  fs << "P3" << std::endl;
  fs << width << " " << height << std::endl;
  fs << maxColorValue << std::endl;

  for (int i = 0; i < height; ++i)
  {
    for (int j = 0; j < width; ++j)
    {
      fs << buffer[i][j] << std::endl;
    }
  }
}

int main(void)
{
  tinyxml2::XMLDocument doc;
  doc.LoadFile("resources/bilinear.xml");
  tinyxml2::XMLNode *root = doc.FirstChild();
  auto film = root->FirstChildElement("film");
  auto attribute = film->FirstAttribute();
  std::vector<Argument> arguments;
  while (attribute != nullptr)
  {
    arguments.push_back(Argument(attribute));
    attribute = attribute->Next();
  };

  Arguments args = std::make_tuple("film", arguments);
  arguments.clear();
  Film *producedFilm = Factory<Film, Arguments>::Produce(args);
  std::cout << std::endl;

  auto cameraType = std::string(root->FirstChildElement("camera")->Attribute("type"));
  auto cameraArgs = std::make_tuple(cameraType, std::vector<Argument>());
  Camera *producedCamera = Factory<Camera, Arguments>::Produce(cameraArgs);

  auto background = root->FirstChildElement("background");
  std::string bgKey = "background";
  attribute = background->FirstAttribute();
  while (attribute != nullptr)
  {
    arguments.push_back(Argument(attribute));
    attribute = attribute->Next();
  };
  Background *bg = Factory<Background, Arguments>::Produce(std::make_tuple(bgKey, arguments));

  std::vector<std::vector<vec3>> buffer(producedFilm->getHeight(), std::vector<vec3>(producedFilm->getWidth()));

  int height = producedFilm->getHeight();
  int width = producedFilm->getWidth();
  for (size_t h = 0; h < height; h++)
  {
    for (size_t w = 0; w < width; w++)
    {
      double i = double(h) / height;
      double j = double(w) / width;
      buffer[h][w] = bg->getColor(i, j);
    }
  }
  writePpm("teste2.ppm", buffer);
  return 0;
}
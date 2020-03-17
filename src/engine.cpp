#include "engine.h"

void Engine::render()
{
  std::shared_ptr<Film> filmPtr = nullptr;
  Arguments lookat = std::make_tuple<std::string, std::vector<Argument>>(std::string(), std::vector<Argument>());
  for (auto &&arg : args)
  {
    std::string tagName = get<0>(arg);
    auto constructionArguments = get<1>(arg);
    auto produceArgs = std::make_tuple(tagName, constructionArguments);
    if (tagName == "camera")
    {
      this->camera = std::shared_ptr<Camera>(Factory<Camera, Arguments>::Produce(produceArgs));
    }
    if (tagName == "film")
    {
      filmPtr = std::shared_ptr<Film>(Factory<Film, Arguments>::Produce(produceArgs));
    }
    if (tagName == "lookat")
    {
      lookat = arg;
    }
    if (tagName == "background")
    {
      this->background = std::shared_ptr<Background>(Factory<Background, Arguments>::Produce(produceArgs));
    }
  }
  if (!get<1>(lookat).empty())
  {
    camera->setFrame(lookat);
    std::cout << "sets" << std::endl;
  }
  if (filmPtr != nullptr)
  {
  std::cout << "sets" << std::endl;
    camera->setFilm(filmPtr);
  }
  int height = camera->film->getHeight();
  int width = camera->film->getWidth();
  buffer = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));
#pragma omp parallel for collapse(2)
  for (int h = 0; h < height; h++)
  {
    for (int w = 0; w < width; w++)
    {
      float i = float(h) / height;
      float j = float(w) / width;
      buffer[h][w] = this->background->getColor(i, j);
    }
  }
}

void Engine::writeToFile(std::string path)
{
  std::ofstream fs(path);

  int width = this->buffer[0].size();
  int height = this->buffer.size();
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

Engine::Engine(std::string path)
{
  args = std::vector<Arguments>();
  buffer = std::vector<std::vector<vec3>>();
  tinyxml2::XMLDocument doc;
  doc.LoadFile(path.c_str());
  auto node = doc.FirstChildElement()->FirstChildElement(); // supposedly goes to <settings>
  while (node != nullptr)
  {
    readArguments(node);
    node = node->NextSiblingElement();
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

  Arguments currentArgs = std::make_tuple(elemName, arg);
  this->args.push_back(currentArgs);
}
Engine::~Engine()
{
}
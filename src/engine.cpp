#include "include/engine.hpp"

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
    if (tagName == "object")
    {
      obj_list.push_back(std::shared_ptr<Primitive>(Factory<Primitive, Arguments>::Produce(produceArgs)));
    }
  }
  if (!get<1>(lookat).empty())
  {
    camera->setFrame(lookat);
  }
  if (filmPtr != nullptr)
  {
    std::cout << "setting film" << std::endl;
    camera->setFilm(filmPtr);
  }
  else
  {
    std::cout << "nullptr film" << std::endl;
  }

  int height = camera->film->getHeight();
  int width = camera->film->getWidth();

#pragma omp parallel for collapse(2)
  for (int h = height - 1; h >= 0; h--)
  {
    for (int w = 0; w < width; w++)
    {
      float j = float(height -1 -h) / height;
      float i = float(width - 1 - w) / width;
      Ray ray = camera->generate_ray(w, h);
//std::cout << ray.direction() << " " << ray.origin() << std::endl;
      vec3 color = this->background->getColor(i, j, ray);
      for (const shared_ptr<Primitive> &p : obj_list)
      {
        if (p->intersect_p(ray))
        {
        // std::cout << p << std::endl;
          color = vec3(255, 0, 0);
        }
      }
      camera->film->setPoint(w, h, color);
    }
  }
  camera->film->writeToFile();
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

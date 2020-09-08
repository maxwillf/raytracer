#include "engine.h"
#include "lodepng.h"

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
    camera->setFilm(filmPtr);
  }

  int height = camera->film->getHeight();
  int width = camera->film->getWidth();
  buffer = std::vector<std::vector<vec3>>(height, std::vector<vec3>(width));

#pragma omp parallel for collapse(2)
  for (int h = height - 1; h >= 0; h--)
  {
    for (int w = 0; w < width; w++)
    {
      float j = float(h) / height;
      float i = float(w) / width;
      Ray ray = camera->generate_ray(w, h);
      //std::cout << ray.direction() << " " << ray.origin() << std::endl;
      if (buffer[h][w] != vec3(255, 0, 0))
      {
        buffer[h][w] = this->background->getColor(i, j, ray);
      }
      for (const shared_ptr<Primitive> &p : obj_list)
      {
        if (p->intersect_p(ray))
        {
          // std::cout << p << std::endl;
          buffer[height - 1 - h][w] = vec3(255, 0, 0);
        }
      }
    }
  }

  writeToFile(camera->film);
}

void Engine::writeToFile(std::shared_ptr<Film> film)
{
  std::ofstream fs(film->getFilename());
  int width = this->buffer[0].size();
  int height = this->buffer.size();

  if (film->getImgType() == "png")
  {
    std::vector<unsigned char> image;
    image.resize(width * height * 4);
    for (int i = 0; i < height; ++i)
    {
      for (int j = 0; j < width; ++j)
      {
        image[4 * width * i + 4 * j + 0] = buffer[i][j][0];
        image[4 * width * i + 4 * j + 1] = buffer[i][j][1];
        image[4 * width * i + 4 * j + 2] = buffer[i][j][2];
        image[4 * width * i + 4 * j + 3] = 255;
      }
    }
    lodepng::encode(film->getFilename(), image, width, height);
  }
  else
  {
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
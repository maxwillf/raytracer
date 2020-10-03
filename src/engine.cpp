#include "include/engine.hpp"
#include "include/aggregate.hpp"
#include "include/integrator.hpp"
#include "include/scene.hpp"
#include <memory>

void Engine::run()
{
  std::shared_ptr<Film> filmPtr = nullptr;
  unique_ptr<Integrator> integrator = nullptr;
  shared_ptr<Material> currentMaterial;
  shared_ptr<Aggregate> aggregate = make_shared<Aggregate>();

  Arguments lookat = std::make_tuple<std::string, std::vector<Argument>>(std::string(), std::vector<Argument>());
  for (auto &&arg : args)
  {
    std::string tagName = get<0>(arg);
    auto constructionArguments = get<1>(arg);
    auto produceArgs = std::make_tuple(tagName, constructionArguments);
    if (tagName == "camera")
    {
      this->camera = std::shared_ptr<Camera>(Factory<Camera, Arguments>::Produce(produceArgs));
      camera->setFrame(lookat);
      std::cout << "setting camera frame" << std::endl;
      if(integrator != nullptr) {
        std::cout << "Setting a new camera for the integrator" << std::endl;
        integrator->setCamera(camera);
      }
    }
      if (tagName == "film")
      {
        filmPtr = std::shared_ptr<Film>(Factory<Film, Arguments>::Produce(produceArgs));
        std::cout << "setting camera film" << std::endl;
    camera->setFilm(filmPtr);
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
       auto obj =
         std::shared_ptr<Primitive>(Factory<Primitive, Arguments>::Produce(produceArgs));
       obj->setMaterial(currentMaterial);
        aggregate->addPrimitive(obj);
  //        obj_list.push_back(std::shared_ptr<Primitive>(Factory<Primitive, Arguments>::Produce(produceArgs)));
      }
      if(tagName == "world_end"){
        std::cout << "should be rendered first" << std::endl;
        Scene scene(aggregate,background);
        integrator->render(scene);
        //render();
      }
        if(tagName == "material" ){
          currentMaterial =
            std::shared_ptr<Material>(Factory<Material, Arguments>::Produce(produceArgs));
        }
        if(tagName == "integrator" ){
          integrator =
            std::unique_ptr<Integrator>(Factory<Integrator, Arguments>::Produce(produceArgs));
          integrator->setCamera(camera);
        }
        if(tagName == "render_again" ){
          std::cout << "should be rendered second" << std::endl;
           Scene scene(aggregate,background);
           integrator->render(scene);
           //  render();
        }
  }
}


void Engine::render() {
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


void Engine::loadSceneFile(std::string path)
{
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

  // if there are more than one scene files, read them
  if(elemName == "include"){
    std::string filename = element->FirstAttribute()->Value();
    std::cout << "found include: " << filename << std::endl;
    loadSceneFile(filename);
  }

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


Engine::Engine()
{
  args = std::vector<Arguments>();
  buffer = std::vector<std::vector<vec3>>();
}

Engine::~Engine()
{
}

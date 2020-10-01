#include "include/engine.hpp"

int main(int argc, char **argv)
{
  if (argc != 2)
  {
    std::cerr << "Wrong amount of arguments, please insert a valid xml file name and the output file name" << std::endl;
    exit(-1);
  }
  Engine engine;
  engine.loadSceneFile(argv[1]);
  engine.run();
  //engine.writeToFile(argv[2]);
  return 0;
}

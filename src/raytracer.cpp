#include "engine.h"
#include "lodepng.h"

int main(int argc, char** argv)
{
  if(argc != 3){
    std::cerr << "Wrong amount of arguments, please insert a valid xml file name and the output file name" << std::endl;
    exit(-1);
  }
  std::vector<unsigned char> image;
  unsigned int width, height;
  unsigned error = lodepng::decode(image,width,height,"resources/grid.png");
  if(error){
    std::cout << "rip" << std::endl;
  }
  else {
  std::cout << width << " " << height << std::endl;
    for(auto && val : image){
      //std::cout << (int) val << std::endl;
    }
  }
  //Engine engine(argv[1]);
  //engine.render();
  //engine.writeToFile(argv[2]);
  return 0;
}

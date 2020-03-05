#include "engine.h"

int main(void)
{
  Engine engine("resources/bilinear.xml");
  engine.render();
  engine.writeToFile("blablabla.ppm");
  return 0;
}

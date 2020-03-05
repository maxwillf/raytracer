#pragma once
#ifndef __ARGUMENT__
#define __ARGUMENT__

#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
#include "tinyxml2.h"

class Argument
{
private:
  std::string argumentKey;
  std::vector<std::string> values;

public:
  Argument(const tinyxml2::XMLAttribute *attribute);

  std::string getKey();

  template <typename T>
  T getValue(){};

  template <typename T>
  std::vector<T> getValues(){};
};

Argument findAttribute(std::vector<Argument> attributes, std::string attrName);

using Arguments = std::tuple<std::string, std::vector<Argument>>;

#endif
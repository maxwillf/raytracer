#pragma once
#ifndef __ARGUMENT__
#define __ARGUMENT__

#include <iostream>
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
  Argument(std::string argumentKey,
           std::vector<std::string> values);

  std::string getKey() const;

  template <typename T>
  T getValue() const {};

  template <typename T>
  std::vector<T> getValues() const {};

  void print()
  {
    std::cout << argumentKey << std::endl;
    for (auto &&arg : values)
    {
      std::cout << arg << std::endl;
    }
  }
};

Argument findAttribute(std::vector<Argument> attributes, std::string attrName);

using Arguments = std::tuple<std::string, std::vector<Argument>>;

#endif

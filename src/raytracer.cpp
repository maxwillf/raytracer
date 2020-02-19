/**
 * @file driver_dictionary.cpp
 * @brief File for DAL and DSAL classes tests .
 */

#include <iostream>  // cout, endl
#include <cassert>   // assert()
#include <algorithm> // shuffle
#include <random>    // random_device, mt19937
#include <iterator>  // std::begin(), std::end()
#include "tinyxml2.h"

int main(void)
{
  tinyxml2::XMLDocument doc;
  doc.LoadFile("resources/sample.xml");
  tinyxml2::XMLNode *root = doc.FirstChild();
  // std::cout << (root->Parent()) << std::endl;
  // std::cout << (root->LastChild()->NextSibling() == nullptr) << std::endl;
  while (root != nullptr && (root->Parent() != 0 || root != doc.FirstChild()))
  {
    if (root->ToComment() == nullptr) // returns true if the node isn't a comment
    {
      std::cout << root->Value() << std::endl;
    }
    if (nullptr != root->FirstChild())
    {
      root = root->FirstChild();
    }
    else if (nullptr != root->NextSibling())
    {
      root = root->NextSibling();
    }
    else
    {
      root = root->Parent();
      root = root->NextSibling();
    }
  }
}
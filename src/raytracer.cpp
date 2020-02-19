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

#include <fstream>

void writePpm(std::string path){
	std::ofstream fs(path);
	
	int width =  800;
	int height = 600;
	int maxColorValue = 255;
	fs << "P3" << std::endl;
	fs << width << " " << height << std::endl;
	fs << maxColorValue << std::endl;

	for (int i = 0; i < width ; ++i) {
			for (int j = 0; j < height; ++j) {
					 fs << 75 << " " << 75 << " " << 75 << " ";
			}
			fs << std::endl;
	}
	std::cout << "ué" << std::endl;
}

int main(void)
{
  tinyxml2::XMLDocument doc;
  doc.LoadFile("resources/sample.xml");
  tinyxml2::XMLNode *root = doc.FirstChild();

	writePpm("teste.teste");
//  while (root != nullptr && (root->Parent() != 0 || root != doc.FirstChild()))
//  {
//    if (root->ToComment() == nullptr) // returns true if the node isn't a comment
//    {
//			auto elem = root->ToElement();
//			auto attr = elem->FirstAttribute();
//      std::cout << elem->Value() << " ";
//			while(attr != nullptr){
//					std::cout << attr->Name() << " ";
//					std::cout << attr->Value() << " ";
//					attr = attr->Next();
//			}
//			std::cout << std::endl;
//    }
//    if (nullptr != root->FirstChild())
//    {
//      root = root->FirstChild();
//    }
//    else if (nullptr != root->NextSibling())
//    {
//      root = root->NextSibling();
//    }
//    else
//    {
//      root = root->Parent();
//      root = root->NextSibling();
//    }
//  }
}

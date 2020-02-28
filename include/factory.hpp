#pragma once

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include "argument.h"

using namespace std;

//class Camera
//{
//};

// Factory class to produce Base* objects from an int (for simplicity).
// The class uses a list of registered function pointers, which attempt
// to produce a derived class based on the given int.
template <typename Base, typename Args>
class Factory
{
public:
  typedef Base *(*ReadFunPtr)(Args);

private:
  // for some reason it doesn't work if i inline and initialize it
  // it should work if used with -std=c++17 but seemingly it doesn't
  static vector<ReadFunPtr> registeredFuns; // = vector<ReadFunPtr>();

public:
  static void registerPtr(ReadFunPtr ptr)
  {
    registeredFuns.push_back(ptr);
    return;
  }
  static Base *Produce(Args args)
  {
    //	auto value = ptrMap.find(str);
    Base *ptr = NULL;
    for (typename vector<ReadFunPtr>::const_iterator I = registeredFuns.begin(), E = registeredFuns.end(); I != E; ++I)
    {
      ptr = (*I)(args);
      if (ptr != NULL)
      {
        return ptr;
      }
    }
    return NULL;
  }
};
// initialize vector of funptrs
// using xmlAttribute = tuple<string, string>;
using Arguments = tuple<string, vector<Argument>>;
// using Fact = Factory<Camera, Arguments>;
// template <>
//std::vector<Factory<Film,Arguments>::ReadFunPtr> Factory<Film,Arguments>::registeredFuns = std::vector<Factory<Film,Arguments>::ReadFunPtr>();

// Register Derived in the Factory so it will attempt to construct objects.
// This is done by adding the function pointer Derived::ProduceDerivedFromInt
// in the Factory's list of registered functions.
template <typename BaseClass, typename DerivedClass>
struct DerivedRegistrar
{
  DerivedRegistrar()
  {
    Factory<BaseClass, Arguments>::registerPtr(&(DerivedClass::Make));
  }
};

// An example Derived class, which can be produced from an int=0.
// The producing method is static to avoid the need for prototype objects.
//class Derived : public Camera
//{
//private:
//  static Camera *Make(Arguments attrs)
//  {
//    if (get<0>(attrs) == "derived")
//      return new Derived();
//    return NULL;
//  }
//
//public:
//  Derived(){};
//
//  // registrar is a friend because we made the producing function private
//  // this is not necessary, may be desirable (e.g. encapsulation)
//  friend DerivedRegistrar<Camera, Derived>;
//};

// Registers a function pointer that creates an Object from the Derived class
// that inherits from the Camera class;

//DerivedRegistrar<Camera, Derived> derived;

// string derived = "derived";
// vector<xmlAttribute> testeVec;
// Camera *test = Fact::Produce(make_tuple(derived, testeVec));
#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

class Camera
{
};

// Factory class to produce Base* objects from an int (for simplicity).
// The class uses a list of registered function pointers, which attempt
// to produce a derived class based on the given int.
template <typename Base, typename Args>
class Factory
{
public:
  typedef Base *(*ReadFunPtr)(Args);

private:
  static vector<ReadFunPtr> registeredFuns;

public:
  static void registerPtr(ReadFunPtr ptr)
  {
    registeredFuns.push_back(ptr);
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
using xmlAttribute = tuple<string, string>;
using Arguments = tuple<string, vector<xmlAttribute>>;
using Fact = Factory<Camera, Arguments>;
template <>
std::vector<Fact::ReadFunPtr> Fact::registeredFuns = std::vector<Factory::ReadFunPtr>();

// Register Derived in the Factory so it will attempt to construct objects.
// This is done by adding the function pointer Derived::ProduceDerivedFromInt
// in the Factory's list of registered functions.
template <typename BaseClass, typename DerivedClass>
struct DerivedRegistrar
{
  DerivedRegistrar()
  {
    Factory<BaseClass, Arguments>::registerPtr(&(DerivedClass::ProduceDerivedFromStrAndXmlAttr));
  }
};

// An example Derived class, which can be produced from an int=0.
// The producing method is static to avoid the need for prototype objects.
class Derived : public Camera
{
private:
  static Camera *ProduceDerivedFromStrAndXmlAttr(tuple<string, vector<xmlAttribute>> attrs)
  {
    if (get<0>(attrs) == "derived")
      return new Derived();
    return NULL;
  }

public:
  Derived(){};

  // registrar is a friend because we made the producing function private
  // this is not necessary, may be desirable (e.g. encapsulation)
  friend DerivedRegistrar<Camera, Derived>;
};

// Registers a function pointer that creates an Object from the Derived class
// that inherits from the Camera class;
DerivedRegistrar<Camera, Derived> derived;

int main()
{
  // attempt to produce a Derived object from 1: should fail
  //    Base* test=Factory::Produce(1);
  //    std::cout << test << std::endl; // outputs 0

  // attempt to produce a Derived object from 0: works
  string derived = "derived";
  vector<xmlAttribute> testeVec;
  Camera *test = Fact::Produce(make_tuple(derived, testeVec));
  //    Base* test2 = remove_pointer<decltype(test)>::type::ProduceDerivedFromStr(0);
  std::cout << test << std::endl; // outputs an address
                                  //   std::cout << test2 << std::endl; // outputs an address
}

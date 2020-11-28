#include "include/argument.hpp"

Argument::Argument(const tinyxml2::XMLAttribute *attribute)
{
  argumentKey = std::string(attribute->Name());
  char *token = strdup(attribute->Value());
  token = std::strtok(token, " ");
  while (token != NULL)
  {
    values.push_back(token);
    token = std::strtok(NULL, " ");
  }
  free(token);
};

Argument::Argument(std::string argumentKey, std::vector<std::string> values)
{
  this->argumentKey = argumentKey;
  this->values = values;
};

std::string Argument::getKey() const
{
  return argumentKey;
}

template <typename T>
T getValue() = delete;

template <typename T>
std::vector<T> getValues() = delete;

Argument findAttribute(std::vector<Argument> attributes, std::string attrName)
{

  auto it = std::find_if(attributes.begin(), attributes.end(), [attrName](Argument attr) {
    return attr.getKey() == attrName;
  });
  if (it != attributes.end())
  {
    return *it;
  }
  else
  {
    throw std::runtime_error("Attribute" + attrName + "not found");
  }
}

template <>
int Argument::getValue<int>() const
{
  return std::stoi(values[0]);
}
template <>
double Argument::getValue<double>() const
{
  return std::stod(values[0]);
}
template <>
std::string Argument::getValue<std::string>() const
{
  return values[0];
}

template <>
std::vector<int> Argument::getValues<int>() const
{
  std::vector<std::string> vals(values);
  std::vector<int> intValues;
  std::transform(vals.begin(), vals.end(), std::back_inserter(intValues), [](std::string str) { return std::stoi(str); });
  return intValues;
}
template <>
std::vector<double> Argument::getValues<double>() const
{
  std::vector<std::string> vals(values);
  std::vector<double> doubleValues;
  std::transform(vals.begin(), vals.end(), std::back_inserter(doubleValues), [](std::string str) { return std::stod(str); });
  return doubleValues;
}
template <>
std::vector<std::string> Argument::getValues<std::string>() const
{
  return values;
}

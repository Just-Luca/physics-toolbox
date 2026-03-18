#ifndef LIB_H
#define LIB_H

// Default template arguments from c++11

template <typename genericType, int nTimes = 5>
genericType multiply (genericType a)
{
  return a * static_cast<genericType>(nTimes);
}

template <int nTimes = 5>
std::string multiply (std::string a)
{
  std::string s = "";
  for (unsigned int i = 0;
       i < nTimes; i++) s += a;

  return s;
}

template <typename genericType>
genericType sum (genericType a, genericType b)
{
  return a + b;
}

template <typename genericType>
genericType double2 (genericType a)
{
  return a * 2;
}

#endif

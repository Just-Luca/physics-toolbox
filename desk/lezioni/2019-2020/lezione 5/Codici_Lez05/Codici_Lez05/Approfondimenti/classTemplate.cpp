/*
c++ -o classTemplate classTemplate.cpp
*/

#include <iostream>
#include <cmath>

class Circle
{
public:
  Circle(double Radius) { R = Radius; };
  ~Circle() {};
  double getPerimeter() { return 2*M_PI*R; }
private:
  double R;
};

class Square
{
public:
  Square(double Side) { S = Side; };
  ~Square() {};
  double getPerimeter() { return 4*S; }
private:
  double S;
};

template<class Sh1, class Sh2>
class CompareShapes
{
public:
  CompareShapes() {};
  ~CompareShapes() {};
  void greater(Sh1& s1, Sh2& s2)
  {
    if (s1.getPerimeter() > s2.getPerimeter())
      std::cout << "The first shape is greater" << std::endl;
    else
      std::cout << "The second shape is greater" << std::endl;
  };
};

int main()
{
  Circle C(2);
  Square S(2);

  CompareShapes<Circle,Square> comp;
  comp.greater(C,S);

  return 0;
}

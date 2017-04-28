// Class circle

#include <iostream>
#include <string>

#include "Circle.h"

Circle::Circle(const std::string n, double cx, double cy, double r) : Shape(n)
{
	this->cx = cx;
	this->cy = cy;
	this->r = r;
}

inline void Circle::print_name() const {
	std::cout << "Circle " << name << std::endl;
}


// Header for class Circle

#pragma once

#include <iostream>
#include <string>

#include "Shape.h"

class Circle : public Shape {
private:
	double cx, cy;
	double r;

public:
	Circle() : Shape(), cx(0.0), cy(0.0), r(0.0) {}
	virtual ~Circle() {}
	Circle(const std::string n, double cx, double cy, double r);
	virtual void print_name() const override;
};


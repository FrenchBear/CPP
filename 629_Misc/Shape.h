// Header for class Shape

#pragma once

#include <iostream>

class Shape {
public:
	std::string name;

public:
	Shape() : Shape(nullptr) {}
	virtual ~Shape() {}
	Shape(const std::string n) : name(n) {}

	virtual void print_name() const;
};

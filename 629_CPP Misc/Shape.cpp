// Class Shape

#include <iostream>
#include <string>

#include "Shape.h"

void Shape::print_name() const {
	std::cout << "Shape " << name << std::endl;
}

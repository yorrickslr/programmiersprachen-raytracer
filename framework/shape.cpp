#include "shape.hpp"
#include <iostream>

Shape::Shape() :
	name_{"default"},
	color_{100,100,100}
{}

Shape::Shape(Color const& color, std::string const& name) :
	name_{name},
	color_{color}
{}

Shape::~Shape() {
	// std::cout << "Destruction of shape" << std::endl;
}

std::string Shape::name() const {
	return name_;
}

Color Shape::color() const {
	return color_;
}

std::ostream& Shape::print(std::ostream& os) const {
	os << "name: " << name_ << "\r\n" << "color: " << color_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}

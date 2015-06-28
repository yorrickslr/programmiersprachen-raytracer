#include "shape.hpp"

Shape::Shape() :
	name_{"default"},
	color_{100,100,100}
{}

Shape::Shape(std::string const& name, Color const& color) :
	name_{name},
	color_{color}
{}

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

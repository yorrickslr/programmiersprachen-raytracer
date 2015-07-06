#include "shape.hpp"
#include <iostream>

Shape::Shape() :
	name_{"default"},
	material_{ Material{} }
{}

Shape::Shape(Material const& material, std::string const& name) :
	name_{name},
	material_{material}
{}

Shape::~Shape() {
	// std::cout << "Destruction of shape" << std::endl;
}

std::string Shape::name() const {
	return name_;
}

Material Shape::material() const {
	return material_;
}

std::ostream& Shape::print(std::ostream& os) const {
	os << "name: " << name_ << "\r\n" << "material: " << material_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}

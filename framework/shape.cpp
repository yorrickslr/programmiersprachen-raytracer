#include "shape.hpp"
#include <iostream>

Shape::Shape(Bbox const& bbox) :
	name_{"default"},
	material_{ Material{} },
	bbox_{bbox}
{}

Shape::Shape(Material const& material, std::string const& name, Bbox const& bbox) :
	name_{name},
	material_{material},
	bbox_{bbox}
{}

Shape::~Shape() {}

std::string Shape::name() const {
	return name_;
}

Material Shape::material() const {
	return material_;
}

Bbox* Shape::bbox() {
	return &bbox_;
}

std::ostream& Shape::print(std::ostream& os) const {
	os << "name: " << name_ << "\r\n" << "material: " << material_;
	return os;
}

std::ostream& operator<<(std::ostream& os, Shape const& s) {
	return s.print(os);
}



#include "shape.hpp"
#include <iostream>

Shape::Shape(Bbox const& bbox) :
	name_{"default"},
	material_{ Material{} },
	bbox_{bbox}
{
	/*std::cout << "***DEBUG*** set bbox of shape to:" << std::endl;
	glm::vec3 tmp = bbox.min;
	std::cout << "***DEBUG*** min=[" << tmp.x << "," << tmp.y << "," << tmp.z << "]" << std::endl;
	tmp = bbox.max;
	std::cout << "***DEBUG*** max=[" << tmp.x << "," << tmp.y << "," << tmp.z << "]" << std::endl;*/
}

Shape::Shape(Material const& material, std::string const& name, Bbox const& bbox) :
	name_{name},
	material_{material},
	bbox_{bbox}
{
	/*std::cout << "***DEBUG*** set bbox of shape to:" << std::endl;
	glm::vec3 tmp = bbox.min;
	std::cout << "***DEBUG*** min=[" << tmp.x << "," << tmp.y << "," << tmp.z << "]" << std::endl;
	tmp = bbox.max;
	std::cout << "***DEBUG*** max=[" << tmp.x << "," << tmp.y << "," << tmp.z << "]" << std::endl;*/
}

Shape::~Shape() {
	// std::cout << "Destruction of shape" << std::endl;
}

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



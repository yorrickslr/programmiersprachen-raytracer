#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {
public:
	double area() override;
	double volume() override;
private:
	glm::vec3 center;
	double radius;
};

#endif

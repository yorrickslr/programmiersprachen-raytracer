#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP
#include <glm/vec3.hpp>
#include "shape.hpp"

class Sphere : public Shape {
private:
	glm::vec3 center;
	double radius;
};

#endif

#ifndef BUW_HIT_HPP
#define BUW_HIT_HPP

#include <glm/vec3.hpp>
#include <ray.hpp>
#include <memory>

class Shape;

struct Hit {
	bool hit;
	float distance;
	glm::vec3 intersection;
	glm::vec3 normal;
	std::shared_ptr<Shape> object;
};

#endif

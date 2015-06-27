#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Sphere : public Shape {
public:
	Sphere(glm::vec3 const& center, double const radius);
	Sphere();
	~Sphere();
	glm::vec3 center() const;
	double radius() const;
	double area() const override;
	double volume() const override;
private:
	glm::vec3 center_;
	double radius_;
};

#endif

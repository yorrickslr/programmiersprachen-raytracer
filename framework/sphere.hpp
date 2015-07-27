#ifndef BUW_SPHERE_HPP
#define BUW_SPHERE_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "color.hpp"
#include <string>
#include "ray.hpp"

class Sphere : public Shape {
public:
	Sphere(glm::vec3 const& center, double const radius, Material const& material, std::string const& name);
	Sphere(glm::vec3 const& center, double const radius);
	Sphere();
	~Sphere();
	glm::vec3 center() const;
	double radius() const;
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
	bool intersect(Ray const& ray, float& distance) const override;
private:
	glm::vec3 center_;
	double radius_;
};

std::ostream& operator<<(std::ostream& os, Sphere const& s);

#endif

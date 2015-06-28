#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <cmath>

Sphere::Sphere(std::string const& name, glm::vec3 const& center, double const radius, Color const& color) :
	Shape{name, color},
	center_{center},
	radius_{radius}
{}

Sphere::Sphere(glm::vec3 const& center, double const radius) :
	center_{center},
	radius_{radius}
{}

Sphere::Sphere() :
	Shape{},
	center_{0.0,0.0,0.0},
	radius_{1}
{}

double Sphere::volume() const {
	return (12.56636 * std::pow(radius_,3)) / 3 ;
}

double Sphere::area() const {
	return 12.56636 * radius_ * radius_;
}

glm::vec3 Sphere::center() const {
	return center_;
}

double Sphere::radius() const {
	return radius_;
}

// MinGW does not support M_PI, 
// so I replaced it with 3.14159 and reduced the equations
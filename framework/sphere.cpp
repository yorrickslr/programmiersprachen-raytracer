#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <cmath>

Sphere::Sphere(glm::vec3 const& center, double const radius) :
	center_{center},
	radius_{radius}
{}

Sphere::Sphere() :
	center_{0.0,0.0,0.0},
	radius_{1}
{}

Sphere::~Sphere() {}

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
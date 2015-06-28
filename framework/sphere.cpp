#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <cmath>
#include "ray.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

Sphere::Sphere(glm::vec3 const& center, double const radius, Color const& color, std::string const& name) :
	Shape{color, name},
	center_{center},
	radius_{radius}
{}

Sphere::Sphere(glm::vec3 const& center, double const radius) :
	Shape{},
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

std::ostream& Sphere::print(std::ostream& os) const {
	Shape::print(os) << "center: [" << center_.x << "," << center_.y 
		<< "," << center_.z << "]\r\n" << "radius: " << radius_ << "\r\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Sphere const& s) {
	return s.print(os);
}

bool Sphere::intersect(Ray const& ray, float& distance) const {
	return glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center_, radius_, distance);
}

// MinGW does not support M_PI, 
// so I replaced it with 3.14159 and reduced the equations

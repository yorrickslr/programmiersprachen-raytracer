#define _USE_MATH_DEFINES
#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <math.h>
#include "ray.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

Sphere::Sphere(glm::vec3 const& center, double const radius, Material const& material, std::string const& name) :
	Shape{material, name, {center_-float(radius_),center_+float(radius_)}},
	center_{center},
	radius_{radius}
{
	// std::cout << "Construction of sphere" << std::endl;
	glm::vec3 min = center_-float(radius);
	std::cout << "***DEBUG*** Sphere constructor: min=[" << min.x << "," << min.y << "," << min.z << "]" << std::endl;
	glm::vec3 max = center_+float(radius);
	std::cout << "***DEBUG*** Sphere constructor: max=[" << max.x << "," << max.y << "," << max.z << "]" << std::endl;
}

Sphere::Sphere(glm::vec3 const& center, double const radius) :
	Shape{{center_-float(radius_),center_+float(radius_)}},
	center_{center},
	radius_{radius}
{
	// std::cout << "Construction of sphere" << std::endl;
}

Sphere::Sphere() :
	Shape{{{-1,-1,-1},{1,1,1}}},
	center_{0.0,0.0,0.0},
	radius_{1}
{
	// std::cout << "Construction of sphere" << std::endl;
}

Sphere::~Sphere() {
	// std::cout << "Destruction of sphere" << std::endl;
}
/*
double Sphere::volume() const {
	return (4 * M_PI * std::pow(radius_,3)) / 3 ;
}

double Sphere::area() const {
	return 4 * M_PI * radius_ * radius_;
}*/

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

Hit Sphere::intersect(Ray const& ray) {
	Hit hit;
	hit.hit = glm::intersectRaySphere(ray.origin, glm::normalize(ray.direction), center_, radius_, hit.intersection, hit.normal);
	hit.distance = glm::distance(ray.origin,hit.intersection);
	hit.object = this;
	return hit;
}

void Sphere::translate(glm::vec3 const& trans_dir) {
	glm::vec4 center_4{center_, 1.0f};

	world_transformation = glm::translate(glm::mat4(1.0f), trans_dir);

	center_4 = world_transformation * center_4;

	glm::vec3 center_trans{center_4};
	center_ = center_trans;
}

// MinGW does not support M_PI, 
// so I replaced it with 3.14159 and reduced the equations

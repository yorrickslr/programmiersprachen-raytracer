#include "box.hpp"
#include <glm/vec3.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>

Box::Box() :
	Shape{},
	min_{0,0,0},
	max_{1,1,1}
{
	std::cout << "Construction of box" << std::endl;
}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	Shape{},
	min_{
		min.x<max.x ? min.x : max.x,
		min.y<max.y ? min.y : max.y,
		min.z<max.z ? min.z : max.z
	},
	max_{
		max.x>min.x ? max.x : min.x,
		max.y>min.y ? max.y : min.y,
		max.z>min.z ? max.z : min.z
	}
{
	std::cout << "Construction of box" << std::endl;
}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Color const& color, std::string const& name) :
	Shape{color,name},
	min_{
		min.x<max.x ? min.x : max.x,
		min.y<max.y ? min.y : max.y,
		min.z<max.z ? min.z : max.z
	},
	max_{
		max.x>min.x ? max.x : min.x,
		max.y>min.y ? max.y : min.y,
		max.z>min.z ? max.z : min.z
	}
{
	std::cout << "Construction of box" << std::endl;
}

Box::~Box() {
	std::cout << "Destruction of box" << std::endl;
}

glm::vec3 Box::min() const {
	return min_;
}

glm::vec3 Box::max() const {
	return max_;
}

double Box::area() const {
	double a = max_[0] - min_[0];
	double b = max_[1] - min_[1];
	double c = max_[2] - min_[2];
	return 2 * (a * b + b * c + a * c);
}

double Box::volume() const {
	double a = max_[0] - min_[0];
	double b = max_[1] - min_[1];
	double c = max_[2] - min_[2];
	return a * b * c;
}

std::ostream& Box::print(std::ostream& os) const {
	Shape::print(os) << "min: [" << min_.x << "," << min_.y 
		<< "," << min_.z << "]\r\n" << "max: [" << max_.x 
		<< "," << max_.y << "," << max_.z << "]" << "\r\n";
	return os;
}

std::ostream& operator<<(std::ostream& os, Box const& s) {
	return s.print(os);
}

bool Box::intersect(Ray const& ray, float& distance) {
	float tx1 {(min_.x - ray.origin.x) * glm::normalize(ray.direction).x};
	float tx2 {(max_.x - ray.origin.x) * glm::normalize(ray.direction).x};
	float tmin {std::min(tx1,tx2)};
	float tmax {std::max(tx1,tx2)};
	float w {tmax - tmin};

	float ty1 {(min_.y - ray.origin.y) * glm::normalize(ray.direction).y};
	float ty2 {(max_.y - ray.origin.y) * glm::normalize(ray.direction).y};
	float tmp {abs(ty1 - ty2)};
	float h {tmp!=tmp ? 0.0 : tmax - tmin};

	float tz1 {(min_.z - ray.origin.z) * glm::normalize(ray.direction).z};
	float tz2 {(max_.z - ray.origin.z) * glm::normalize(ray.direction).z};
	tmin = std::max(tmin, std::min(tz1,tz2));
	tmax = std::min(tmax, std::max(tz1,tz2));
	tmp = abs(tz1 - tz2);
	float l {tmp!=tmp ? 0.0 : tmax - tmin};

	if(tmax >= std::max(0.0f, tmin)) {
		distance = sqrt(w * w + h * h + l * l);
		return true;
	} else {
		return false;
	}
}
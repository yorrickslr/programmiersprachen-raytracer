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
	// std::cout << "Construction of box" << std::endl;
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
	// std::cout << "Construction of box" << std::endl;
}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Material const& material, std::string const& name) :
	Shape{material,name},
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
	// std::cout << "Construction of box" << std::endl;
}

Box::~Box() {
	// std::cout << "Destruction of box" << std::endl;
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
	for(int i=0; i<3; i++) {
		float dmin{0.0}, dmax{0.0}, dtmp{0.0};
		dmin = (min_[i] - ray.origin[i]) / ray.direction[i];
		dmax = (max_[i] - ray.origin[i]) / ray.direction[i];
		dtmp = dmin < dmax ? dmin : dmax;
		glm::vec3 tmp{0.0,0.0,0.0};
		if(!std::isnan(dtmp) && !std::isinf(dtmp)) {
			tmp = {
				ray.origin.x + dtmp * ray.direction.x,
				ray.origin.y + dtmp * ray.direction.y,
				ray.origin.z + dtmp * ray.direction.z
			};
		} else {
			continue;
		}
		if(tmp.x>=min_.x && tmp.x<=max_.x &&
			tmp.y>=min_.y && tmp.y<=max_.y && 
			tmp.z>=min_.z && tmp.z<=max_.z) {
			glm::vec3 mvec{dtmp * ray.direction};
			distance = sqrt(pow(mvec.x,2) + pow(mvec.y,2) +pow(mvec.z,2));
			return true;
		}
	}
	return false;
}

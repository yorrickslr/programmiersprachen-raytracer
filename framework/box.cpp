#include "box.hpp"
#include <glm/vec3.hpp>

Box::Box() :
	Shape{},
	min_{0,0,0},
	max_{1,1,1}
{}

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
{}

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
{}

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

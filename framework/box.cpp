#include "box.hpp"
#include <glm/vec3.hpp>

Box::Box() :
	min_{0,0,0},
	max_{1,1,1}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
	min_{
		min[0]<max[0] ? min[0] : max[0],
		min[1]<max[1] ? min[1] : max[1],
		min[2]<max[2] ? min[2] : max[2]
	},
	max_{
		max[0]>min[0] ? max[0] : min [0],
		max[1]>min[1] ? max[1] : min [1],
		max[2]>min[2] ? max[2] : min [2]
	}
{}

Box::Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, Color const& color) :
	Shape{name,color},
	min_{
		min[0]<max[0] ? min[0] : max[0],
		min[1]<max[1] ? min[1] : max[1],
		min[2]<max[2] ? min[2] : max[2]
	},
	max_{
		max[0]>min[0] ? max[0] : min [0],
		max[1]>min[1] ? max[1] : min [1],
		max[2]>min[2] ? max[2] : min [2]
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
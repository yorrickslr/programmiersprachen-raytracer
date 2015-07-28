#include <triangle.hpp>
#include <math.h>


Triangle::Triangle() :
	Shape(),
	p1_{ glm::vec3{0.0,0.0,0.0} },
	p2_{ glm::vec3{0.0,0.0,0.0} },
	p3_{ glm::vec3{0.0,0.0,0.0} }{}

Triangle::Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) :
	Shape(),
	p1_{p1},
	p2_{p2},
	p3_{p3}{}

Triangle::Triangle(Material material, std::string name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3) :
	Shape(material, name),
	p1_{p1},
	p2_{p2},
	p3_{p3}{}

Triangle::~Triangle(){}


glm::vec3 Triangle::get_p1() const {
	return p1_;
}

glm::vec3 Triangle::get_p2() const {
	return p2_;
}

glm::vec3 Triangle::get_p3() const {
	return p3_;
}


double Triangle::area() const {
	double a = sqrt((p1_.x - p2_.x)*(p1_.x - p2_.x) + (p1_.y - p2_.y)*(p1_.y - p2_.y) + (p1_.z - p2_.z)*(p1_.z - p2_.z));
	double b = sqrt((p1_.x - p3_.x)*(p1_.x - p3_.x) + (p1_.y - p3_.y)*(p1_.y - p3_.y) + (p1_.z - p3_.z)*(p1_.z - p3_.z));
	double c = sqrt((p2_.x - p3_.x)*(p2_.x - p3_.x) + (p2_.y - p3_.y)*(p2_.y - p3_.y) + (p2_.z - p3_.z)*(p2_.z - p3_.z));

	double s = ((a + b + c)/2);

	return sqrt(s*(s-a)*(s-b)*(s-c)); 
}

double Triangle::volume() const {
	return 0;
}

bool Triangle::intersect(Ray const& ray, float& distance) const {
	glm::vec3 baryPosition{};
	auto a = glm::intersectRayTriangle(ray.origin, ray.direction, p1_, p2_, p3_, baryPosition);
	if(a){
		glm::vec3 cartesianPosition = ray.origin + ray.direction * baryPosition.z;
		distance = glm::distance(cartesianPosition, ray.origin);
		return distance;
	}
	return a;
}

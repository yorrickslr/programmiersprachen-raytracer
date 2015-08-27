#include <triangle.hpp>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>

Triangle::Triangle() :
	Shape(),
	p1_{ glm::vec3{0.0,0.0,0.0} },
	p2_{ glm::vec3{0.0,0.0,0.0} },
	p3_{ glm::vec3{0.0,0.0,0.0} }{}

Triangle::Triangle(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3) :
	Shape(),
	p1_{p1},
	p2_{p2},
	p3_{p3}{}

Triangle::Triangle(std::string const& name, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, Material const& material) :
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


/*double Triangle::area() const {
	double a = sqrt((p1_.x - p2_.x)*(p1_.x - p2_.x) + (p1_.y - p2_.y)*(p1_.y - p2_.y) + (p1_.z - p2_.z)*(p1_.z - p2_.z));
	double b = sqrt((p1_.x - p3_.x)*(p1_.x - p3_.x) + (p1_.y - p3_.y)*(p1_.y - p3_.y) + (p1_.z - p3_.z)*(p1_.z - p3_.z));
	double c = sqrt((p2_.x - p3_.x)*(p2_.x - p3_.x) + (p2_.y - p3_.y)*(p2_.y - p3_.y) + (p2_.z - p3_.z)*(p2_.z - p3_.z));

	double s = ((a + b + c)/2);

	return sqrt(s*(s-a)*(s-b)*(s-c)); 
}

double Triangle::volume() const {
	return 0;
}*/

float triangle_area(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3) {
	float a = sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y) + (p1.z - p2.z)*(p1.z - p2.z));
	float b = sqrt((p1.x - p3.x)*(p1.x - p3.x) + (p1.y - p3.y)*(p1.y - p3.y) + (p1.z - p3.z)*(p1.z - p3.z));
	float c = sqrt((p2.x - p3.x)*(p2.x - p3.x) + (p2.y - p3.y)*(p2.y - p3.y) + (p2.z - p3.z)*(p2.z - p3.z));

	float s = ((a + b + c)/2);

	return sqrt(s*(s-a)*(s-b)*(s-c)); 
}

Hit Triangle::intersect(Ray const& ray) {
	Hit hit;
	hit.object = shared_from_this();
	hit.normal = glm::normalize(glm::cross(p1_-p2_, p1_-p3_));
	if(glm::dot(hit.normal, ray.direction)>0) {
		hit.normal = -hit.normal;
	}
	glm::vec3 normDir = glm::normalize(ray.direction);
	hit.hit = glm::intersectLineTriangle(ray.origin, normDir, p1_, p2_, p3_, hit.intersection);
	hit.distance = (glm::dot(p1_,hit.normal) - glm::dot(hit.normal,ray.origin)) / glm::dot(normDir, hit.normal);
	hit.intersection = ray.origin + hit.distance * normDir;
	if(hit.hit && hit.distance<0) {
		hit.hit = false;
	}
	return hit;

	/*Hit hit;
	hit.object = shared_from_this();
	hit.hit = glm::intersectLineTriangle(ray.origin, glm::normalize(ray.direction), p1_, p2_, p3_, hit.intersection);
	glm::vec3 normDir = glm::normalize(ray.direction);
	hit.distance = glm::distance(ray.origin, hit.intersection);
	glm::vec3 tmp1{p1_-p2_};
	glm::vec3 tmp2{p1_-p3_};
	hit.normal = glm::normalize(glm::cross(tmp1, tmp2));
	std::cout << hit.intersection.z << std::endl;
	if(hit.intersection.z > 0) {
		hit.hit = false;
	}
	return hit;

	second try: */
	//netter versuch, funzt nur für gleiche y-werte
	/*glm::vec3 baryPosition{};
	auto a = glm::intersectRayTriangle(ray.origin, ray.direction, p1_, p2_, p3_, baryPosition);

	if(a){
		glm::vec3 cartesianPosition = ray.origin + ray.direction * baryPosition.z;
		distance = glm::distance(cartesianPosition, ray.origin);
		return distance;
	}

	return a;*/
}

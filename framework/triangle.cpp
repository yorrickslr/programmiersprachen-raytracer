#define _USE_MATH_DEFINES
#include <triangle.hpp>
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <memory>
#include <algorithm>

Bbox triangle_bbox(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3) {
	float maxX = std::max(p1.x,std::max(p2.x,p3.x));
	float maxY = std::max(p1.y,std::max(p2.y,p3.y));
	float maxZ = std::max(p1.z,std::max(p2.z,p3.z));
	float minX = std::min(p1.x,std::min(p2.x,p3.x));
	float minY = std::min(p1.y,std::min(p2.y,p3.y));
	float minZ = std::min(p1.z,std::min(p2.z,p3.z));
	return Bbox{{minX, minY, minZ},{maxX, maxY, maxZ}};
}

Triangle::Triangle() :
	Shape{{{0,0,0},{0,0,0}}},
	p1_{ glm::vec3{0.0,0.0,0.0} },
	p2_{ glm::vec3{0.0,0.0,0.0} },
	p3_{ glm::vec3{0.0,0.0,0.0} }
{}

Triangle::Triangle(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3) :
	Shape{triangle_bbox(p1,p2,p3)},
	p1_{p1},
	p2_{p2},
	p3_{p3}
{}

Triangle::Triangle(std::string const& name, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, Material const& material) :
	Shape(material, name, triangle_bbox(p1,p2,p3)),
	p1_{p1},
	p2_{p2},
	p3_{p3}
{}

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
	hit.object = this;
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


//Transformation
void Triangle::translate(glm::vec3 const& trans_dir) {
	glm::vec4 p1_4{p1_, 1.0f};
	glm::vec4 p2_4{p2_, 1.0f};
	glm::vec4 p3_4{p3_, 1.0f};

	world_transformation = glm::translate(glm::mat4(1.0f), trans_dir);

	p1_4 = world_transformation * p1_4;
	p2_4 = world_transformation * p2_4;
	p3_4 = world_transformation * p3_4;

	glm::vec3 p1_trans{p1_4};
	glm::vec3 p2_trans{p2_4};
	glm::vec3 p3_trans{p3_4};

	p1_ = p1_trans;
	p2_ = p2_trans;
	p3_ = p3_trans;
}


void Triangle::rotate(float& radiant, glm::vec3 const& axis) {
	//Preparations
	glm::vec4 p1_4{p1_, 1.0f};
	glm::vec4 p2_4{p2_, 1.0f};
	glm::vec4 p3_4{p3_, 1.0f};
 
    if(2*M_PI < radiant) {
        radiant = (radiant * M_PI)/ 180;
    }

    glm::vec3 axis_normed = glm::normalize(axis);

    //Dat Matrix O____________O
    //HOLY FUCKIN SHIT!!! WENN DAS NICHT FUNZT, RASTE ICH ABER AUS!
    //First row
    world_transformation[0][0] = pow(axis_normed.x,2)*(1 - cos(radiant))+cos(radiant);
    world_transformation[0][1] = axis_normed.x*axis_normed.y*(1 - cos(radiant))-axis_normed.z*sin(radiant);
    world_transformation[0][2] = axis_normed.x*axis_normed.z*(1 - cos(radiant))-axis_normed.y*sin(radiant);
    world_transformation[0][3] = 0;
    //Second row
    world_transformation[1][0] = axis_normed.y*axis_normed.x*(1 - cos(radiant))-axis_normed.z*sin(radiant);
    world_transformation[1][1] = pow(axis_normed.y,2)*(1 - cos(radiant))+cos(radiant);
    world_transformation[1][2] = axis_normed.y*axis_normed.z*(1 - cos(radiant))-axis_normed.x*sin(radiant);
    world_transformation[1][3] = 0;
    //Third row
    world_transformation[2][0] = axis_normed.z*axis_normed.x*(1 - cos(radiant))-axis_normed.y*sin(radiant);
    world_transformation[2][1] = axis_normed.z*axis_normed.y*(1 - cos(radiant))-axis_normed.x*sin(radiant);
    world_transformation[2][2] = pow(axis_normed.z,2)*(1 - cos(radiant))+cos(radiant);
    world_transformation[2][3] = 0;
    //Fourth row
    world_transformation[3][0] = 0;
    world_transformation[3][1] = 0;
    world_transformation[3][2] = 0;
    world_transformation[3][3] = 1;

	p1_4 = world_transformation * p1_4;
	p2_4 = world_transformation * p2_4;
	p3_4 = world_transformation * p3_4;

	glm::vec3 p1_rotate{p1_4};
	glm::vec3 p2_rotate{p2_4};
	glm::vec3 p3_rotate{p3_4};

	p1_ = p1_rotate;
	p2_ = p2_rotate;
	p3_ = p3_rotate;

}

void Triangle::scale(double& scale) {
	glm::vec4 p1_4{p1_, 1.0f};
	glm::vec4 p2_4{p2_, 1.0f};
	glm::vec4 p3_4{p3_, 1.0f};

	glm::vec3 scalierer{ scale, scale, scale };

	world_transformation = glm::scale(glm::mat4(1.0f), scalierer);

	p1_4 = world_transformation * p1_4;
	p2_4 = world_transformation * p2_4;
	p3_4 = world_transformation * p3_4;
	glm::vec3 p1_trans{p1_4};
	glm::vec3 p2_trans{p2_4};
	glm::vec3 p3_trans{p3_4};

	p1_ = p1_trans;
	p2_ = p2_trans;
	p3_ = p3_trans;

}

// Rotationsmatrix aus einer beliebigen Ursprungsgeraden
/*
    normaler vector n = {n.x, n.y, n.z}
    Winkel alpha = a* pi

    Matrix:
    n.x^2*(1 - cos{alpha}) + cos{alpha}   |   n.x*n.y*(1 - cos{alpha})-n.z sin{alpha} |   n.x*n.z*(1 - cos{alpha})+n.y*sin{alpha}
    
    n.y*n.x*(1 - cos{alpha})+n.z*sin{alpha} |   n.y^2*(1 - cos{alpha})+cos{alpha}   |   n.y*n.z*(1 - cos{alpha})-n.x*sin{alpha}
    
    n.z*n.x*(1 - cos{alpha})-n.y*sin{alpha} |   n.z*n.y*(1 - cos{alpha})+n.xcos{alpha}   |   n.z^2*(1 - cos{alpha})+cos{alpha}



*/

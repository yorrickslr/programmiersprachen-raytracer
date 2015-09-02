#define _USE_MATH_DEFINES
#include "sphere.hpp"
#include <glm/vec3.hpp>
#include <math.h>
#include "ray.hpp"
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>

Sphere::Sphere(glm::vec3 const& center, double const radius, Material const& material, std::string const& name) :
	Shape{material, name, {center-float(radius),center+float(radius)}},
	center_{center},
	radius_{radius}
{}

Sphere::Sphere(glm::vec3 const& center, double const radius) :
	Shape{{center-float(radius),center+float(radius)}},
	center_{center},
	radius_{radius}
{}

Sphere::Sphere() :
	Shape{{{-1,-1,-1},{1,1,1}}},
	center_{0.0,0.0,0.0},
	radius_{1}
{}

Sphere::~Sphere() {}

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

void Sphere::rotate(float& radiant, glm::vec3 const& axis) {
	//Preparations
	glm::vec4 center_4{center_, 1.0f};
 
    if(2*M_PI < radiant) {
        radiant = (radiant * M_PI)/ 180;
    }

    glm::vec3 axis_normed = glm::normalize(axis);

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

	center_4 = world_transformation * center_4;

	glm::vec3 center_rotate{center_4};

	center_ = center_rotate;;

}

void Sphere::scale(double& scale) {
	radius_ = radius_*scale;
}

#define _USE_MATH_DEFINES
#include <math.h>
#include "box.hpp"
#include <glm/vec3.hpp>
#include <iostream>
#include <glm/glm.hpp>
#include <algorithm>

Box::Box() :
  Shape{{{0,0,0},{1,1,1}}},
  min_{0,0,0},
  max_{1,1,1}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max) :
  min_{
    min.x<max.x ? min.x : max.x,
    min.y<max.y ? min.y : max.y,
    min.z<max.z ? min.z : max.z
  },
  max_{
    max.x>min.x ? max.x : min.x,
    max.y>min.y ? max.y : min.y,
    max.z>min.z ? max.z : min.z
  },
  Shape{{min_,max_}}
{}

Box::Box(glm::vec3 const& min, glm::vec3 const& max, Material const& material, std::string const& name) :
  Shape{material,name,{min,max}},
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

Box::~Box() {}

glm::vec3 Box::min() const {
  return min_;
}

glm::vec3 Box::max() const {
  return max_;
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

Hit Box::intersect(Ray const& ray) {
  float eps = 0.001;
  Hit xHit, yHit, zHit;
  glm::vec3 normDir = glm::normalize(ray.direction);
  float tmp, tmpX, tmpY, tmpZ, xLimit, yLimit, zLimit;

  if(max_.x < ray.origin.x) {
    xLimit = max_.x;
    xHit.normal = {1,0,0};
  } else {
    xLimit = min_.x;
    xHit.normal = {-1,0,0};
  }

  if(max_.y < ray.origin.y) {
    yLimit = max_.y;
    yHit.normal = {0,1,0};
  } else {
    yLimit = min_.y;
    yHit.normal = {0,-1,0};
  }

  if(max_.z < ray.origin.z) {
    zLimit = max_.z;
    zHit.normal = {0,0,1};
  } else {
    zLimit = min_.z;
    zHit.normal = {0,0,-1};
  }

  /* Without normals
  float xLimit = max_.x < ray.origin.x ? max_.x : min_.x;
  float yLimit = max_.y < ray.origin.y ? max_.y : min_.y;
  float zLimit = max_.z < ray.origin.z ? max_.z : min_.z;
  float tmp, tmpX, tmpY, tmpZ;
  */

  xHit.distance = (xLimit - ray.origin.x) / normDir.x;
  tmpY = ray.origin.y + xHit.distance * normDir.y;
  tmpZ = ray.origin.z + xHit.distance * normDir.z;
  xHit.intersection = {xLimit,  tmpY, tmpZ};
  xHit.hit = xHit.distance>0 && tmpY<=max_.y+eps && tmpY+eps>=min_.y && tmpZ<=max_.z+eps && tmpZ+eps>=min_.z ? true : false;

  yHit.distance = (yLimit - ray.origin.y) / normDir.y;
  tmpX = ray.origin.x + yHit.distance * normDir.x;
  tmpZ = ray.origin.z + yHit.distance * normDir.z;
  yHit.intersection = {tmpX, yLimit, tmpZ};
  yHit.hit = yHit.distance>0 && tmpX<=max_.x+eps && tmpX+eps>=min_.x && tmpZ<=max_.z+eps && tmpZ+eps>=min_.z ? true : false;

  zHit.distance = (zLimit - ray.origin.z) / normDir.z;
  tmpX = ray.origin.x + zHit.distance * normDir.x;
  tmpY = ray.origin.y + zHit.distance * normDir.y;
  zHit.intersection = {tmpX, tmpY, zLimit};
  zHit.hit = zHit.distance>0 && tmpX<=max_.x+eps && tmpX+eps>=min_.x && tmpY<=max_.y+eps && tmpY+eps>=min_.y ? true : false;

  Hit hit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
  hit = xHit.hit && xHit.distance < hit.distance ? xHit : hit;
  hit = yHit.hit && yHit.distance < hit.distance ? yHit : hit;
  hit = zHit.hit && zHit.distance < hit.distance ? zHit : hit;

  hit.object = this;
  return hit;
}

void Box::translate(glm::vec3 const& trans_dir) {
	glm::vec4 min_4{min_, 1.0f};
	glm::vec4 max_4{max_, 1.0f};

	world_transformation = glm::translate(glm::mat4(1.0f), trans_dir);

	min_4 = world_transformation * min_4;
	max_4 = world_transformation * max_4;

	glm::vec3 min_trans{min_4};
	glm::vec3 max_trans{max_4};

	min_ = min_trans;
	max_ = max_trans;
}

void Box::rotate(float& radiant, glm::vec3 const& axis) {
	//Preparations
	glm::vec4 min_4{min_, 1.0f};
	glm::vec4 max_4{max_, 1.0f};
 
    if(2*M_PI < radiant) {
        radiant = (radiant * M_PI)/ 180;
    }

    glm::vec3 axis_normed = glm::normalize(axis);

	world_transformation = glm::rotate(glm::mat4(1.f), radiant, axis);

	min_4 = world_transformation * min_4;
	max_4 = world_transformation * max_4;

	glm::vec3 min_rotate{min_4};
	glm::vec3 max_rotate{max_4};

	min_ = min_rotate;
	max_ = max_rotate;

}

void Box::scale(double& scale) {
	glm::vec4 min_4{min_, 1.0f};
	glm::vec4 max_4{max_, 1.0f};

	glm::vec3 scalierer{scale, scale, scale};

	world_transformation = glm::scale(glm::mat4(1.f), scalierer);

	min_4 = world_transformation * min_4;
	max_4 = world_transformation * max_4;

	glm::vec3 min_trans{min_4};
	glm::vec3 max_trans{max_4};

	min_ = min_trans;
	max_ = max_trans;
}

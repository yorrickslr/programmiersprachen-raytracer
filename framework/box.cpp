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
{
  // std::cout << "Construction of box" << std::endl;
}

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

/*double Box::area() const {
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
*/
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
// also renders in front if behind camera
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

/* ### Second try, no intersection points are correct
  Hit min, max;
  min.object = shared_from_this();
  max.object = shared_from_this();
  glm::vec3 invDirection{ (1 / ray.direction.x), (1 / ray.direction.y), (1 / ray.direction.z) };
  double t1 = (min_[0] - ray.origin[0])*invDirection[0];
  double t2 = (max_[0] - ray.origin[0])*invDirection[0];

  double tmin = std::min(t1, t2);
  double tmax = std::max(t1, t2);
  
  min.intersection.x = tmin;
  max.intersection.x = tmax;
  for (int i = 1; i < 3; ++i) {
    t1 = (min_[i] - ray.origin[i])*invDirection[i];
    t2 = (max_[i] - ray.origin[i])*invDirection[i];

    tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
    tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));

    min.intersection[i] = tmin;
    max.intersection[i] = tmax;
  }

  if(tmax > std::max(tmin, 0.0)) {
    max.distance = glm::distance(max.intersection, ray.origin);
    min.distance = glm::distance(min.intersection, ray.origin);

    if(max.distance > min.distance) {
      min.hit = true;
      return min;
    }

    max.hit = true;
    return max;
  }
  return Hit{};
*/
  

  /*for(int i=0; i<3; i++) {
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
  return false;*/
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

    //Dat Matrix O____________O
    //HOLY FUCKIN SHIT!!! WENN DAS NICHT FUNZT, RASTE ICH ABER AUS!
    //First row
    /*world_transformation[0][0] = pow(axis_normed.x,2)*(1 - cos(radiant))+cos(radiant);
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

    std::cout << "***DEBUG*** Min before rotation: " << std::endl;
	std::cout << min_4.x << " | " << min_4.y << " | " << min_4.z << std::endl;
	std::cout << "***DEBUG*** Max before rotation: " << std::endl;
	std::cout << max_4.x << " | " << max_4.y << " | " << max_4.z << std::endl;

	min_4 = world_transformation * min_4;
	max_4 = world_transformation * max_4;

	std::cout << "***DEBUG*** Min after rotation: " << std::endl;
	std::cout << min_4.x << " | " << min_4.y << " | " << min_4.z << std::endl;
	std::cout << "***DEBUG*** Max after rotation: " << std::endl;
	std::cout << max_4.x << " | " << max_4.y << " | " << max_4.z << std::endl;

	glm::vec3 min_rotate{min_4};
	glm::vec3 max_rotate{max_4};*/

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

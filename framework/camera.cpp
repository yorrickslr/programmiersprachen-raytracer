#include <camera.hpp>
#include <cmath>
#include <glm/glm.hpp>
#include <iostream>

Camera::Camera():
	name_{"Camera_Obscura"},
	eye_{ 0.0,0.0,0.0 },
	direction_{ 0,0,-1 },
	up_{ 0.0,0.0,0.0 },
	fovX_{ 45.0 }
{}

Camera::Camera(glm::vec3 const& pos) :
	name_{"Camera_Obscura"},
	eye_{ pos },
	direction_{0,0,-1},
	up_{ 0.0,0.0,0.0 },
	fovX_{45.0} 
{}

Camera::Camera(std::string const& name, glm::vec3 const& pos, glm::vec3 const& dir, glm::vec3 const& up, float& fov) : 
	name_{ name },
	eye_{ pos },
	direction_{ dir },
	up_{ up },
	fovX_{ fov }
{}

Camera::Camera(Camera const& cam) : 
	name_{ cam.name_ },
	eye_{ cam.eye_ },
	direction_{ cam.direction_ },
	up_{ cam.up_ },
	fovX_{ cam.fovX_ }
{}

Camera::~Camera(){}


Camera& Camera::operator=(Camera& tmp) {
	name_ = tmp.name_;
	eye_ = tmp.eye_;
	direction_ = tmp.direction_;
	up_ = tmp.up_;
	fovX_ = tmp.fovX_;
	return *this;
}


std::string Camera::get_name() const {
	return name_;
}

glm::vec3 Camera::get_position() const {
	return eye_;
}

glm::vec3 Camera::get_direction() const {
	return direction_;
}

glm::vec3 Camera::get_up() const {
	return up_;
}

float Camera::get_fov_x() const {
	return fovX_;
}

void Camera::setResolution(int width, int height) {
	width_ = width;
	height_ = height;
}

unsigned Camera::width() const {
	return width_;
}

unsigned Camera::height() const {
	return height_;
}

Ray Camera::eyeRay(float x, float y) const {
	float tmpx =(2*x*float(width_)/float(height_))/float(width_) - float(width_)/float(height_);
 	//float tmpx = 2*x/float(width_) - 1;
 	float tmpy = 2*y/float(height_) - 1;
	float tmpz = (fovX_-180)/fovX_;
	glm::vec4 rayDir{tmpx, tmpy, tmpz, 0};

	glm::vec3 n = glm::normalize(direction_);
	glm::vec3 u = glm::normalize(glm::cross(direction_,up_));
	glm::vec3 v = glm::normalize(glm::cross(u,n));
	glm::mat4 c{
		u.x, -v.x, n.x, eye_.x,
		u.y, -v.y, n.y, eye_.y,
		u.z, -v.z, n.z, eye_.z,
		0.f, 0.f, 0.f, 1.f
	};
	glm::vec4 translatedRay{c * rayDir};
	return Ray{eye_, {translatedRay[0],translatedRay[1],translatedRay[2]}};
}

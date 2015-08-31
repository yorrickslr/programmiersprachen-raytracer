#include <camera.hpp>
#include <cmath>
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
	/* yorrick'scher Algorithmus - funst nicht:
	glm::vec3 origin{0,0,0};
	glm::vec3 direction{0,0,0};
	float fovY = fovX_ * width_ / height_;
	direction.x = 0.5 - float(x) / width_;
	direction.y = 0.5 - float(y) / height_;//(fovY * (90 - fovY)) / (direction.z * ;
	direction.z = -((90 - fovX_) * width_) / (2 * fovX_);
	std::cout << "***DEBUG*** " << "x=" << direction.x << " y=" << direction.y << " z=" << direction.z << std::endl;
	return Ray{origin, direction};
	*/

	/* Algorithm powered by internet
	Ray eyeRay;
	float fovX = fovX_;
	float fovY = (width_ / height_) * fovX;
	float dirX = ((2 * float(x) - width_) / (width_)) * std::tan(fovX);
	float dirY = ((2 * float(y) - height_) / (height_)) * std::tan(fovY);
	eyeRay.direction = glm::vec3{dirX, -1.0, dirY};
	eyeRay.origin = eye_;
	return eyeRay;*/

	float tmpx =(2*x*float(width_)/float(height_))/float(width_) - float(width_)/float(height_);
	//float tmpx = 2*x/float(width_) - 1;
	float tmpy = 2*y/float(height_) - 1;
	float tmpz = (fovX_-90)/fovX_;
	return Ray{eye_, {tmpx, tmpy, tmpz}};
}
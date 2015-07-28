#include <camera.hpp>

Camera::Camera():
	name_{"Camera_Obscura"},
	eye_{ 0.0,0.0,0.0 },
	direction_{ 0,-1,0 },
	up_{ 0.0,0.0,0.0 },
	fovX_{ 0.0 }
{}

Camera::Camera(glm::vec3 const& pos) :
	name_{"Camera_Obscura"},
	eye_{ pos },
	direction_{0,-1,0},
	up_{ 0.0,0.0,0.0 },
	fovX_{0.0} 
{}

Camera::Camera(std::string const& name, glm::vec3 const& pos, glm::vec3 const& dir, float& fov, glm::vec3 const& up) : 
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


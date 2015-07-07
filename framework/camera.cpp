#include <camera.hpp>

Camera::Camera():
	cam_position_{ glm::vec3{0.0,0.0,0.0} }{}

Camera::Camera(glm::vec3 pos) :
	cam_position_{ pos }{}

Camera::~Camera(){}


glm::vec3 Light::get_position() const {
	return cam_position_;
}

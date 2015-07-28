#include <camera.hpp>

Camera::Camera():
	name{"Camera_Obscura"},
	eye{ glm::vec3{0.0,0.0,0.0} },
	direction{{0,-1,0}},
	fov_x{0.0},
	up{{0.0,0.0,0.0}} {}

Camera::Camera(glm::vec3 pos) :
	name{"Camera_Obscura"},
	eye{ pos },
	direction{{0,-1,0}},
	fov_x{0.0},
	up{{0.0,0.0,0.0}} {}

Camera::Camera(String const& name, glm::vec3 const& pos, glm::vec3 const& dir, float& fov_x, glm::vec3 const& up) : 
	name{ name },
	eye{ pos },
	direction{ dir },
	fov_x{ fov_x },
	up{ up }{}

Camera::Camera(Camera const& cam) : 
	name{ cam.name },
	eye{ cam.eye },
	direction{ cam.direction },
	fov_x{ cam.fov_x },
	up{{ cam.up }{}

Camera::~Camera(){}


String get_name() const {
	return name;
}

glm::vec3 get_position() const {
	return eye;
}

glm::vec3 get_direction() const {
	return direction;
}

float get_fov_x() const {
	return fov_x;
}

glm::vec3 get_up() const {
	return up;
}


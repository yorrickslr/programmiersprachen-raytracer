#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>

class Camera{
	Camera();
	Camera(glm::vec3 pos);
	~Camera();

	glm::vec3 get_position() const;
private:
	glm::vec3 cam_position_;
};

#endif

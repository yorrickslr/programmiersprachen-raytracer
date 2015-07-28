#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>

class Camera{
public:
	Camera();
	Camera(glm::vec3 const& pos);
	Camera(std::string const& name, glm::vec3 const& eye, glm::vec3 const& direction, float& fov_x, glm::vec3 const& up);
	Camera(Camera const& cam);
	~Camera();

	std::string get_name() const;
	glm::vec3 get_position() const;
	glm::vec3 get_direction() const;
	float get_fov_x() const;
	glm::vec3 get_up() const;

private:
	std::string name;
	glm::vec3 eye;
	glm::vec3 direction;
	float fov_x;
	glm::vec3 up;

};

#endif

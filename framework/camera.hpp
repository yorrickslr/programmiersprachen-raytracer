#ifndef BUW_CAMERA_HPP
#define BUW_CAMERA_HPP
#include <glm/vec3.hpp>
#include <string>
#include <ray.hpp>

class Camera{
public:
	Camera();
	Camera(glm::vec3 const& pos);
	Camera(std::string const& name, glm::vec3 const& eye, glm::vec3 const& direction, glm::vec3 const& up, float& fov);
	Camera(Camera const& cam);
	~Camera();

	Camera& operator=(Camera& tmp);

	std::string get_name() const;
	glm::vec3 get_position() const;
	glm::vec3 get_direction() const;
	float get_fov_x() const;
	glm::vec3 get_up() const;
	Ray eyeRay(int x, int y) const;
	void setResolution(int width, int height);

private:
	std::string name_;
	glm::vec3 eye_;
	glm::vec3 direction_;
	glm::vec3 up_;
	float fovX_;
	int width_;
	int height_;
};

#endif

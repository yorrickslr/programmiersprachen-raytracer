#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP
#include <glm/vec3.hpp>
#include <color.hpp>

class Light {
public:
	Light();
	Light(glm::vec3 pos);
	Light(Color intensity);
	Light(glm::vec3 pos, Color intensity);
	~Light();

	glm::vec3 get_position() const;
	Color get_intensity() const;

private:
	glm::vec3 light_position_;
	Color intensity_;
};


#endif

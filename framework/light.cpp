#include <light.hpp>

Light::Light() :
	name_{"default"},
	lightPosition_{ glm::vec3{0.0,0.0,0.0} },
	ld_{ Color{0.0,0.0,0.0} }
{}

Light::Light(std::string const& name, glm::vec3 const& pos, Color const& ld) :
	name_{ name },
	lightPosition_{ pos },
	ld_{ ld }
{}

Light::~Light(){}

glm::vec3 Light::get_position() const {
	return lightPosition_;
}

Color Light::get_ld() const {
	return ld_;
}

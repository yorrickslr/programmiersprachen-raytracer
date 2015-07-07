#include <light.hpp>

Light::Light() :
	light_position_{ glm::vec3{0.0,0.0,0.0} },
	intensity_{ Color{0.0,0.0,0.0} } {}

Light::Light(glm::vec3 pos) : 
	light_position_{ pos },
	intensity_{ Color{0.0,0.0,0.0} } {}

Light::Light(Color intensity) :
	light_position_{ glm::vec3{0.0,0.0,0.0} },
	intensity_{ intensity } {}

Light::Light(glm::vec3 pos, Color intensity) :
	light_position_{ pos },
	intensity_{ intensity } {}

Light::~Light(){}

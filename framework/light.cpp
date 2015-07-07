#include <light.hpp>

Light::Light() :
	position_{ glm::vec{0.0,0.0,0.0} },
	intensity_{ Color{0.0,0.0,0.0} } {}

Light::Light(glm::vec3 pos) : 
	position_{ pos },
	intensity_{ Color{0.0,0.0,0.0} } {}

Light::Light(Color intensity) :
	position_{ glm::vec{0.0,0.0,0.0} },
	intensity_{ intensity } {}

Light::Light(glm::vec3 pos, Color intensity) :
	position_{ pos },
	intensity_{ intensity } {}

Light::~Light(){}

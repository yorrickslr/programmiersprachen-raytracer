#ifndef BUW_LIGHT_HPP
#define BUW_LIGHT_HPP
#include <glm/vec3.hpp>
#include <color.hpp>
#include <string>

class Light {
public:
	Light();
/*	Light(glm::vec3 const& pos);
	Light(Color const& la, Color const& ld);*/
	Light(std::string const& name, glm::vec3 const& pos, /*Color const& la,*/ Color const& ld);
	~Light();

	std::string get_name() const;
	glm::vec3 get_position() const;
	/*Color get_la() const;*/
	Color get_ld() const;

private:
	std::string name_;
	glm::vec3 lightPosition_;
	/*Color la_; //ambient */
	Color ld_; //diffuse
};


#endif

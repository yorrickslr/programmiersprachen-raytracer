#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>

class Box : public Shape {
public:
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(std::string const& name, glm::vec3 const& min, glm::vec3 const& max, Color const& color);
	glm::vec3 min() const;
	glm::vec3 max() const;
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
private:
	glm::vec3 min_;
	glm::vec3 max_;
};

std::ostream& operator<<(std::ostream& os, Box const& s);

#endif

#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP
#include <shape.hpp>
#include <glm/vec3.hpp>
#include <hit.hpp>

class Triangle : public Shape {
public:
	Triangle();
	Triangle(glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3);
	Triangle(std::string const& name, glm::vec3 const& p1, glm::vec3 const& p2, glm::vec3 const& p3, Material const& material);
	~Triangle();

	glm::vec3 get_p1() const;
	glm::vec3 get_p2() const;
	glm::vec3 get_p3() const;

	double area() const override;
	double volume() const override;
	Hit intersect(Ray const& ray) override;
private:
	glm::vec3 p1_;
	glm::vec3 p2_;
	glm::vec3 p3_;
};

#endif

#ifndef BUW_TRIANGLE_HPP
#define BUW_TRIANGLE_HPP
#include <shape.hpp>
#include <glm/vec3.hpp>

class Triangle : public Shape {
public:
	Triangle();
	Triangle(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	Triangle(Material material, std::string name, glm::vec3 p1, glm::vec3 p2, glm::vec3 p3);
	~Triangle();

	glm::vec3 get_p1() const;
	glm::vec3 get_p2() const;
	glm::vec3 get_p3() const;

	/*virtual*/ double area() const override;
	/*virtual*/ double volume() const override;
private:
	glm::vec3 p1_;
	glm::vec3 p2_;
	glm::vec3 p3_;
};

#endif

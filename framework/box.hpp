#ifndef BUW_BOX_HPP
#define BUW_BOX_HPP

#include "shape.hpp"
#include <glm/vec3.hpp>
#include "ray.hpp"
#include <hit.hpp>

class Box : public Shape {
public:
	Box();
	Box(glm::vec3 const& min, glm::vec3 const& max);
	Box(glm::vec3 const& min, glm::vec3 const& max, Material const& material, std::string const& name);
	~Box();
	glm::vec3 min() const;
	glm::vec3 max() const;
	std::ostream& print(std::ostream& os) const override;
	Hit intersect(Ray const& ray) override;
	void translate(glm::vec3 const& trans_dir) override;
	void rotate(float& radiant, glm::vec3 const& axis) override;
	void scale(double& scale) override;
private:
	glm::vec3 min_;
	glm::vec3 max_;

	glm::mat4 world_transformation;
	glm::mat4 world_transformation_inv;
};

std::ostream& operator<<(std::ostream& os, Box const& s);

#endif

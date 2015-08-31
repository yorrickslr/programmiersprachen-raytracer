#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ray.hpp>
#include <material.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <hit.hpp>
#include <bbox.hpp>

class Shape { //: public std::enable_shared_from_this<Shape> { //umstellen von shared ptr auf raw ptr
public:
	~Shape();
	/*virtual double area() const = 0;
	virtual double volume() const = 0;*/
	std::string name() const;
	Material material() const;
	Bbox* bbox();
	virtual std::ostream& print(std::ostream& os) const;
	virtual Hit intersect(Ray const& ray) = 0;
	// virtual void add(std::shared_ptr<Shape> const& composite) = 0;
	virtual void translate(glm::vec3 const& trans_dir) = 0;
	virtual void rotate(float& radiant, glm::vec3 const& axis) = 0;
	virtual void scale(double& scale) = 0;
protected:
	Shape(Bbox const& bbox);
	Shape(Material const& material, std::string const& name, Bbox const& bbox);
private:
	Material material_;
	std::string name_;
	Bbox bbox_;
	glm::mat4 world_transformation;
	glm::mat4 world_transformation_inv;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif

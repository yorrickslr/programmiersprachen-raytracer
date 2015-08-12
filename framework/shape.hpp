#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <string>
#include "color.hpp"
#include <ray.hpp>
#include <material.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <glm/vec3.hpp>
#include <memory>
#include <hit.hpp>


class Shape : public std::enable_shared_from_this<Shape> {
public:
	~Shape();
	virtual double area() const = 0;
	virtual double volume() const = 0;
	std::string name() const;
	Material material() const;
	virtual std::ostream& print(std::ostream& os) const;
	virtual Hit intersect(Ray const& ray) = 0;
protected:
	Shape();
	Shape(Material const& material, std::string const& name);
private:
	Material material_;
	std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif

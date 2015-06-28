#ifndef BUW_SHAPE_HPP
#define BUW_SHAPE_HPP

#include <string>
#include "color.hpp"

class Shape {
public:
	Shape();
	Shape(std::string const& name, Color const& color);
	virtual double area() const = 0;
	virtual double volume() const = 0;
	virtual std::string name() const;
	virtual Color color() const;
private:
	Color color_;
	std::string name_;
};

#endif

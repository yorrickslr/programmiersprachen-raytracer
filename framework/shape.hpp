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
	std::string name() const;
	Color color() const;
	virtual std::ostream& print(std::ostream& os) const;
private:
	Color color_;
	std::string name_;
};

std::ostream& operator<<(std::ostream& os, Shape const& s);

#endif

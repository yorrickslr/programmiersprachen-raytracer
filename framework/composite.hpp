#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include <shape.hpp>
#include <memory>
#include <map>

class Composite : public Shape {
public:
	Composite();
	Composite(std::string const& name);
	/*
	double area() const override;
	double volume() const override;*/
	std::ostream& print(std::ostream& os) const override;
	Hit intersect(Ray const& ray) override;

	void add(std::shared_ptr<Shape>& shape);
	void remove(std::string const& name);
	std::map<std::string, std::shared_ptr<Shape>> get_children();

private:
	std::map<std::string,std::shared_ptr<Shape>> shapes_;
};

#endif

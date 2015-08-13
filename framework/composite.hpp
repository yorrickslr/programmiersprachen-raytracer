#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include <shape.hpp>
#include <memory>
#include <map>

class Composite : public Shape {
public:
	typedef std::map<std::string, std::shared_ptr<Shape>> map;
	Composite();
	Composite(std::string const& name);
	
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
	Hit intersect(Ray const& ray) override;

	void add(std::shared_ptr<Shape> const& shape);
	map get_children() const;

private:
	std::string name_;
	// typedef std::map<std::shared_ptr<Shape>>::iterator mapIter;
	std::map<std::string, std::shared_ptr<Shape>> shapes;
};


#endif


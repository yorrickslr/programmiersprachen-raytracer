#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include <shape.hpp>
#include <memory>
#include <map>

class Composite : public Shape {
public:
	Composite(std::string const& name);
	
	double area() const override;
	double volume() const override;
	std::ostream& print(std::ostream& os) const override;
	bool intersect(Ray const& ray, float& distance) const override;

	void add(Shape& shape);
	void remove(Shape& shape);

private:
	std::string name_;
	typedef std::vector<std::shared_ptr<Shape>>::iterator vecIter;
	std::vector<std::shared_ptr<Shape>> children_;
};


#endif


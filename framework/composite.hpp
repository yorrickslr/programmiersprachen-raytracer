#ifndef BUW_COMPOSITE_HPP
#define BUW_COMPOSITE_HPP
#include <shape.hpp>
#include <memory>
#include <map>
#include <box.hpp>

class Composite : public Shape {
public:
	Composite();
	Composite(std::string const& name);
	Composite(std::string const& name, Box const& bounds);
	std::ostream& print(std::ostream& os) const override;
	Hit intersect(Ray const& ray) override;

	void add(std::shared_ptr<Shape>& shape);
	void remove(std::string const& name);
	std::map<std::string, std::shared_ptr<Shape>> get_children();
	
	void translate(glm::vec3 const& trans_dir) override;
	void rotate(float& radiant, glm::vec3 const& axis) override;
	void scale(double& scale) override;

private:
	std::map<std::string,std::shared_ptr<Shape>> shapes_;
};

#endif

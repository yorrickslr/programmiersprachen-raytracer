#include <composite.hpp>

Composite::Composite() :
	name_{"Default"},
	shapes{}
{}


Composite::Composite(std::string const& name) :
	name_{ name },
	shapes{}
{}


double Composite::area() const {
	float sum = 0;
	for(auto element : shapes) {
		sum += element.second->area();
	}
	return sum;
}

double Composite::volume() const {
	float sum = 0;
	for(auto element : shapes) {
		sum += element.second->volume();
	}
	return sum;
}

std::ostream& Composite::print(std::ostream& os) const {
	for(auto element : shapes) {
		element.second->print(os);
	}
	return os;
}

Hit Composite::intersect(Ray const& ray) {
	Hit hit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
	for(auto element : shapes) {
		Hit tmp = element.second->intersect(ray);
		if(tmp.hit && tmp.distance<=hit.distance) {
			hit = tmp;
		}
	}
	return hit;
}


void Composite::add(std::shared_ptr<Shape> const& shape) {
	shapes.insert(shapes.end(),std::pair<std::string,std::shared_ptr<Shape>>(shape->name(), shape));
}

std::map<std::string, std::shared_ptr<Shape>> Composite::get_children() const {
	return shapes;
}

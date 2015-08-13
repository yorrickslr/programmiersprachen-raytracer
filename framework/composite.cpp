#include <composite.hpp>

Composite::Composite(std::string name) :
	name_{ name },
	children_{}
{}


double Composite::area() {
	float sum = 0;
	for(auto element : children_) {
		sum += element->area();
	}
	return sum;
}

double Composite::volume() {
	float sum = 0;
	for(auto element : children_) {
		sum += element->volume();
	}
	return sum;
}

std::ostream& Composite::print(std::ostream& os) {
	for(auto element : children_) {
		element->print(os);
	}
	return os;
}

Hit Composite::intersect(Ray const& ray) {
	Hit hit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
	for(auto element : children_) {
		Hit tmp = element->intersect(ray);
		if(tmp.hit && tmp.distance<=hit.distance) {
			hit = tmp;
		}
	}
	return hit;
}


void Composite::add(Shape& shape) {
	children_.insert(shape);
}

void Composite::remove(mapIter element) {
	children_.erase(element);
}

#include <composite.hpp>
#include <sphere.hpp>
#include <box.hpp>
#include <triangle.hpp>
#include <shape.hpp>

Composite::Composite() :
	Shape{{{INFINITY,INFINITY,INFINITY},{-INFINITY,-INFINITY,-INFINITY}}},
	shapes_{}
{}


Composite::Composite(std::string const& name) :
	Shape{Material{}, name, {{INFINITY,INFINITY,INFINITY},{-INFINITY,-INFINITY,-INFINITY}}},
	shapes_{}
{}

Composite::Composite(std::string const& name, Box const& bounds) :
	Shape{Material{}, name, {{INFINITY,INFINITY,INFINITY},{-INFINITY,-INFINITY,-INFINITY}}},
	shapes_{}
{}

std::ostream& Composite::print(std::ostream& os) const {
	for(auto element : shapes_) {
		element.second->print(os);
	}
	return os;
}

Hit Composite::intersect(Ray const& ray) {
	Hit hit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
	if(!bbox()->intersect(ray)) {
		return hit;
	}
	for(auto element : shapes_) {
		Hit tmp = element.second->intersect(ray);
		if(tmp.hit && tmp.distance<=hit.distance) {
			hit = tmp;
		}
	}
	return hit;
}

void Composite::add(std::shared_ptr<Shape>& shape) {
	bbox()->add(*(shape->bbox()));
	shapes_.insert(shapes_.begin(),std::pair<std::string,std::shared_ptr<Shape>>(shape->name(),shape));
}

void Composite::remove(std::string const& name) {
	shapes_.erase(name);
	bbox()->min = {INFINITY,INFINITY,INFINITY};
	bbox()->max = {-INFINITY,-INFINITY,-INFINITY};
	for(auto element : shapes_) {
		bbox()->add(*(element.second->bbox()));
	}
}

std::map<std::string, std::shared_ptr<Shape>> Composite::get_children() {
	return shapes_;
}


void Composite::translate(glm::vec3 const& trans_dir) {
	for(auto element : shapes_) {
		element.second->translate(trans_dir);
	}

}

void Composite::rotate(float& radiant, glm::vec3 const& axis) {
	for(auto element : shapes_) {
		element.second->rotate(radiant, axis);
	}
}

void Composite::scale(double& scale) {
	for(auto element : shapes_) {
		element.second->scale(scale);
	}
}


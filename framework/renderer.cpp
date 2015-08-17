// -----------------------------------------------------------------------------
// Copyright  : (C) 2014 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#include "renderer.hpp"
#include <sphere.hpp>
#include <triangle.hpp>
#include <glm/glm.hpp>

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
	: width_(w)
	, height_(h)
	, colorbuffer_(w*h, Color(0.0, 0.0, 0.0))
	, filename_(file)
	, ppm_(width_, height_)
{}

void Renderer::render(Scene& scene)
{
	const std::size_t checkersize = 10;
	for (unsigned y = 0; y < height_; ++y) {
		for (unsigned x = 0; x < width_; ++x) {
			Pixel p(x,y);
			if ( ((x/checkersize)%2) != ((y/checkersize)%2)) {
				p.color = Color(0.9, 0.9, 0.9);
			} else {
				p.color = Color(0.8, 0.8, 0.8);
			}
			p.color = raytrace(scene.camera.eyeRay(x,y), scene);
			write(p);
		}
	}
	ppm_.save(filename_);
}

void Renderer::write(Pixel const& p)
{
	// flip pixels, because of opengl glDrawPixels
	size_t buf_pos = (width_*p.y + p.x);
	if (buf_pos >= colorbuffer_.size() || (int)buf_pos < 0) {
		std::cerr << "Fatal Error Renderer::write(Pixel p) : "
			<< "pixel out of ppm_ : "
			<< (int)p.x << "," << (int)p.y
			<< std::endl;
	} else {
		colorbuffer_[buf_pos] = p.color;
	}

	ppm_.write(p);
}

Color Renderer::raytrace(Ray const& ray, Scene scene) const {
  scene.ambient_light = {100,100,100};
	float distance{INFINITY};
	/*scene.shapes.insert(std::pair<std::string,std::shared_ptr<Shape>>("testri",std::make_shared<Triangle>(Triangle{scene.materials["blue"], "testri", {-1,-2,-1}, {1,-2,-1}, {0,-2,1}})));*/
	Hit minHit{false, INFINITY, {INFINITY, INFINITY, INFINITY}, {0,0,0}, nullptr};
	for(auto element : scene.composite->get_children()) {
		Hit hit = element.second->intersect(ray);
		if(hit.distance < minHit.distance && hit.hit) {
			minHit = hit;
		}
		/*if(hit.hit) {
			for(auto element : scene.lights) {
			}
			std::cout << hit.distance << std::endl;
			return element.second->material().get_ka();
		}*/
	}
	Color color = scene.ambient_light;
	/*if(minHit.hit) {
		Light debugLight{"debug", {0,0,0}, {255,255,255}, {100,100,100}}; //total fail as of color between 0 and 1
		float deg = glm::dot(glm::normalize(ray.direction),glm::normalize(debugLight.get_position() - minHit.intersection));
    float red = (*minHit.object).material().get_kd().r * debugLight.get_ld().r * deg;
		float green = (*minHit.object).material().get_kd().g * debugLight.get_ld().g * deg;
		float blue = (*minHit.object).material().get_kd().b * debugLight.get_ld().b * deg;
		return Color(red, green, blue);
	}

	return color;*/
  if(minHit.hit) {
    return Color{1,1,1};
  }
  return Color{0,0,0};
}

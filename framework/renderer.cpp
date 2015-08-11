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
  float distance{INFINITY};
  Color color;
  /*scene.shapes.insert(std::pair<std::string,std::shared_ptr<Shape>>("testri",std::make_shared<Triangle>(Triangle{scene.materials["blue"], "testri", {-1,-2,-1}, {1,-2,-1}, {0,-2,1}})));*/
  Hit minHit;
  for(auto element : scene.shapes) {
    Hit hit = element.second->intersect(ray);
    if(hit.distance < minHit.distance) {
      minHit = hit;
    }
    /*if(hit.hit) {
      for(auto element : scene.lights) {
      }
      std::cout << hit.distance << std::endl;
      return element.second->material().get_ka();
    }*/
  }
  if(minHit.hit) {
    std::cout << "Core dump? Area=" << minHit.object->area() << std::endl;
    return Color(0,0,0); //(*minHit.object).material().get_ka();
  }
  return scene.ambient_light;
  Sphere kugel{{0,-10,0},0.01};
  if(kugel.intersect(ray).hit) {
    return Color(0,0,0);
  }
  return Color(1,1,1);
}

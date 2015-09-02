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
#include <cmath>

Renderer::Renderer(Scene const& scene) :
  width_{0},
  height_{0},
  colorbuffer_{scene.camera->width()*scene.camera->height(), Color(0.0, 0.0, 0.0)},
  ppm_{scene.camera->width(),scene.camera->height(),scene.filename}
{}

Color Renderer::shade(Ray const& ray, Hit const& hit, Scene const& scene, unsigned depth) const {
  Color color{0,0,0};
  if (depth > 0) {
    Material mat = hit.object->material();
    float red{0}, green{0}, blue{0};
    for(auto light : scene.lights) {
      glm::vec3 toLight = glm::normalize(light.second.get_position() - hit.intersection);
      glm::vec3 epsIntersect = hit.intersection + 0.001f * glm::normalize(hit.normal);
      float dot = glm::dot(glm::normalize(hit.normal),toLight);
      Hit shadowHit = scene.composite->intersect(Ray{epsIntersect, toLight});
      if(!shadowHit.hit) {
        float tmpRed = mat.get_kd().r * light.second.get_ld().r * dot;
        float tmpGreen = mat.get_kd().g * light.second.get_ld().g * dot;
        float tmpBlue = mat.get_kd().b * light.second.get_ld().b * dot;
        red += tmpRed>0 ? tmpRed : 0;
        green += tmpGreen>0 ? tmpGreen : 0;
        blue += tmpBlue>0 ? tmpBlue : 0;
      }
    }
    red += mat.get_ka().r * scene.ambient_light.r;
    green += mat.get_ka().g * scene.ambient_light.g;
    blue += mat.get_ka().b * scene.ambient_light.b;

    color = Color{red,green,blue};

    /*if(mat.get_m()==1.0f) {
      std::cout << "reflection" << std::endl;
      glm::vec3 tmp = glm::reflect(glm::normalize(ray.direction),hit.normal);
      color += raytrace({hit.intersection,tmp}, scene, depth-1);
    }*/
  }
  return color;
}

void Renderer::render(Scene& scene, unsigned depth)
{
  height_ = scene.camera->height();
  width_ = scene.camera->width();
  glm::vec3 dbg_min = scene.composite->bbox()->min;
  glm::vec3 dbg_max = scene.composite->bbox()->max;
  std::cout << "Starting..." << std::endl;
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p{x,y};
      Color c1, c2, c3, c4;
      c1 = raytrace(scene.camera->eyeRay(x,y), scene, depth);
      c2 = raytrace(scene.camera->eyeRay(x,y+.5), scene, depth);
      c3 = raytrace(scene.camera->eyeRay(x+.5,y), scene, depth);
      c4 = raytrace(scene.camera->eyeRay(x+.5,y+.5), scene, depth);
      p.color.r = (c1.r + c2.r + c3.r + c4.r) / 4;
      p.color.g = (c1.g + c2.g + c3.g + c4.g) / 4;
      p.color.b = (c1.b + c2.b + c3.b + c4.b) / 4;
      write(p);
    }
  }
  ppm_.save(scene.filename);
  std::cout << "Finished!" << std::endl;
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

Color Renderer::raytrace(Ray const& ray, Scene const& scene, unsigned depth) const {
  float distance{INFINITY};
  Hit minHit = scene.composite->intersect(ray);
  Color color = scene.background;
  if(minHit.hit) {
    color = shade(ray, minHit, scene, depth);
  }
  return color;
}

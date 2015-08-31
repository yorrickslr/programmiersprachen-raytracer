#ifndef BUW_BBOX_HPP
#define BUW_BBOX_HPP

#include <glm/vec3.hpp>
#include <glm/glm.hpp>
#include <ray.hpp>
#include <string>
#include <algorithm>
#include <map>

struct Bbox {
  Bbox(glm::vec3 const& min, glm::vec3 const& max) :
    min{min},
    max{max}
  {}
  glm::vec3 min;
  glm::vec3 max;
  bool intersect(Ray const& ray) {
    glm::vec3 invDirection{ (1 / ray.direction.x), (1 / ray.direction.y), (1 / ray.direction.z) };
    double t1 = (min[0] - ray.origin[0])*invDirection[0];
    double t2 = (max[0] - ray.origin[0])*invDirection[0];

    double tmin = std::min(t1, t2);
    double tmax = std::max(t1, t2);

    for (int i = 1; i < 3; ++i) {
      t1 = (min[i] - ray.origin[i])*invDirection[i];
      t2 = (max[i] - ray.origin[i])*invDirection[i];

      tmin = std::max(tmin, std::min(std::min(t1, t2), tmax));
      tmax = std::min(tmax, std::max(std::max(t1, t2), tmin));
    }

    if(tmax > std::max(tmin, 0.0)) {
      return true;
    }
    return false;
  }
  void add(Bbox const& bbox) {
   /* std::cout << std::endl;
    std::cout << "current = [" << min.x << "," << min.y << "," << min.z << "] , [" << max.x << "," << max.y << "," << max.z << "]" << std::endl;
    std::cout << "toAdd = [" << bbox.min.x << "," << bbox.min.y << "," << bbox.min.z << "] , [" << bbox.max.x << "," << bbox.max.y << "," << bbox.max.z << "]" << std::endl;*/
    min.x = std::min(min.x,bbox.min.x);
    min.y = std::min(min.y,bbox.min.y);
    min.z = std::min(min.z,bbox.min.z);
    max.x = std::max(max.x,bbox.max.x);
    max.y = std::max(max.y,bbox.max.y);
    max.z = std::max(max.z,bbox.max.z);
  }
};

#endif

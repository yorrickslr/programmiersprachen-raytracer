#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <shape.hpp>
#include <light.hpp>
#include <camera.hpp>
#include <memory>
#include <composite.hpp>


struct Scene{
  Scene() : 
    ambient_light{ Color{0.0,0.0,0.0} },
    composite{ std::make_shared<Composite>(Composite{}) },
    lights{},
    materials{},
    cameras{},
    background{0,0,0},
    camera{},
    filename{}
  {}

  ~Scene() {}

  Scene& operator=(Scene const& src) {
    ambient_light = src.ambient_light;
    composite = src.composite;
    lights = src.lights;
    materials = src.materials;
    cameras = src.cameras;
    background = src.background;
    camera = src.camera;
    filename = src.filename;
    return *this;
  };

  Color ambient_light;
  std::shared_ptr<Composite> composite /*= std::make_shared<Composite>(Composite{})*/;
  std::map<std::string, Light> lights;
  std::map<std::string, Material> materials;
  std::map<std::string, std::shared_ptr<Camera>> cameras;
  Color background;
  std::shared_ptr<Camera> camera;
  std::string filename;
};

#endif

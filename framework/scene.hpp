#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <shape.hpp>
#include <light.hpp>
#include <camera.hpp>
#include <memory>


struct Scene{
	Scene() : 
		ambient_light{ Color{0.0,0.0,0.0} },
		shapes{},
		lights{},
		materials{},
		camera{ Camera{} } {}
		/*shape_vec{},
		light_vec{},
		cam_vec{} {}*/

	~Scene() {}
		

	Color ambient_light;
	std::map<std::string, std::shared_ptr<Shape>> shapes; // shared_ptr instead of objects works! legal?
	std::map<std::string, Light> lights;
	std::map<std::string, Material> materials;
	Camera camera;
/*	std::vector<Shape> shape_vec;
	std::vector<Light> light_vec;
	std::vector<Camera> cam_vec;*/
};

#endif

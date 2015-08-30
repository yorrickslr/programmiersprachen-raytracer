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
		background{0,0,0}
		{}
		/*shape_vec{},
		light_vec{},
		cam_vec{} {}*/

	~Scene() {}
	Scene& operator=(Scene& src) {
		ambient_light = src.ambient_light;
		composite = src.composite;
		lights = src.lights;
		materials = src.materials;
		cameras = src.cameras;
		return *this;
	};

	Color ambient_light;
	 // shared_ptr instead of objects works! legal?
	std::shared_ptr<Composite> composite /*= std::make_shared<Composite>(new Composite{})*/;
	std::map<std::string, Light> lights;
	std::map<std::string, Material> materials;
	std::map<std::string, Camera> cameras;
	Color background;
/*	std::vector<Shape> shape_vec;
	std::vector<Light> light_vec;
	std::vector<Camera> cam_vec;*/
};

#endif

//move operator to a new file scene.cpp:

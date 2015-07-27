#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
#include <map>
#include <shape.hpp>
#include <light.hpp>
#include <camera.hpp>


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
	std::map<Shape> shapes; // Doch Map! Und per Value!
	std::map<Light> lights;
	std::map<Material> materials;
	Camera camera;
/*	std::vector<Shape> shape_vec;
	std::vector<Light> light_vec;
	std::vector<Camera> cam_vec;*/
};

#endif

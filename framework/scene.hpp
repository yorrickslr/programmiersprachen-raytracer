#ifndef BUW_SCENE_HPP
#define BUW_SCENE_HPP
//#include <vector>
#include <map>
#include <shape.hpp>
#include <light.hpp>
#include <camera.hpp>


struct Scene{
	Scene() : 
		ambient_light{ Color{0.0,0.0,0.0} },
		shapes{},
		lights{},
		camera{}
	{}
		/*shape_vec{},
		light_vec{},
		cam_vec{} {}*/

	~Scene() {}

	Color ambient_light;
	std::vector<Shape*> shapes;
	std::vector<Light*> lights;
	std::vector<Material*> materials;
	Camera* camera;
/*	std::vector<Shape> shape_vec;
	std::vector<Light> light_vec;
	std::vector<Camera> cam_vec;*/
};

#endif

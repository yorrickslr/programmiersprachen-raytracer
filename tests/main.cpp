#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.cpp"
#include "box.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <scene.hpp>
#include <triangle.hpp>
#include <hit.hpp>
#include <sdfloader.cpp>
#include <exception>

TEST_CASE("transformation tests", "[transformation]") {
	glm::vec3 one{0, 0, 0};
	glm::mat4 mat1(1.0f);

	std::cout << "Matrix vor der Translation:" << std::endl;
	std::cout << mat1[0][0] << " | " << mat1[0][1] << " | " << mat1[0][2] << " | " << mat1[0][3] << std::endl;
	std::cout << mat1[1][0] << " | " << mat1[1][1] << " | " << mat1[1][2] << " | " << mat1[1][3] << std::endl;
	std::cout << mat1[2][0] << " | " << mat1[2][1] << " | " << mat1[2][2] << " | " << mat1[2][3] << std::endl;
	std::cout << mat1[3][0] << " | " << mat1[3][1] << " | " << mat1[3][2] << " | " << mat1[3][3] << std::endl;

	glm::vec3 dir{2,2,-3};
	auto m = glm::translate(mat1, dir);
	auto n = glm::translate(m, dir);

	std::cout << "Matrix nach der Translation:" << std::endl;
	std::cout << m[0][0] << " | " << m[0][1] << " | " << m[0][2] << " | " << m[0][3] <<std::endl;
	std::cout << m[1][0] << " | " << m[1][1] << " | " << m[1][2] << " | " << m[1][3] <<std::endl;
	std::cout << m[2][0] << " | " << m[2][1] << " | " << m[2][2] << " | " << m[2][3] <<std::endl;
	std::cout << m[3][0] << " | " << m[3][1] << " | " << m[3][2] << " | " << m[3][3] <<std::endl;

	
	glm::vec3 two{m[3][0], m[3][1], m[3][2]};
	std::cout << "Neuer Punkt nach Translation: " << std::endl;
	std::cout << two.x << " | " << two.y << " | " << two.z << std::endl;
}

TEST_CASE("Let’s start with triangle-translation", "[triangle-translation]") {
	Triangle tri1{{0,0,0},{2,0,0},{1,2,0}};

	glm::vec3 dir{0,0,-5};

	glm::vec4 p1{tri1.get_p1(), 1.0f};
	glm::vec4 p2{tri1.get_p2(), 1.0f};
	glm::vec4 p3{tri1.get_p3(), 1.0f};

	glm::mat4 world_transformation = glm::translate(glm::mat4(1.0f), dir);

	glm::vec4 p1_trans = world_transformation * p1;
	glm::vec4 p2_trans = world_transformation * p2;
	glm::vec4 p3_trans = world_transformation * p3;

	std::cout << "Neue Punkte: " << std::endl;
	std::cout << "p1: " << std::endl;
	std::cout << p1_trans[0] << " | " << p1_trans[1] << " | " << p1_trans[2] << " | " << p1_trans[3] <<std::endl;
	std::cout << "p2: " << std::endl;
	std::cout << p2_trans[0] << " | " << p2_trans[1] << " | " << p2_trans[2] << " | " << p2_trans[3] <<std::endl;
	std::cout << "p3: " << std::endl;
	std::cout << p3_trans[0] << " | " << p3_trans[1] << " | " << p3_trans[2] << " | " << p3_trans[3] <<std::endl;

	// Triangle tri_trans{{p1_trans[0],p1_trans[1],p1_trans[2]},{p2_trans[0],p2_trans[1],p2_trans[2]},{p3_trans[0],p3_trans[1],p3_trans[2]}};
	glm::vec3 p1_trans_3{p1_trans};
	glm::vec3 p2_trans_3{p2_trans};
	glm::vec3 p3_trans_3{p3_trans};

	Triangle tri_trans{p1_trans_3, p2_trans_3, p3_trans_3};
}

TEST_CASE("test the triangle.translate()", "[I hope this works]") {
	Triangle tri1{{0,0,0},{2,0,0},{1,2,0}};
	glm::vec3 dir{0,0,-5};

	std::cout << "Altes Dreieck: " << std::endl;
	std::cout << "p1: " << std::endl;
	std::cout << tri1.get_p1().x << " | " << tri1.get_p1().y << " | " << tri1.get_p1().z << std::endl;
	std::cout << "p2: " << std::endl;
	std::cout << tri1.get_p2().x << " | " << tri1.get_p2().y << " | " << tri1.get_p2().z << std::endl;
	std::cout << "p3: " << std::endl;
	std::cout << tri1.get_p3().x << " | " << tri1.get_p3().y << " | " << tri1.get_p3().z << std::endl;

	tri1.translate(dir);

	std::cout << "Neues Dreieck: " << std::endl;
	std::cout << "p1: " << std::endl;
	std::cout << tri1.get_p1().x << " | " << tri1.get_p1().y << " | " << tri1.get_p1().z << std::endl;
	std::cout << "p2: " << std::endl;
	std::cout << tri1.get_p2().x << " | " << tri1.get_p2().y << " | " << tri1.get_p2().z << std::endl;
	std::cout << "p3: " << std::endl;
	std::cout << tri1.get_p3().x << " | " << tri1.get_p3().y << " | " << tri1.get_p3().z << std::endl;

}

TEST_CASE("test the sphere.translate()", "[I hope this works]") {
	Sphere sphere1{{0,0,0}, 1.0f};
	glm::vec3 dir{0,0,-5};

	std::cout << "Alte Kugel: " << std::endl;
	std::cout << "Center: " << std::endl;
	std::cout << sphere1.center().x << " | " << sphere1.center().y << " | " << sphere1.center().z << std::endl;
	std::cout << "Radius: " << std::endl;
	std::cout << sphere1.radius() << std::endl;

	sphere1.translate(dir);

	std::cout << "Neue Kugel: " << std::endl;
	std::cout << "Center: " << std::endl;
	std::cout << sphere1.center().x << " | " << sphere1.center().y << " | " << sphere1.center().z << std::endl;
	std::cout << "Radius: " << std::endl;
	std::cout << sphere1.radius() << std::endl;
}

TEST_CASE("test the box.translate()", "[I hope this works]") {
	Box box1{{0,0,0}, {1,1,1}};
	glm::vec3 dir{0,0,-5};

	std::cout << "Alte Box: " << std::endl;
	std::cout << "Min: " << std::endl;
	std::cout << box1.min().x << " | " << box1.min().y << " | " << box1.min().z << std::endl;
	std::cout << "Max: " << std::endl;
	std::cout << box1.max().x << " | " << box1.max().y << " | " << box1.max().z << std::endl;

	box1.translate(dir);

	std::cout << "Neue Box: " << std::endl;
	std::cout << "Min: " << std::endl;
	std::cout << box1.min().x << " | " << box1.min().y << " | " << box1.min().z << std::endl;
	std::cout << "Max: " << std::endl;
	std::cout << box1.max().x << " | " << box1.max().y << " | " << box1.max().z << std::endl;
}


// /*TEST_CASE("new sdfloader","[nsdfloader]") {
// 	Scene scene;
// 	std::ifstream file;
// 	file.open("input.sdf");
// 	REQUIRE(file.is_open());
// 	try {
// 		scene = loadScene(file);
// 	} catch(std::exception& e) {
// 		std::cerr << "---ERROR--- SDF-loader: " << e.what() << std::endl;
// 	}
// }

// TEST_CASE("Raycasting", "[raycast]") {
// 	float fov = 45;
// 	Camera cam{"eye",{0,0,0},{0,0,-1},{1,0,0},fov};
// 	cam.setResolution(100,100);
// 	glm::vec3 dir = cam.eyeRay(50,50).direction;
// 	std::cout << "Direction of ray at 50,50: {" << dir.x << "," << dir.y << "," << dir.z << "}" << std::endl;
// }

// TEST_CASE("Constructor for hit","[hit]")  {
// 	Hit hit;
// 	REQUIRE(hit.distance == 0);
// }*/
// /*
// TEST_CASE("output objects of scene","[print scene]") {
// 	Scene scene;
// 	std::ifstream file;
// 	file.open("input.sdf");
// 	REQUIRE(file.is_open());
// 	sdf_loadScene(file,scene);
// 	std::cout << "*** Printing Scene..." << std::endl;
// 	std::cout << "***    Materials:" << std::endl;
// 	for(auto element : scene.materials) {
// 		std::cout << "***       " << element.second.get_name() << std::endl;
// 	}
// 	std::cout << "***    Shapes:" << std::endl;
// 	for(auto element : scene.composite->get_children()) {
// 		std::cout << "***       " << element.second->name() << std::endl;
// 	}
// }

// TEST_CASE("material parse test for sdfloader","[sdfloader]") {
// 	Scene scene;
// 	std::ifstream file;	//must be relative to current shell dir or absolute
// 	file.open("input.sdf");
// 	REQUIRE(file.is_open()); //check if file exists
// 	sdf_loadScene(file,scene);
// 	Material tmp = scene.materials["red"];
// 	std::cout << tmp << std::endl;
// 	REQUIRE(tmp.get_name() == "red");
// 	tmp = scene.materials["blue"];
// 	REQUIRE(tmp.get_name() == "blue");
// 	std::cout << tmp << std::endl;
// 	file.close();
// }
// */
// /*TEST_CASE("testing triangle class","[triangle]") {
// 	Triangle tri{Material{}, "Dereck", glm::vec3{0.0,0.0,0.0}, glm::vec3{2.0,0.0,0.0}, glm::vec3{1.0,2.0,0.0}};
// 	glm::vec3 testp1{0.0,0.0,0.0};
// 	glm::vec3 testp2{2.0,0.0,0.0};
// 	glm::vec3 testp3{1.0,2.0,0.0};

// 	REQUIRE(testp1 == tri.get_p1());
// 	REQUIRE(testp2 == tri.get_p2());
// 	REQUIRE(testp3 == tri.get_p3());
// 	REQUIRE("Dereck" == tri.name());
// 	REQUIRE(Approx{2.0f} == tri.area());

// 	std::cout << "Funzt" << std::endl;

// 	Triangle tri2{Material{}, "Durak", glm::vec3{-1.0,0.0,0.0}, glm::vec3{1.0,0.0,0.0}, glm::vec3{0.0,2.0,0.0}};
// 	REQUIRE(Approx{2.0f} == tri2.area());

// 	Triangle tri3{Material{}, "Yorrick", glm::vec3{0.0,0.0,0.0}, glm::vec3{2.0,0.0,0.0}, glm::vec3{1.0,4.0,-2.0}};
// 	REQUIRE(Approx{4.4721f} == tri3.area());
// }*/

// TEST_CASE("get volume of sphere", "[volume]") {
// 	Sphere sphere;
// 	REQUIRE(sphere.volume() == Approx(4.1888));
// }

// TEST_CASE("get area of sphere", "[area]") {
// 	Sphere sphere;
// 	REQUIRE(sphere.area() == Approx(12.5664));
// }

// TEST_CASE("get radius of sphere", "[radius]") {
// 	Sphere sphere;
// 	REQUIRE(sphere.radius() == 1);
// }

// TEST_CASE("get center of sphere", "[center]") {
// 	Sphere sphere;
// 	glm::vec3 tmp{0,0,0};
// 	REQUIRE(sphere.center() == tmp);
// }

// TEST_CASE("constructors of sphere", "[constructors]") {
// 	Sphere s1;
// 	Sphere s2{{0,0,0},1};
// 	REQUIRE(s1.center() == s2.center());
// 	REQUIRE(s1.radius() == s2.radius());
// 	REQUIRE(s1.area() == s2.area());
// 	REQUIRE(s1.volume() == s2.volume());
// }

// TEST_CASE("constructors for box", "[constructors]") {
// 	Box b1;
// 	glm::vec3 tmp{0,0,0};
// 	REQUIRE(b1.min() == tmp);
// 	tmp = {1,1,1};
// 	REQUIRE(b1.max() == tmp);
// 	Box b2{{1,1,3},{3,2,2}};
// 	tmp = {1,1,2};
// 	REQUIRE(b2.min() == tmp);
// 	tmp = {3,2,3};
// 	REQUIRE(b2.max() == tmp);
// }

// TEST_CASE("get area of box", "[area]") {
// 	Box box;
// 	REQUIRE(box.area() == 6);
// }

// TEST_CASE("get volume of box", "[area]") {
// 	Box box;
// 	REQUIRE(box.volume() == 1);
// }

// /*TEST_CASE("get color of sphere", "[color]") {
// 	Sphere sphere;
// 	Color tmp{100,100,100};
// 	REQUIRE(sphere.color().r == tmp.r);
// 	REQUIRE(sphere.color().g == tmp.g);
// 	REQUIRE(sphere.color().b == tmp.b);
// }*/

// TEST_CASE("get name of sphere", "[name]") {
// 	Sphere sphere;
// 	REQUIRE(sphere.name() == "default");
// }

// /*TEST_CASE("shape constructor for sphere") {
// 	Sphere sphere{{1,2,3},4.2,{255,200,200},"test"};
// 	REQUIRE(sphere.name() == "test");
// 	REQUIRE(sphere.color().r == 255);
// 	glm::vec3 tmp{1,2,3};
// 	REQUIRE(sphere.center() == tmp);
// 	REQUIRE(sphere.radius() == 4.2);
// }*/

// /*TEST_CASE("get color of box", "[color]") {
// 	Box box;
// 	Color tmp{100,100,100};
// 	REQUIRE(box.color().r == tmp.r);
// 	REQUIRE(box.color().g == tmp.g);
// 	REQUIRE(box.color().b == tmp.b);
// }*/

// TEST_CASE("get name of box", "[name]") {
// 	Box box;
// 	REQUIRE(box.name() == "default");
// }

// /*TEST_CASE("shape constructor for box") {
// 	Box box{{1,2,3},{4,5,6},{255,200,200},"test"};
// 	REQUIRE(box.name() == "test");
// 	REQUIRE(box.color().r == 255);
// 	glm::vec3 tmp{1,2,3};
// 	REQUIRE(box.min() == tmp);
// 	tmp = {4,5,6};
// 	REQUIRE(box.max() == tmp);
// }*/

// TEST_CASE("use ostream of shape", "[ostream]") {
// 	Sphere sphere;
// 	std::cout << sphere << std::endl;
// }

// TEST_CASE("use ostream of box", "[ostream]") {
// 	Box box;
// 	std::cout << box << std::endl;
// }

// /*TEST_CASE("intersectRaySphere", "[intersect]") {
// 	//Ray
// 	glm :: vec3 ray_origin (0.0 ,0.0 ,0.0);
// 	//ray direction has to be normalized!
// 	//you can use:
// 	//v = glm::normalize(some_vector)
// 	glm::vec3 ray_direction(0.0,0.0,1.0);
// 	// Sphere
// 	glm::vec3 sphere_center(0.0,0.0,5.0);
// 	float sphere_radius(1.0);

// 	float distance (0.0);
// 	auto result = glm::intersectRaySphere(
// 	ray_origin, ray_direction,
// 	sphere_center, sphere_radius,
// 	distance);
// 	REQUIRE(distance == Approx(4.0f));
// }*/

// /*TEST_CASE("intersect ray with sphere method","[intersect]") {
// 	Ray ray{{0.0f,0.0f,0.0f},{0.0,0.0,1.0}};
// 	Sphere sphere{{0.0,0.0,5.0},1.0};
// 	float distance{0.0};
// 	REQUIRE(sphere.intersect(ray,distance) == true);
// 	REQUIRE(distance == Approx(4.0f));
// }*/

// /*TEST_CASE("virtual constructor of shape","[constructor]") {
// 	std::cout << "\r\ntest-case: 'virtual constructor of shape'" << std::endl;
// 	Color red(255,0,0);
// 	glm::vec3 position(0,0,0);
// 	Sphere* s1 = new Sphere(position,1.2,red,"sphere0");
// 	Shape* s2 = new Sphere(position,1.2,red,"sphere1");
// 	s1->print(std::cout);
// 	s2->print(std::cout);
// 	delete s1;
// 	delete s2;
// }*/

// //TEST_CASE("intersect ray with box method","[intersect]") {
// //	Ray ray{{0.0f,0.0f,0.0f},{0.0,0.0,1.0}};
// //	Box box{{-1,-1,2},{1,1,2}};
// //	float distance{0.0};
// //	REQUIRE(box.intersect(ray,distance) == true);
// //	REQUIRE(distance == Approx(2.0f));
// //}

// /*TEST_CASE("intersect box","[intersect]") {
// 	Box box{{1,1,0},{3,3,2}};
// 	Ray ray{{0,1,0},{0.5,0.5,0.5}};
// 	float distance;
// 	REQUIRE(box.intersect(ray,distance));
// 	REQUIRE(distance == Approx(sqrt(3)));
// }*/

// /*TEST_CASE("intersect box with negative min","[intersect]") {
// 	Box box{{-3,-0.5,-0.5},{-3.2, 0.5, 0.5}};
// 	Ray ray{{0,0,0},{-1,0,0}};
// 	float distance{0};
// 	REQUIRE(box.intersect(ray,distance));
// 	REQUIRE(distance == 3);
// }*/

// /*TEST_CASE("intersect ray with triangle", "[intersect]"){
// 	Ray ray{{0,0,0},{0,-1,0}};
// 	Triangle test_tri{{0,-3,1},{2,-3,-0.5},{-2,-3,-0.5}};
// 	float distance{0};
// 	REQUIRE(test_tri.intersect(ray, distance));
// 	REQUIRE(3 == distance);
// }*/

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}

/* Aufgabe 6.7
	s1 ist ein shared Pointer vom Typ sphere.
	s2 ist ein shared pointer vom Typ shape.
	s1 ist hier statisch, 
	da ihm nur Objekte des Typs sphere zugewiesen werden koennen.
	s2 dagegen ist dynamisch, weil es sich um einen Typ der Basisklasse handelt:
	Es kann ihr sowohl ein Objekt vom Typ der Basisklasse, 
	als auch eines der abgeleiteten Klasse zugewiesen werden.

	Falls sphere noch eine abgeleitete Klasse haette,
	so wuerde s1 auch insofern dynamisch sein,
	als dass man ein Objekt der abgeleiteten Klasse zuweisen kann.
*/

/* Aufgabe 6.8
	Output with virtual:
		test-case: 'virtual constructor of shape'
		Construction of sphere
		Construction of sphere
		name: sphere0
		color: (255,0,0)
		center: [0,0,0]
		radius: 1.2
		name: sphere1
		color: (255,0,0)
		center: [0,0,0]
		radius: 1.2
		Destruction of sphere
		Destruction of shape
		Destruction of sphere
		Destruction of shape
	Output without virtual:
		test-case: 'virtual constructor of shape'
		Construction of sphere
		Construction of sphere
		name: sphere0
		color: (255,0,0)
		center: [0,0,0]
		radius: 1.2
		name: sphere1
		color: (255,0,0)
		center: [0,0,0]
		radius: 1.2
		Destruction of sphere
		Destruction of shape
		Destruction of shape
	Wenn der Destruktor von shape als virtual deklariert ist,
	so wird beim Loeschen auch der ueberschreibende Destruktor aufgerufen,
	da es sich um einen Pointer auf ein Objekt des abgeleiteten Typs handelt.
	Laesst man das virtual weg, 
	so wir nur der Destruktor der Basisklasse aufgerufen
	(es findet ja keine Ueberschreibung statt).
*/

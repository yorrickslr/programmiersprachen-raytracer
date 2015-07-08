#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.cpp"
#include "box.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>
#include <iostream>
#include <fstream>
#include <sdfloader.hpp>
#include <string>
#include <scene.hpp>
#include <triangle.hpp>

TEST_CASE("material parse test for sdfloader","[sdfloader]") {
	Scene scene;
	std::ifstream file{"input.sdf"};	//must be relative to current shell dir or absolute
	sdf_loadScene(file,scene);
	Material tmp = *(scene.materials[0]);
	std::cout << tmp << std::endl;
	REQUIRE(tmp.get_name() == "red");
	tmp = *(scene.materials[1]);
	REQUIRE(tmp.get_name() == "blue");
	std::cout << tmp << std::endl;
}

TEST_CASE("testing triangle class","[triangle]") {
	Triangle tri{Material{}, "Dereck", glm::vec3{0.0,0.0,0.0}, glm::vec3{2.0,0.0,0.0}, glm::vec3{1.0,2.0,0.0}};
	glm::vec3 testp1{0.0,0.0,0.0};
	glm::vec3 testp2{2.0,0.0,0.0};
	glm::vec3 testp3{1.0,2.0,0.0};

	REQUIRE(testp1 == tri.get_p1());
	REQUIRE(testp2 == tri.get_p2());
	REQUIRE(testp3 == tri.get_p3());
	REQUIRE("Dereck" == tri.name());
	REQUIRE(Approx{2.0f} == tri.area());

	std::cout << "Funzt" << std::endl;

	Triangle tri2{Material{}, "Durak", glm::vec3{-1.0,0.0,0.0}, glm::vec3{1.0,0.0,0.0}, glm::vec3{0.0,2.0,0.0}};
	REQUIRE(Approx{2.0f} == tri2.area());

	Triangle tri3{Material{}, "Yorrick", glm::vec3{0.0,0.0,0.0}, glm::vec3{2.0,0.0,0.0}, glm::vec3{1.0,4.0,-2.0}};
	REQUIRE(Approx{4.4721f} == tri3.area());
}

TEST_CASE("get volume of sphere", "[volume]") {
	Sphere sphere;
	REQUIRE(sphere.volume() == Approx(4.1888));
}

TEST_CASE("get area of sphere", "[area]") {
	Sphere sphere;
	REQUIRE(sphere.area() == Approx(12.5664));
}

TEST_CASE("get radius of sphere", "[radius]") {
	Sphere sphere;
	REQUIRE(sphere.radius() == 1);
}

TEST_CASE("get center of sphere", "[center]") {
	Sphere sphere;
	glm::vec3 tmp{0,0,0};
	REQUIRE(sphere.center() == tmp);
}

TEST_CASE("constructors of sphere", "[constructors]") {
	Sphere s1;
	Sphere s2{{0,0,0},1};
	REQUIRE(s1.center() == s2.center());
	REQUIRE(s1.radius() == s2.radius());
	REQUIRE(s1.area() == s2.area());
	REQUIRE(s1.volume() == s2.volume());
}

TEST_CASE("constructors for box", "[constructors]") {
	Box b1;
	glm::vec3 tmp{0,0,0};
	REQUIRE(b1.min() == tmp);
	tmp = {1,1,1};
	REQUIRE(b1.max() == tmp);
	Box b2{{1,1,3},{3,2,2}};
	tmp = {1,1,2};
	REQUIRE(b2.min() == tmp);
	tmp = {3,2,3};
	REQUIRE(b2.max() == tmp);
}

TEST_CASE("get area of box", "[area]") {
	Box box;
	REQUIRE(box.area() == 6);
}

TEST_CASE("get volume of box", "[area]") {
	Box box;
	REQUIRE(box.volume() == 1);
}

/*TEST_CASE("get color of sphere", "[color]") {
	Sphere sphere;
	Color tmp{100,100,100};
	REQUIRE(sphere.color().r == tmp.r);
	REQUIRE(sphere.color().g == tmp.g);
	REQUIRE(sphere.color().b == tmp.b);
}*/

TEST_CASE("get name of sphere", "[name]") {
	Sphere sphere;
	REQUIRE(sphere.name() == "default");
}

/*TEST_CASE("shape constructor for sphere") {
	Sphere sphere{{1,2,3},4.2,{255,200,200},"test"};
	REQUIRE(sphere.name() == "test");
	REQUIRE(sphere.color().r == 255);
	glm::vec3 tmp{1,2,3};
	REQUIRE(sphere.center() == tmp);
	REQUIRE(sphere.radius() == 4.2);
}*/

/*TEST_CASE("get color of box", "[color]") {
	Box box;
	Color tmp{100,100,100};
	REQUIRE(box.color().r == tmp.r);
	REQUIRE(box.color().g == tmp.g);
	REQUIRE(box.color().b == tmp.b);
}*/

TEST_CASE("get name of box", "[name]") {
	Box box;
	REQUIRE(box.name() == "default");
}

/*TEST_CASE("shape constructor for box") {
	Box box{{1,2,3},{4,5,6},{255,200,200},"test"};
	REQUIRE(box.name() == "test");
	REQUIRE(box.color().r == 255);
	glm::vec3 tmp{1,2,3};
	REQUIRE(box.min() == tmp);
	tmp = {4,5,6};
	REQUIRE(box.max() == tmp);
}*/

TEST_CASE("use ostream of shape", "[ostream]") {
	Sphere sphere;
	std::cout << sphere << std::endl;
}

TEST_CASE("use ostream of box", "[ostream]") {
	Box box;
	std::cout << box << std::endl;
}

TEST_CASE("intersectRaySphere", "[intersect]") {
	//Ray
	glm :: vec3 ray_origin (0.0 ,0.0 ,0.0);
	//ray direction has to be normalized!
	//you can use:
	//v = glm::normalize(some_vector)
	glm::vec3 ray_direction(0.0,0.0,1.0);
	// Sphere
	glm::vec3 sphere_center(0.0,0.0,5.0);
	float sphere_radius(1.0);

	float distance (0.0);
	auto result = glm::intersectRaySphere(
	ray_origin, ray_direction,
	sphere_center, sphere_radius,
	distance);
	REQUIRE(distance == Approx(4.0f));
}

TEST_CASE("intersect ray with sphere method","[intersect]") {
	Ray ray{{0.0f,0.0f,0.0f},{0.0,0.0,1.0}};
	Sphere sphere{{0.0,0.0,5.0},1.0};
	float distance{0.0};
	REQUIRE(sphere.intersect(ray,distance) == true);
	REQUIRE(distance == Approx(4.0f));
}

/*TEST_CASE("virtual constructor of shape","[constructor]") {
	std::cout << "\r\ntest-case: 'virtual constructor of shape'" << std::endl;
	Color red(255,0,0);
	glm::vec3 position(0,0,0);
	Sphere* s1 = new Sphere(position,1.2,red,"sphere0");
	Shape* s2 = new Sphere(position,1.2,red,"sphere1");
	s1->print(std::cout);
	s2->print(std::cout);
	delete s1;
	delete s2;
}*/

//TEST_CASE("intersect ray with box method","[intersect]") {
//	Ray ray{{0.0f,0.0f,0.0f},{0.0,0.0,1.0}};
//	Box box{{-1,-1,2},{1,1,2}};
//	float distance{0.0};
//	REQUIRE(box.intersect(ray,distance) == true);
//	REQUIRE(distance == Approx(2.0f));
//}

TEST_CASE("intersect box","[intersect]") {
	Box box{{1,1,0},{3,3,2}};
	Ray ray{{0,1,0},{0.5,0.5,0.5}};
	float distance;
	REQUIRE(box.intersect(ray,distance));
	REQUIRE(distance == Approx(sqrt(3)));
}

TEST_CASE("intersect box with negative min","[intersect]") {
	Box box{{-3,-0.5,-0.5},{-3.2, 0.5, 0.5}};
	Ray ray{{0,0,0},{-1,0,0}};
	float distance{0};
	REQUIRE(box.intersect(ray,distance));
	REQUIRE(distance == 3);
}

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

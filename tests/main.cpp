#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "sphere.cpp"
#include "box.hpp"
#include "color.hpp"
#include <glm/vec3.hpp>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtx/intersect.hpp>

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

TEST_CASE("get color of sphere", "[color]") {
	Sphere sphere;
	Color tmp{100,100,100};
	REQUIRE(sphere.color().r == tmp.r);
	REQUIRE(sphere.color().g == tmp.g);
	REQUIRE(sphere.color().b == tmp.b);
}

TEST_CASE("get name of sphere", "[name]") {
	Sphere sphere;
	REQUIRE(sphere.name() == "default");
}

TEST_CASE("shape constructor for sphere") {
	Sphere sphere{{1,2,3},4.2,{255,200,200},"test"};
	REQUIRE(sphere.name() == "test");
	REQUIRE(sphere.color().r == 255);
	glm::vec3 tmp{1,2,3};
	REQUIRE(sphere.center() == tmp);
	REQUIRE(sphere.radius() == 4.2);
}

TEST_CASE("get color of box", "[color]") {
	Box box;
	Color tmp{100,100,100};
	REQUIRE(box.color().r == tmp.r);
	REQUIRE(box.color().g == tmp.g);
	REQUIRE(box.color().b == tmp.b);
}

TEST_CASE("get name of box", "[name]") {
	Box box;
	REQUIRE(box.name() == "default");
}

TEST_CASE("shape constructor for box") {
	Box box{{1,2,3},{4,5,6},{255,200,200},"test"};
	REQUIRE(box.name() == "test");
	REQUIRE(box.color().r == 255);
	glm::vec3 tmp{1,2,3};
	REQUIRE(box.min() == tmp);
	tmp = {4,5,6};
	REQUIRE(box.max() == tmp);
}

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
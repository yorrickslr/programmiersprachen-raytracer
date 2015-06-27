#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <sphere.cpp>
#include <glm/vec3.hpp>

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

int main(int argc, char *argv[]) {
  return Catch::Session().run(argc, argv);
}

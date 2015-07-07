#include <sdfloader.hpp>


void SDFLoader::getScene(std::ifstream& file, Scene& scene) {
	std::string line = "";
	while(std::getline(file,line)) {
		std::cout << line << std::endl;
	}
}
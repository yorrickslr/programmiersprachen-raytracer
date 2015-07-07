#include <sdfloader.hpp>


Scene SDFLoader::getScene(std::ifstream file) {
	std::string line{""};
	while(std::getline(file,line)) {
		std::cout << line << std::endl;
	}
}
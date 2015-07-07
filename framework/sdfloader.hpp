#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <fstream>
#include <string>
#include <scene.hpp>

class SDFLoader {
public:
	SDFLoader();
	SDFLoader(std::ifstream& file);
	~SDFLoader();
	Scene getScene();
private:
	std::ifstream file_;
};

#endif

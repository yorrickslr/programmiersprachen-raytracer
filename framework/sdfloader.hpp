#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>

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

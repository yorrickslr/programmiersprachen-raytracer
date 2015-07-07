#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>

class SDFLoader {
public:
	SDFLoader();
	SDFLoader(std::fstream& file);
	~SDFLoader();
	Scene getScene();
private:
	std::fstream file_;
};

#endif

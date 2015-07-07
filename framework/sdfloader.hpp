#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>
#include <vector>

void loadScene(std::ifstream& file, Scene& scene) {
	std::string line{""};
	while(std::getline(file,line)) {
		vector<std::string> input = split(line," ");
	}
}

#endif

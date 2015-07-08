#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

void sdf_splitString(std::string const& input, std::vector<std::string>& output) {
	std::istringstream tmp{input};
	do {
		std::string sub{""};
		tmp >> sub;
		output.push_back(sub);
	} while(tmp);
}

bool sdf_isMaterial(std::string const& input, Material*& material) {
	std::regex rgx_material{"define[\\s\\t]material[\\s\\t]\\S+[\\s\\t]([0-9][\\s\\t]){9}[0-9].*"};
	if(std::regex_match(input,rgx_material)) {
		std::vector<std::string> parsed;
		sdf_splitString(input,parsed);
		material = new Material{parsed[2],{1,1,1},{1,1,1},{1,1,1},4.2};
		return true;
	}
	return false;
}

void sdf_loadScene(std::ifstream& file, Scene& scene) {
	std::string line{""};
	while(std::getline(file,line)) {
		// Material
		Material* tmp_material{nullptr};
		if(sdf_isMaterial(line,tmp_material)) {
			scene.materials.push_back(tmp_material);
		}
		tmp_material = nullptr;
	}
}

#endif

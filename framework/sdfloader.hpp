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
		Color ka = {std::stof(parsed[3]),std::stof(parsed[4]),std::stof(parsed[5])};
		Color kd = {std::stof(parsed[6]),std::stof(parsed[7]),std::stof(parsed[8])};
		Color ks = {std::stof(parsed[9]),std::stof(parsed[10]),std::stof(parsed[11])};
		material = new Material{parsed[2],ka,kd,ks,std::stof(parsed[12])};
		return true;
	}
	return false;
}

bool sdf_isComment(std::string const& input) {
	std::regex rgx_comment{"^#.*"};
	if(std::regex_match(input, rgx_comment)) {
		return true;
	}
	return false;
}

void sdf_loadScene(std::ifstream& file, Scene& scene) {
	std::string line{""};
	while(std::getline(file,line)) {
		//Comment
		if(sdf_isComment(line)) {
			continue;
		}
		// Material
		Material* tmp_material{nullptr};
		if(sdf_isMaterial(line,tmp_material)) {
			scene.materials.push_back(tmp_material);
			continue;
		}
	}
}

#endif

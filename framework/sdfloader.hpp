#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>

bool sdf_isMaterial(std::string const& input, Material* material) {	
	std::regex rgx_material{"define material \\S+ ([0-9] ){9}[0-9]\\s*"};	
	if(std::regex_match(input,rgx_material)) {		
		material = new Material{"name",{1,1,1},{1,1,1},{1,1,1},4.2};
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

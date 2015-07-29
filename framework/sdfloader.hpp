#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include <glm/vec3.hpp>

#include <material.hpp>
#include <sphere.hpp>
#include <shape.hpp>
#include <camera.hpp>

void sdf_splitString(std::string const& input, std::vector<std::string>& output) {
	std::istringstream tmp{input};
	do {
		std::string sub{""};
		tmp >> sub;
		output.push_back(sub);
	} while(tmp);
}

bool sdf_isComment(std::string const& input) {
	std::regex rgx_comment{"^[\\s\\t]*#.*$"};
	if(std::regex_match(input, rgx_comment)) {
		return true;
	}
	return false;
}

bool sdf_isEmpty(std::string const& input) {
	std::regex rgx_emptyLine{"^[\\s\\t]*$"};
	if(std::regex_match(input,rgx_emptyLine)) {
		return true;
	}
	return false;
}

bool sdf_isSphere(std::string const& input) {
	std::regex rgx_sphere{"^[\\s\\t]*define[\\s\\t]+shape[\\s\\t]+sphere[\\s\\t]+\\S+[\\s\\t]+([0-9]+(\\.[0-9]+)?[\\s\\t]+){4}\\S+[\\s\\t]*$"};
	if(std::regex_match(input,rgx_sphere)) {
		return true;
	}
	return false;
}

bool sdf_parseSphere(
		std::string const& input, 
		std::map<std::string,std::shared_ptr<Shape>>& shapes, 
		std::map<std::string,Material>& materials) {
	std::vector<std::string> parsed;
	sdf_splitString(input, parsed);
	glm::vec3 center{std::stod(parsed[4]), std::stod(parsed[5]), std::stod(parsed[6])};
	auto iterator = materials.find(parsed[8]);
	if(iterator == materials.end()) {
		return false;
	}
	std::shared_ptr<Shape> pointer = std::make_shared<Sphere>(center, std::stod(parsed[7]), iterator->second, parsed[3]);
	shapes.insert(shapes.end(),std::pair<std::string,std::shared_ptr<Shape>>(parsed[3], pointer));
	std::cout << "***DEBUG*** parsed sphere" << std::endl;
	return true;
}

bool sdf_isBox(std::string const& input) {
	std::regex rgx_box{"^[\\s\\t]*define[\\s\\t]+shape[\\s\\t]+box[\\s\\t]+\\S+[\\s\\t]+([0-9]+(\\.[0-9]+)?[\\s\\t]+){6}\\S+[\\s\\t]*$"};
	if(std::regex_match(input, rgx_box)) {
		return true;
	}
	return false;
}

bool sdf_parseBox(
		std::string const& input,
		std::map<std::string,std::shared_ptr<Shape>>& shapes,
		std::map<std::string,Material>& materials) {
	std::vector<std::string> parsed;
	sdf_splitString(input, parsed);
	glm::vec3 min{std::stod(parsed[4]),std::stod(parsed[5]),std::stod(parsed[6])};
	glm::vec3 max{std::stod(parsed[7]),std::stod(parsed[8]),std::stod(parsed[9])};
	auto iterator = materials.find(parsed[10]);
	if(iterator == materials.end()) {
		return false;
	}
	std::shared_ptr<Shape> pointer = std::make_shared<Box>(min, max, iterator->second, parsed[3]);
	shapes.insert(shapes.end(),std::pair<std::string, std::shared_ptr<Shape>>(parsed[3],pointer));
	std::cout << "***DEBUG*** parsed box" << std::endl;
	return true;
}

bool sdf_isMaterial(std::string const& input) {
	std::cout << "***DEBUG*** bin drin" << std::endl;
	std::regex rgx_material{"^[\\s\\t]*define[\\s\\t]+material[\\s\\t]+\\S+[\\s\\t]+([0-1](\\.[0-9]+)?[\\s\\t]+){9}[0-9](\\.[0-9]+)?+[\\s\\t]*$"};
	if(std::regex_match(input,rgx_material)) {
		return true;
	}
	return false;
}

bool sdf_parseMaterial(std::string const& input, std::map<std::string,Material>& materials) {
	std::vector<std::string> parsed;
	sdf_splitString(input,parsed);
	Color ka = {std::stof(parsed[3]),std::stof(parsed[4]),std::stof(parsed[5])};
	Color kd = {std::stof(parsed[6]),std::stof(parsed[7]),std::stof(parsed[8])};
	Color ks = {std::stof(parsed[9]),std::stof(parsed[10]),std::stof(parsed[11])};
	materials.insert(materials.end(),std::pair<std::string,Material>(parsed[2],{parsed[2],ka,kd,ks,std::stof(parsed[12])}));
	return true;
}

// Should detect camera, not finished yet
bool sdf_isCamera(std::string const& input) {
	std::cout << "***DEBUG*** regex ok" << std::endl;
	std::regex rgx_camera{"^[\\s\\t]*camera[\\s\\t]+\\S+[\\s\\t]+[0-9]+(\\.[0-9]+)?[\\s\\t]+([0-9]+(\\.[0-9]+)?[\\s\\t]+){8}[0-9]+(\\.[0-9]+)?[\\s\\t]*$"};
	if(std::regex_match(input,rgx_camera)) {
		return true;
	}
	return false; 			// camera 	<name> <fov-x> <eye> <dir> <up>
}

void sdf_parseCamera(std::string const& input, Camera cam) {
	std::vector<std::string> parsed;
	sdf_splitString(input, parsed);
	glm::vec3 eye{std::stod(parsed[3]), std::stod(parsed[4]), std::stod(parsed[5])};
	glm::vec3 dir{std::stod(parsed[6]), std::stod(parsed[7]), std::stod(parsed[8])};
	glm::vec3 up{std::stod(parsed[9]), std::stod(parsed[10]), std::stod(parsed[11])};
	auto name = parsed[1];
	auto fov = std::stof(parsed[2]);
	Camera tmp{name, eye, dir, up, fov};
	cam = tmp;
}

// isLight 
/*bool sdf_isLight(std::string const& input) {
	std::regex rgx_light{};
	if(std::regex_match(input,rgx_light)) {
		return true;
	}
	return false;
}
*/

// Light parser
/*void sdf_parseCamera(std::string const& input, std::map<std::string,Light>& lights) {
	std::vector<std::string> parsed;

*/


void sdf_loadScene(std::ifstream& file, Scene& scene) {
	std::string line{""};
	int lineCount{0};
	while(std::getline(file,line)) {
		lineCount++;
		//Comment
		if(sdf_isComment(line) || sdf_isEmpty(line)) {
			std::cout << "***DEBUG*** continued at line " << lineCount << std::endl;
			continue;
		}
		//Sphere
		if(sdf_isSphere(line)) {
			if(!sdf_parseSphere(line,scene.shapes,scene.materials)) {
				std::cout << "---ERROR--- could not parse sphere (material not defined?) in line" << lineCount << std::endl;
			}
			continue;
		}
		//Box
		if(sdf_isBox(line)) {
			if(!sdf_parseBox(line,scene.shapes,scene.materials)) {
				std::cout << "---ERROR--- could not parse box (material not defined?) in line" << lineCount << std::endl;
			}
			continue;
		}
		// Material	
		if(sdf_isMaterial(line)) {		
			sdf_parseMaterial(line,scene.materials);		
			//scene.materials.push_back(tmp_material);
			continue;
		}
		// Camera
		if(sdf_isCamera(line)) {
			sdf_parseCamera(line, scene.camera);
			continue;
		}
		std::cout << "---ERROR--- line " << lineCount << " could not be parsed" << std::endl;
		break;
	}
}

#endif

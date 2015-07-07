#include <sdfloader.hpp>
#include <iostream>

SDFLoader::SDFLoader() :
	file_{""}
{}

SDFLoader::SDFLoader(std:ifstream& file) :
	file_{file}
{}

SDFLoader::~SDFLoader() {}

Scene SDFLoader::getScene() {
	while(std::getline(file_,line)) {
		std::cout << line << std::endl;
	}
}
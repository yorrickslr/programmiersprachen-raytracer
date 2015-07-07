#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <string>
#include <scene.hpp>
#include <iostream>
#include <fstream>

class SDFLoader {
public:
	void getScene(std::ifstream& file, Scene& scene);
private:
	std::ifstream& file_;
};

#endif

#ifndef BUW_SDFLOADER_HPP
#define BUW_SDFLOADER_HPP

#include <fstream>

struct Scenedummy {
};

class SDFLoader {
public:
	SDFLoader();
	SDFLoader(std::ifstream file);
	~SDFLoader();
	Scenedummy getScene();
private:
	std::fstream file_;
};

#endif

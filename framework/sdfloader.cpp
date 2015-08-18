#include <iostream>
#include <scene.hpp>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>
#include <shape.hpp>
#include <box.hpp>
#include <memory>

Scene& nsdf_loadScene(std::ifstream& file) {
  Scene* scene = new Scene();
  std::string line;
  int lineCount{0};
  while(std::getline(file,line)) {
    lineCount++;
    std::string lineCountStr = std::to_string(lineCount);
    std::vector<std::string> input;
    std::istringstream stream{line};
    do {
      std::string sub{""};
      stream >> sub;
      input.push_back(sub);
    } while(stream);
    // Parsing
    if(line.empty() || input[0].at(0)=='#') {
      std::cout << lineCount << ": empty line detected, nothing to do...." << std::endl;
    } else if(input[0]=="define" && input[1]=="shape") {
      if(input[2]=="box") {
        std::cout << lineCount << ": box detected, going to parse..." << std::endl;
        std::shared_ptr<Shape> ptr = std::make_shared<Box>(Box{});
        scene->composite->add(ptr); //shitty code, muss aber irgendwie? =S
      } else if(input[2]=="sphere") {
        std::cout << lineCount << ": sphere detected, going to parse..." << std::endl;
      } else if(input[2]=="triangle") {
        std::cout << lineCount << ": triangle detected, going to parse..." << std::endl;
      } else if(input[2]=="composite") {
        std::cout << lineCount << ": composite detected, going to parse..." << std::endl;
      } else {
        throw std::logic_error("cannot parse shape at line " + lineCountStr);
      }
    } else if(input[0]=="define" && input[1]=="material") {
      std::cout << lineCount << ": material detected, going to parse..." << std::endl;
    } else {
      throw std::logic_error("cannot parse line " + lineCountStr);
    }
  }
  return *scene;
}
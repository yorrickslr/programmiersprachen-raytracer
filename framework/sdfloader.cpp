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

      if(input[2]=="box" && input.size() == 10) {
        std::cout << lineCount << ": box detected, going to parse..." << std::endl;

        // Box components
        glm::vec3 min{std::stod(input[4]),std::stod(input[5]),std::stod(input[6])};
        glm::vec3 max{std::stod(input[7]),std::stod(input[8]),std::stod(input[9])};
        std::string name = input[3];
        auto iterator = materials.find(input[10]);

        if(iterator == materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to box and add it to composite
        std::shared_ptr<Shape> ptr = std::make_shared<Box>(min, max, iterator->second, name);
        scene->composite->add(ptr); //shitty code, muss aber irgendwie? =S


      } else if(input[2]=="sphere" && input.size() == 8) {
        std::cout << lineCount << ": sphere detected, going to parse..." << std::endl;

        // Sphere components
        glm::vec3 center{std::stod(input[4]), std::stod(input[5]), std::stod(input[6])};
        auto iterator = materials.find(input[8]);

        if(iterator == materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to Sphere and add it to composite  
        std::shared_ptr<Shape> ptr = std::make_shared<Sphere>(center, std::stod(input[7]), iterator->second, input[3]);
        scene->composite->add(ptr);
        
      } else if(input[2]=="triangle" && input.size() == 13) {
        std::cout << lineCount << ": triangle detected, going to parse..." << std::endl;

        // Triangle components
        glm::vec3 p1{std::stod(input[4]),std::stod(input[5]),std::stod(input[6])};
        glm::vec3 p2{std::stod(input[7]),std::stod(input[8]),std::stod(input[9])};
        glm::vec3 p3{std::stod(input[10]),std::stod(input[11]),std::stod(input[12])};
        auto iterator = materials.find(input[13]);

        if(iterator == materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to Triangle and add it to composite
        std::shared_ptr<Shape> ptr = std::make_shared<Triangle>(input[3], p1, p2, p3, iterator->second);
        scene->composite->add(ptr);

      } else if(input[2]=="composite") {
        std::cout << lineCount << ": composite detected, going to parse..." << std::endl;
        std::shared_ptr<Shape> ptr = std::make_shared<Composite>(input[3]);
        scene->composite->add(ptr);

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

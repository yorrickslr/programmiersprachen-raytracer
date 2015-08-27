#include <iostream>
#include <scene.hpp>
#include <fstream>
#include <string>
#include <exception>
#include <sstream>
#include <shape.hpp>
#include <box.hpp>
#include <sphere.hpp>
#include <triangle.hpp>
#include <material.hpp>
#include <memory>
#include <vector>

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
    if(line.empty() || input.size()==0 || input[0].length()==0) {
        std::cout << lineCount << ": empty line detected, nothing to do...." << std::endl;
    } else if(input[0].length()>0) {
      if(input[0].at(0) == '#') {
        std::cout << lineCount << ": comment detected, nothing to do...." << std::endl;
      } else if(input[0]=="define" && input[1]=="shape") {
        if(input[2]=="box" && input.size() == 12) {
        std::cout << lineCount << ": box detected, going to parse..." << std::endl;

        // Box components
        glm::vec3 min{std::stod(input[4]),std::stod(input[5]),std::stod(input[6])};
        glm::vec3 max{std::stod(input[7]),std::stod(input[8]),std::stod(input[9])};
        std::string name = input[3];
        auto iterator = scene->materials.find(input[10]);

        if(iterator == scene->materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to box and add it to composite
        std::shared_ptr<Shape> ptr = std::make_shared<Box>(min, max, iterator->second, name);
        scene->composite->add(ptr); //shitty code, muss aber irgendwie? =S


        } else if(input[2]=="sphere" && input.size() == 10) {
        std::cout << lineCount << ": sphere detected, going to parse..." << std::endl;

        // Sphere components
        glm::vec3 center{std::stod(input[4]), std::stod(input[5]), std::stod(input[6])};
        auto iterator = scene->materials.find(input[8]);

        if(iterator == scene->materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to Sphere and add it to composite  
        std::shared_ptr<Shape> ptr = std::make_shared<Sphere>(center, std::stod(input[7]), iterator->second, input[3]);
        scene->composite->add(ptr);
        
        } else if(input[2]=="triangle" && input.size() == 15) {
        std::cout << lineCount << ": triangle detected, going to parse..." << std::endl;

        // Triangle components
        glm::vec3 p1{std::stod(input[4]),std::stod(input[5]),std::stod(input[6])};
        glm::vec3 p2{std::stod(input[7]),std::stod(input[8]),std::stod(input[9])};
        glm::vec3 p3{std::stod(input[10]),std::stod(input[11]),std::stod(input[12])};
        auto iterator = scene->materials.find(input[13]);

        if(iterator == scene->materials.end()) {
          throw std::logic_error("No Material found. Cannot parse line " + lineCountStr);
        }

        // Make smart pointer to Triangle and add it to composite
        std::shared_ptr<Shape> ptr = std::make_shared<Triangle>(input[3], p1, p2, p3, iterator->second);
        scene->composite->add(ptr);

        } else if(input[2]=="composite") {
          std::cout << lineCount << ": composite detected, going to parse..." << std::endl;
  		    std::shared_ptr<Composite> tmpptr = std::make_shared<Composite>(Composite{ input[3] });

        for (int i = 4; i < input.size(); ++i)
        {
          auto iterator = scene->composite->get_children().find(input[i]);
          /*if(iterator == scene->composite->get_children().end()) {
              throw std::logic_error("Shape not found. cannot parse composite at line " + lineCountStr);
          }*/
          std::cout << lineCount << ": outside if" << std::endl;
          tmpptr->add(iterator->second);
          scene->composite->remove(input[i]);
          std::cout << lineCount << ": DEBUG for" << std::endl;
        }
        std::cout << lineCount << ": outside for-loop" << std::endl;

        std::shared_ptr<Shape> ptr = tmpptr;
        scene->composite->add(ptr);

        } else {
          throw std::logic_error("cannot parse shape at line " + lineCountStr);
        }


      } else if(input[0]=="define" && input[1]=="material"  && input.size() == 14) {
        std::cout << lineCount << ": material detected, going to parse..." << std::endl;

        // Material components
        Color ka = {std::stof(input[3]),std::stof(input[4]),std::stof(input[5])};
        Color kd = {std::stof(input[6]),std::stof(input[7]),std::stof(input[8])};
        Color ks = {std::stof(input[9]),std::stof(input[10]),std::stof(input[11])};

        scene->materials.insert(scene->materials.end(),std::pair<std::string,Material>(input[2],{input[2],ka,kd,ks,std::stof(input[12])}));
          

      } else if(input[0]=="define" && input[1]=="light") {
        if (input[2] == "ambient" && input.size() == 8) {
          std::cout << lineCount << ": ambient light detected, going to parse..." << std::endl;

          Color abs{std::stof(input[4]), std::stof(input[5]), std::stof(input[6])};
          scene->ambient_light = abs;
        } else if (input[2] == "diffuse" && input.size() == 11) {
          std::cout << lineCount << ": light detected, going to parse..." << std::endl;

          // Light components
          glm::vec3 pos{std::stof(input[4]), std::stof(input[5]), std::stof(input[6])};
          Color ld{std::stof(input[7]), std::stof(input[8]), std::stof(input[9])};
          
          scene->lights.insert(scene->lights.end(),std::pair<std::string, Light>(input[3],{input[3], pos,/*la,*/ld}));
        } else {
          throw std::logic_error("cannot parse light at line " + lineCountStr);
        }
      } else if(input[0]=="camera" && input.size() == 13) {
        std::cout << lineCount << ": camera detected, going to parse..." << std::endl;

        // Camera components
        glm::vec3 eye{std::stod(input[3]), std::stod(input[4]), std::stod(input[5])};
        glm::vec3 dir{std::stod(input[6]), std::stod(input[7]), std::stod(input[8])};
        glm::vec3 up{std::stod(input[9]), std::stod(input[10]), std::stod(input[11])};
        auto name = input[1];
        auto fov = std::stof(input[2]);
        Camera tmp{name, eye, dir, up, fov};
        scene->camera = tmp;
      } else {
        throw std::logic_error("cannot parse line " + lineCountStr);
      }
    }
  }
  return *scene;
}

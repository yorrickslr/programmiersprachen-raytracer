#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <sdfloader.cpp>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer app(width, height, filename);
  //Renderer app(scene) BS

/*
  Scene scene;
  scene.ambient_light = {100,100,100}; // muss aus dem SDF-FIle gelesen werden!
  std::ifstream file;
  file.open("input.sdf");
  if(!file.is_open()) {
    std::cout << "---ERROR--- file could not be found" << std::endl;
  }
  sdf_loadScene(file, scene); // Lieber mit Rückgabe, operator ist in scene schon drin
  scene.camera.setResolution(width, height); // ist okay, denk nochmal drüber nach
*/


  Scene scene;
  std::ifstream file;
  file.open("input.sdf");
  try {
    scene = nsdf_loadScene(file);
  } catch(std::exception& e) {
    std::cerr << "---ERROR--- SDF-loader: " << e.what() << std::endl;
  }
  scene.camera.setResolution(width, height); // ist okay, denk nochmal drüber nach
  scene.ambient_light = {100,100,100}; // muss aus dem SDF-FIle gelesen werden!
  

  std::thread thr([&app,&scene]() { app.render(scene, 2); });

  Window win(glm::ivec2(width,height));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( width, height, GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();
  return 0;
}

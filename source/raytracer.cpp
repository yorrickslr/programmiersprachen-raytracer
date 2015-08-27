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

  if(argc!=2) {
    std::cerr << "---ERROR--- no path to SDF-file given" << std::endl;
    return 0;
  }
  Scene scene;
  std::ifstream file;
  file.open(argv[1]);
  if(!file.is_open()) {
    std::cerr << "---ERROR--- no SDF-file found at " << argv[1] << std::endl;
    return 0;
  }

  try {
    scene = nsdf_loadScene(file);
  } catch(std::exception& e) {
    std::cerr << "---ERROR--- SDF-loader: " << e.what() << std::endl;
  }
  scene.camera.setResolution(width, height); // ist okay, denk nochmal drüber nach
  scene.background = Color{0,0,0};

  std::thread thr([&app,&scene]() { app.render(scene, 1); });

/*  // Debug
  Ray dbg_ray = {{0,0,0},{0,0,-1}};
  Hit dbg_hit = scene.composite->intersect(dbg_ray);
  std::cout << dbg_hit.intersection.x << " | " << dbg_hit.intersection.y << " | " << dbg_hit.intersection.z << std::endl;
  std::cout << dbg_hit.normal.x << " | " << dbg_hit.normal.y << " | " << dbg_hit.normal.z << std::endl;
  std::cout << glm::dot(dbg_hit.normal, dbg_ray.direction) << std::endl;
*/
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

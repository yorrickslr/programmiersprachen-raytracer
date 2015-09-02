#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <sdfloader.cpp>

int main(int argc, char* argv[])
{
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
    scene = loadScene(file);
  } catch(std::exception& e) {
    std::cerr << "---ERROR--- SDF-loader: " << e.what() << std::endl;
    return 0;
  }
  scene.background = Color{0,0,0};

  Renderer app{scene};

  std::thread thr([&app,&scene]() { app.render(scene, 2); });

  Window win(glm::ivec2(scene.camera->width(),scene.camera->height()));

  while (!win.shouldClose()) {
    if (win.isKeyPressed(GLFW_KEY_ESCAPE)) {
      win.stop();
    }

    glDrawPixels( scene.camera->width(), scene.camera->height(), GL_RGB, GL_FLOAT
                , app.colorbuffer().data());

    win.update();
  }

  thr.join();
  return 0;
}

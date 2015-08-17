#include <thread>
#include <renderer.hpp>
#include <fensterchen.hpp>
#include <sdfloader.hpp>

int main(int argc, char* argv[])
{
  unsigned const width = 600;
  unsigned const height = 600;
  std::string const filename = "./checkerboard.ppm";

  Renderer app(width, height, filename);
  Scene scene;
  std::ifstream file;
  file.open("input.sdf");
  if(!file.is_open()) {
    std::cout << "---ERROR--- file could not be found" << std::endl;
  }
  sdf_loadScene(file, scene);
  scene.camera.setResolution(width, height);
  std::cout << "***GRFJZ*** line 21" << std::endl;
  std::thread thr([&app,&scene]() { app.render(scene); });
  std::cout << "***GRJFZ*** line 23" << std::endl;

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

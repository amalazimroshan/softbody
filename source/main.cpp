
#include <chrono>
#include <softbody/engine.hpp>
#include <softbody/renderer.hpp>
#include <softbody/vector.hpp>
int main() {
  Renderer renderer;
  renderer = Renderer();
  softbody::engine engine;

  bool running = renderer.Setup();
  auto lastTime = std::chrono::high_resolution_clock::now();
  int mouse_x, mouse_y;

  // engine.add_point({400.0f, 100.0f});  // Center top
  // engine.add_point({300.0f, 200.0f});  // Left
  // engine.add_point({500.0f, 200.0f});  // Right

  while (running) {
    for (SDL_Event event; SDL_PollEvent(&event);) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_ESCAPE) running = false;
          if (event.key.keysym.sym == SDLK_UP)
            engine.gravity = {0.f, -981.f};
          else
            engine.gravity = {0.f, 981.f};
          break;
        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            mouse_x = event.button.x;
            mouse_y = event.button.y;

            engine.add_point(
                {static_cast<float>(mouse_x), static_cast<float>(mouse_y)});
          }

          break;
      }
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentTime - lastTime).count();
    // std::cout << dt << std::endl;
    lastTime = currentTime;

    engine.update(dt);
    renderer.ClearScreen(0xFF000816);

    // rendering
    using namespace softbody;

    renderer.DrawLine(0, 750, renderer.GetWindowWidth(), 750,
                      Renderer::RGB(255, 255, 255));

    const int point_radius = 20;
    for (const auto& point : engine.points) {
      renderer.DrawCircle(point.position, point_radius,
                          Renderer::RGB(255, 255, 0));
    }
    renderer.Render();
  }
  return 0;
}
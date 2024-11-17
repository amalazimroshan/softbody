
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
  softbody::Vector<float, 2> mouse_position;
  softbody::Vector<float, 2> mouse_prev_position;
  // softbody::point* selected_point = nullptr;
  // bool is_point_selected = false;

  // engine.add_point({400.0f, 100.0f});  // Center top
  // engine.add_point({300.0f, 200.0f});  // Left
  // engine.add_point({500.0f, 200.0f});  // Right
  using namespace softbody;
  while (running) {
    for (SDL_Event event; SDL_PollEvent(&event);) {
      switch (event.type) {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
              running = false;
              break;
            case SDLK_RIGHT:
              engine.gravity = {981.f, 0.f};
              break;
            case SDLK_LEFT:
              engine.gravity = {-981.f, 0.f};
              break;
            case SDLK_DOWN:
              engine.gravity = {0.f, 981.f};
              break;
            default:
              engine.gravity = {0.f, -981.f};
              break;
          }
          break;

        case SDL_MOUSEMOTION:
          mouse_position = {static_cast<float>(event.button.x),
                            static_cast<float>(event.button.y)};
          if (engine.is_point_selected)
            engine.selected_point->position = mouse_position;
          break;

        case SDL_MOUSEBUTTONDOWN:
          if (event.button.button == SDL_BUTTON_LEFT) {
            mouse_prev_position = mouse_position;
            for (auto& point : engine.points) {
              if (magnitude(point.position - mouse_position) <=
                  engine.point_radius) {
                engine.is_point_selected = true;
                engine.selected_point = &point;
                break;
              }
            }
            if (!engine.is_point_selected) engine.add_point(mouse_position);
          }
          break;
        case SDL_MOUSEBUTTONUP: {
          if (engine.is_point_selected) {
            Vector<float, 2> mouse_up_position = mouse_position;
            Vector<float, 2> velocity =
                (mouse_up_position - mouse_prev_position) * 5.f;
            engine.selected_point->velocity = velocity;
            engine.is_point_selected = false;
            engine.selected_point = nullptr;
          }
        } break;
      }
    }

    auto currentTime = std::chrono::high_resolution_clock::now();
    float dt = std::chrono::duration<float>(currentTime - lastTime).count();
    // std::cout << dt << std::endl;
    lastTime = currentTime;

    engine.update(dt);
    renderer.ClearScreen(0xFF000816);

    // rendering

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
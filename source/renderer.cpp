#include <iostream>
#include <softbody/renderer.hpp>

bool Renderer::Setup() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    std::cerr << "Error initializing SDL" << std::endl;
    return false;
  }

    // SDL_DisplayMode displayMode;
  // SDL_GetCurrentDisplayMode(0, &displayMode);
  windowWidth = 800;
  windowHeight = 800;

  window = SDL_CreateWindow("softbody", SDL_WINDOWPOS_UNDEFINED,
                            SDL_WINDOWPOS_UNDEFINED, windowWidth, windowHeight,
                            SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN);
  if (!window) {
    std::cerr << "Error initializing SDL window" << std::endl;
    return false;
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    std::cerr << "Error initializing SDL renderer" << std::endl;
    return false;
  }

  return true;
}

void Renderer::ClearScreen(Uint32 color) const {
  SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
  SDL_RenderClear(renderer);
}

void Renderer::Render() const { SDL_RenderPresent(renderer); }

void Renderer::DrawLine(int x0, int y0, int x1, int y1, Uint32 color) const {
  SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
  SDL_RenderDrawLine(renderer, x0, y0, x1, y1);
}

void Renderer::DrawPoint(int x, int y, Uint32 color) const {
  SDL_SetRenderDrawColor(renderer, color >> 16, color >> 8, color, 255);
  SDL_RenderDrawPoint(renderer, x, y);
}

using namespace softbody;
void Renderer::DrawCircle(Vector<float, 2> center, int radius,
                          Uint32 color) const {
  Uint8 r = (color >> 16) & 0xFF;
  Uint8 g = (color >> 8) & 0xFF;
  Uint8 b = color & 0xFF;

  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  int x = radius;
  int y = 0;
  int err = 0;

  while (x >= y) {
    SDL_RenderDrawPoint(renderer, center.x + x, center.y + y);
    SDL_RenderDrawPoint(renderer, center.x + y, center.y + x);
    SDL_RenderDrawPoint(renderer, center.x - y, center.y + x);
    SDL_RenderDrawPoint(renderer, center.x - x, center.y + y);
    SDL_RenderDrawPoint(renderer, center.x - x, center.y - y);
    SDL_RenderDrawPoint(renderer, center.x - y, center.y - x);
    SDL_RenderDrawPoint(renderer, center.x + y, center.y - x);
    SDL_RenderDrawPoint(renderer, center.x + x, center.y - y);

    y += 1;
    if (err <= 0) {
      err += 2 * y + 1;
    }
    if (err > 0) {
      x -= 1;
      err -= 2 * x + 1;
    }
  }
}

Renderer::~Renderer() {
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}
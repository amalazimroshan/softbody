#pragma once

#include <SDL2/SDL.h>

#include <softbody/vector.hpp>

class Renderer {
 private:
  int windowWidth, windowHeight;
  SDL_Window* window;
  SDL_Renderer* renderer;

 public:
  Renderer() = default;
  ~Renderer();

  int GetWindowWidth() const { return windowWidth; }
  int GetWindowHeight() const { return windowHeight; }

  bool Setup();

  static Uint32 RGB(Uint8 r, Uint8 g, Uint8 b) {
    return (r << 16) | (g << 8) | b;
  }

  void ClearScreen(Uint32 color) const;
  void Render() const;

  void DrawLine(int x0, int y0, int x1, int y1, Uint32 color) const;
  void DrawPoint(int x, int y, Uint32 color) const;

  void DrawCircle(softbody::Vector<float, 2> center, int radius,
                  Uint32 color) const;
};
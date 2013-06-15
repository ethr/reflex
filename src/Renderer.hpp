#ifndef REFLEXGAME_RENDERER
#define REFLEXGAME_RENDERER

#include <cmath>
#include "SDL.h"
#include "SDL_ttf.h"
#include "GameState.hpp"

namespace reflexgame {

  class Renderer {
    public:
      explicit Renderer(SDL_Surface* surface);
      ~Renderer();

      // TMP
      void draw(const GameState& gs);

      void drawEndGame(const GameState& gs);

      //void renderScene(const GameManager& scene);
    private:
      SDL_Surface* surface_;
      TTF_Font* font_;
      SDL_Surface* crosshair_;
      Renderer(const Renderer&);
      Renderer& operator=(const Renderer &);
  };
}

#endif

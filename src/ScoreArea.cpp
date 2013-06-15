#include <ctime>
#include "SDL.h"
#include "ScoreArea.hpp"

namespace reflexgame {

  ScoreArea::ScoreArea(int x, int y) : x_(x), y_(y),
  creationTime_(SDL_GetTicks()) {}

  int ScoreArea::getX() const {
    return x_;
  }

  int ScoreArea::getY() const {
    return y_;
  }

  Uint32 ScoreArea::getCreationTime() const {
    return creationTime_;
  }

}

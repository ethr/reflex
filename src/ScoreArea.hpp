#ifndef REFLEXGAME_SCOREAREA_
#define REFLEXGAME_SCOREAREA_

#include "SDL.h"

namespace reflexgame {

  /// Represents a scoring area in the game
  class ScoreArea {
    public:
      ScoreArea(int x, int y);

      Uint32 getCreationTime() const;
      int getX() const;
      int getY() const;

    private:
      ScoreArea(const ScoreArea&);
      ScoreArea& operator=(const ScoreArea&);
      
      int x_;
      int y_;
      Uint32 creationTime_;
  };

}

#endif

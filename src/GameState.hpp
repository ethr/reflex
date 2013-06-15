#ifndef REFLEXGAME_GAMESTATE
#define REFLEXGAME_GAMESTATE

#include <vector>
#include "SDL.h"
#include "ScoreArea.hpp"

using namespace std;

namespace reflexgame {

  class GameState {
    public:
      GameState(int width, int height);
      ~GameState();

      /// Returns a reference to the score areas list
      const vector<ScoreArea*>& getScoreAreasRef() const;
      int getScore() const;
      int getMisses() const;
      int getHits() const;
      double getAccuracy() const;
      int getRoundNumber() const;

      /// Handles an attack at the coordinates specified
      void attackAt(int x, int y);

      void handleTick();

      void start();
      Uint32 getStartTime() const;

      /// Returns true if the game is ended
      bool gameEnded() const;

    private:
      /// Adds a new score area in a random position
      void addScoreArea();

      void calcNextCircle();

      /// Ends the game, cleaning up and initalizing anything that needs
      /// to be passed to the driver of the game
      void endGame();

      bool gameEnded_;
      int width_;
      int height_;
      int score_;
      int misses_;
      int hits_;
      int roundNumber_;
      int lives_;
	    vector<ScoreArea*> scoreAreas_;
      Uint32 startTime_;
      Uint32 nextCircle_;
      Uint32 nextRound_;
      Uint32 nextCircleDeath_;

      GameState(const GameState&);
      GameState& operator=(const GameState &);
  };

}

#endif

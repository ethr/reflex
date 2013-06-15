#include <cmath>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "GameState.hpp"
#include "Utils.hpp"
#include "ScoreArea.hpp"
#include "Constants.hpp"

using namespace std;

namespace reflexgame {

  GameState::GameState(int width, int height) : gameEnded_(false), width_(width), height_(height), score_(0), misses_(0), hits_(0), roundNumber_(1), lives_(4) {}

  GameState::~GameState() {
    for (size_t i = 0; i < scoreAreas_.size(); i++) {
      delete scoreAreas_[i];
    }
  }

  int GameState::getRoundNumber() const {
    return roundNumber_;
  }

  const vector<ScoreArea*>& GameState::getScoreAreasRef() const {
    return scoreAreas_;
  }

  int GameState::getScore() const {
    return score_;
  }

  int GameState::getMisses() const {
    return misses_;
  }

  int GameState::getHits() const {
    return hits_;
  }

  Uint32 GameState::getStartTime() const {
    return startTime_;
  }

  void GameState::addScoreArea() {
    int x = rand() % (width_ - constants::SCOREAREA_MAX_RADIUS*2);
    int y = rand() % (height_ - constants::SCOREAREA_MAX_RADIUS*2);
    ScoreArea* sa = new ScoreArea(x + constants::SCOREAREA_MAX_RADIUS, y + constants::SCOREAREA_MAX_RADIUS);
    if (scoreAreas_.empty()) {
      nextCircleDeath_ = SDL_GetTicks() + constants::SCOREAREA_MAX_AGE;
    }
    scoreAreas_.push_back(sa);
  }

  void GameState::start() {
    startTime_ = SDL_GetTicks();
    nextRound_ = startTime_ + constants::ROUND_LENGTH;
    nextCircle_ = startTime_;
    calcNextCircle();
  }

  void GameState::calcNextCircle() {
    float rf = static_cast<float>(roundNumber_);
    //nextCircle_ += static_cast<int>(1000.0/(1.0+log((rf+1.0)/(2.0/(1 + log(rf))))));
    nextCircle_ += static_cast<int>(1000.0/(1.0+log((rf+1.0)/2)));
  }

  void GameState::handleTick() {
    if (SDL_GetTicks() > nextRound_) {
      roundNumber_++;
      nextRound_ += constants::ROUND_LENGTH;
      lives_ = 4;
    }
    if (SDL_GetTicks() > nextCircle_) {
      addScoreArea();
      calcNextCircle();
    }
    if (SDL_GetTicks() > nextCircleDeath_) {
      size_t pos = -1;
      for (size_t i = 0; i < scoreAreas_.size(); i++) {
        ScoreArea* sa = scoreAreas_.at(i);
        Uint32 age = SDL_GetTicks() - sa->getCreationTime();
        if (age < constants::SCOREAREA_MAX_AGE) {
          pos = i;
          break;
        }
      }
      if (pos != -1) {
	      for (size_t i = 0; i < pos; i++) {
          ScoreArea* sa = scoreAreas_.at(0);
		      scoreAreas_.erase(scoreAreas_.begin());
          lives_--;
          delete sa;
        } 
      }
    }
    if (lives_ == 0) {
      endGame();
    }
  }

  void GameState::attackAt(int x, int y) {
    vector<ScoreArea*>::iterator it = scoreAreas_.begin();
    for (; it != scoreAreas_.end(); it++) {
      ScoreArea* sa = *it;
      Uint32 age = SDL_GetTicks() - sa->getCreationTime();
      float radius = static_cast<float>(util::ageToRadius(age));
      float saX = static_cast<float>(sa->getX());
      float saY = static_cast<float>(sa->getY());
      float xf = static_cast<float>(x);
      float yf = static_cast<float>(y);
      float df = sqrt(pow(saX-xf, 2) + pow(saY - yf, 2));
      if (df < radius) {
        ScoreArea* sa = *it;
        scoreAreas_.erase(it);
        Uint32 bonus = static_cast<Uint32>(constants::MAX_ACC_BONUS*(1 - (df/radius)));
	      score_ += constants::HIT_SCORE + bonus;
	      hits_++;
        delete sa;
        return;
      }
    }
		misses_++;
    score_ -= constants::MISS_PUNISHMENT;
  }

  void GameState::endGame() {
    gameEnded_ = true;
  }

  bool GameState::gameEnded() const {
    return gameEnded_;
  }
}

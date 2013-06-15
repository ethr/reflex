#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace constants {

  /// Maxium radius for a score area
  static const Uint32 SCOREAREA_MAX_RADIUS = 40;

  /// The number of ticks which a Score Area can exist for
  static const Uint32 SCOREAREA_MAX_AGE = 3000;
  static const Uint32 SCOREAREA_HALF_LIFE = SCOREAREA_MAX_AGE/2;

  /// Round length in milliseconds
  static const Uint32 ROUND_LENGTH = 15000;

  /// Scoring
  static const Uint32 HIT_SCORE = 100;
  static const Uint32 MISS_PUNISHMENT = 4000;
  static const float MAX_ACC_BONUS = 150.0;

}

#endif
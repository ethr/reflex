#include <cmath>
#include "SDL.h"
#include "Utils.hpp"
#include "Constants.hpp"

namespace reflexgame {
  namespace util {

    int ageToRadius(Uint32 age) {
        if (age == 0) {
          return 0;
        } else if (age > constants::SCOREAREA_MAX_AGE) {
          return 0;
        } else {
          return constants::SCOREAREA_MAX_RADIUS - ((age-constants::SCOREAREA_HALF_LIFE)*(age-constants::SCOREAREA_HALF_LIFE))/(56250);
        }
    }
  }
}

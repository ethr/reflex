#ifndef REFLEXGAME_UTIL
#define REFLEXGAME_UTIL

#include "SDL.h"

namespace reflexgame {
  namespace util {

    /// Returns the width if the circle based on its age
    int ageToRadius(Uint32 age);
  }
}

#endif

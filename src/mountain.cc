#include "mountain.h"

#include <stdlib.h>   /* srand, rand */
#include <time.h>     /* time */

#include <cmath>      /* pow */


// =============================================================================
// Private Functions
// =============================================================================

void Mountain::InitializeHeightmap() {
  for (std::size_t i = 0; i < Mountain::size; ++i) {
    std::vector<int> tempRow;
    for (std::size_t j = 0; j < Mountain::size; ++j) {
      tempRow.push_back(0);
    }
    Mountain::heightmap.push_back(tempRow);
  }
}


// =============================================================================
// Public Functions
// =============================================================================

Mountain::Mountain(size_t _size, int _seed = time(NULL)) {
  Mountain::size = pow(2.0, _size) + 1;
  Mountain::seed = _seed;
  Mountain::InitializeHeightmap();
}

Mountain::~Mountain() {}

void Mountain::Render() {}

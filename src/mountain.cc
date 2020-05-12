#include "mountain.h"

#include <stdlib.h>   /* srand, rand */
#include <time.h>     /* time */

#include <cmath>      /* pow */
#include <iostream>   /* cout */
#include <stdexcept>  /* domain_error */

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

void Mountain::PrintHeightmap() {
  for (size_t i = 0; i < Mountain::size; i++) {
    for (size_t j = 0; j < Mountain::size; j++) {
      std::cout << Mountain::heightmap[i][j] << " ";
    }
    std::cout << std::endl;
  }
}

// =============================================================================
// Private Functions
// =============================================================================

void Mountain::InitializeHeightmap() {
  for (std::size_t i = 0; i < Mountain::size; ++i) {
    std::vector<int> temp_row(Mountain::size);
    Mountain::heightmap.push_back(temp_row);
  }
}

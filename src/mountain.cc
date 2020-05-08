#include "./mountain.h"

#include <stdlib.h>   /* srand, rand */
#include <time.h>     /* time */

#include <cmath>      /* pow */


// =============================================================================
// Private Functions
// =============================================================================

void Mountain::InitializeHeightmap() {}


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

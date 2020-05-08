#ifndef MOUNTAINS_MOUNTAIN_H_
#define MOUNTAINS_MOUNTAIN_H_

#include <cstddef>    /* size_t */
#include <vector>     /* vector */

class Mountain {
 public:
  // Public Functions
  Mountain(std::size_t _size, int _seed);
  void Render();
  ~Mountain();

 private:
  // Private Variables
  std::size_t size;
  std::vector<std::vector<int>> heightmap = {};
  int seed;

  // Private Functions
  void InitializeHeightmap();
  void InitializeCorners();
};

#endif // MOUNTAINS_MOUNTAIN_H_

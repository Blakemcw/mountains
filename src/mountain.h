#pragma once

#include <cstddef>    /* size_t */
#include <vector>     /* vector */

using hmap = std::vector<std::vector<int>>;

class Mountain {
 public:
  Mountain(std::size_t _size, int _seed);
  ~Mountain();

  void Render();
  void PrintHeightmap();

  std::size_t GetSize() { return Mountain::size; }
  hmap GetHeightmap()   { return Mountain::heightmap; }

 private:
  void InitializeHeightmap();

  std::size_t size;
  std::vector<std::vector<int> > heightmap;
  int seed;
};

#pragma once

#include <cstddef>    /* size_t */
#include <vector>     /* vector */

class Mountain {
 public:
  Mountain(std::size_t _size, int _seed);
  ~Mountain();

  void Render();
  void PrintHeightmap();

  std::size_t GetSize() { return Mountain::size; }
  std::vector<std::vector<int> > GetHeightmap() { return Mountain::heightmap; }

 private:
  void InitializeHeightmap();
  void InitializeCorners();

  std::size_t size;
  std::vector<std::vector<int> > heightmap;
  int seed;
};

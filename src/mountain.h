#pragma once

#include <cstddef>    /* size_t */
#include <vector>     /* vector */

class Mountain {
 public:
  Mountain(std::size_t _size, int _seed);
  ~Mountain();

  void Render(void);
  void PrintHeightmap();

  std::size_t GetSize() { return Mountain::size; }
  std::vector<std::vector<int> > GetHeightmap() { return Mountain::heightmap; }

 private:
  // Initialization
  void InitializeHeightmap();
  void InitializeCorners();

  // Diamond-Square Algo
  void DiamondSquare();
  void DiamondSquare(int x0, int y0, int x1, int y1);

  // Diamond Step
  void DiamondStep(std::size_t corner_x, std::size_t corner_y,
                   std::size_t midpnt_x, std::size_t midpnt_y);

  // Square Step
  void SquareStep(std::size_t x0, std::size_t y0,
                  std::size_t x1, std::size_t y1);
  int  HandleWraparound(int component);

  std::size_t size;
  std::vector<std::vector<int> > heightmap;
  int seed;
};

// =============================================================================
// Helper Functions
// =============================================================================

int GetMeanOfCorners(int corners[4]);

// =============================================================================
// Heightmap Color Schemes
// =============================================================================

void PrimaryColors(float height);
void OrangeToAzure(float height);
void GreyScale(float height);

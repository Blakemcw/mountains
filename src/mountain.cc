#include "mountain.h"

#include <stdlib.h>   /* srand, rand */
#include <time.h>     /* time */
#include <GLUT/glut.h>

#include <cmath>      /* pow */
#include <iostream>   /* cout */
#include <stdexcept>  /* domain_error */
#include <algorithm>  /* max */

// =============================================================================
// Public Functions
// =============================================================================

Mountain::Mountain(size_t _size, int _seed = time(NULL)) {
  Mountain::size = pow(2.0, _size) + 1;
  Mountain::seed = _seed;
  Mountain::InitializeHeightmap();
  Mountain::InitializeCorners();
  Mountain::DiamondSquare();
}

Mountain::~Mountain() {}

void Mountain::Render() {
  glBegin(GL_QUADS);
  for (float i = 0; i < Mountain::size - 1; ++i) {
    for (float j = 1; j < Mountain::size; ++j) {
      std::vector<std::vector<float> > quad_corners = {
        {i,   static_cast<float>(Mountain::heightmap[  i][  j]),    j},
        {i,   static_cast<float>(Mountain::heightmap[  i][j-1]),  j-1},
        {i+1, static_cast<float>(Mountain::heightmap[i+1][j-1]),  j-1},
        {i+1, static_cast<float>(Mountain::heightmap[i+1][  j]),    j}
      };

      for (std::vector<float> corner : quad_corners) {
        PrimaryColors(corner[1] / size);
        glVertex3f(
          corner[0]/size,
          corner[1]/size,
          corner[2]/size);
      }
    }
  }
  glEnd();
}

void Mountain::PrintHeightmap() {
  for (size_t i = 0; i < Mountain::size; i++) {
    for (size_t j = 0; j < Mountain::size; j++) {
      printf("%5d", Mountain::heightmap[i][j]);
    }
    printf("\n");
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

void Mountain::InitializeCorners() {
  std::vector<int*> corners(4);
  corners[0] = &(heightmap[0][0]);           // top-left
  corners[1] = &(heightmap[0].back());       // top-right
  corners[2] = &(heightmap.back().back());   // bottom-right
  corners[3] = &(heightmap.back()[0]);       // bottom-left

  std::srand(seed);

  for (int* corner : corners) {
    *corner = std::rand() % size;
  }
}

// =============================================================================
// Diamond Square Algo
// =============================================================================

void Mountain::DiamondSquare() {
  int s = size - 1;
  DiamondSquare(0, 0, s, s);
}

void Mountain::DiamondSquare(int x0, int y0,
                             int x1, int y1) {
  if (std::abs(x1-x0) == 1 || std::abs(y1-y0) == 1) {
    return;
  }
  /**
   *            (x0,y0) - - - - - - (x1,y0)
   *              |          |          |
   *              |          |          |
   *              | - -(mid_x,mid_y)- - |
   *              |          |          |
   *              |          |          |
   *            (x0,y1) - - - - - - (x1,y1)
   * 
   * (x0, y0) is the top-left corner of the square and (x1, y1) is the
   * bottom-right corner of the currently selected square. The square is
   * 'selected' by dragging from the top left corner to the bottom right,
   * targeting everything contained between them.
   * 
   * For a description of Diamond-Square
   * @see https://en.wikipedia.org/wiki/Diamond-square_algorithm
   * 
   */

  DiamondStep(x0, y0, x1, y1);

  SquareStep(x0, y0, x0, y1);  // Left   Diamond
  SquareStep(x0, y0, x1, y0);  // Top    Diamond
  SquareStep(x1, y0, x1, y1);  // Right  Diamond
  SquareStep(x0, y1, x1, y1);  // Bottom Diamond

  // Midpoint of square
  int mid_x = (x0 + x1) / 2;
  int mid_y = (y0 + y1) / 2;

  // Compute the ds algo on each of the 4 quadrants in (x0,y0)->(x1,y1) square
  DiamondSquare(x0, y0, mid_x, mid_y);  // Top    left  square
  DiamondSquare(mid_x, y0, x1, mid_y);  // Top    right square
  DiamondSquare(x0, mid_y, mid_x, y1);  // Bottom left  square
  DiamondSquare(mid_x, mid_y, x1, y1);  // Bottom right square
}

void Mountain::DiamondStep(std::size_t x0, std::size_t y0,
                           std::size_t x1, std::size_t y1) {
  // Calculate corners between two points that are diagonal to each other
  int corners[4] = {
    heightmap[y0][x0],
    heightmap[y0][x1],
    heightmap[y1][x0],
    heightmap[y1][x1]
  };

  int rand_range = std::max(static_cast<int>(x1 - x0)/2, 1);
  int midpoint_val = GetMeanOfCorners(corners);
  midpoint_val += std::rand() % (2 * rand_range) + (-rand_range);

  heightmap[(x0 + x1)/2][(y0+y1)/2] = midpoint_val;
}

void Mountain::SquareStep(std::size_t x0, std::size_t y0,
                          std::size_t x1, std::size_t y1) {
  int mid_x = (x0 + x1)/2;
  int mid_y = (y0 + y1)/2;

  int distance_to_center;
  int rand_range;
  int corners[4];
  corners[0] = heightmap[y0][x0];
  corners[1] = heightmap[y1][x1];

  bool points_are_on_vertical_side = x0 == x1;
  if (points_are_on_vertical_side) {
    distance_to_center = std::abs(static_cast<int>(mid_y - y0));
    rand_range = std::max(static_cast<int>(y1 - y0)/2, 1);
    corners[2] = heightmap[mid_y][HandleWraparound(mid_x - distance_to_center)];
    corners[3] = heightmap[mid_y][HandleWraparound(mid_x + distance_to_center)];
  } else {
    distance_to_center = std::abs(static_cast<int>(mid_x - x0));
    rand_range = std::max(static_cast<int>(x1 - x0)/2, 1);
    corners[2] = heightmap[HandleWraparound(mid_y - distance_to_center)][mid_x];
    corners[3] = heightmap[HandleWraparound(mid_y + distance_to_center)][mid_x];
  }

  int midpoint_val = GetMeanOfCorners(corners);
  midpoint_val += std::rand() % (2 * rand_range) + (-rand_range);

  heightmap[mid_y][mid_x] = midpoint_val;
}

int Mountain::HandleWraparound(int component) {
  /**
   * Handle wrap around for a component in a coordinate (x, y).
   * If a component is out of range of the heightmap, wrap around the heightmap.
   */
  if (component > (size-1)) {
    return 0;
  } else if (component < 0) {
    return size - 1;
  } else {
    return component;
  }
}

// =============================================================================
// Helper Functions
// =============================================================================

int GetMeanOfCorners(int corners[4]) {
  // Get sum of corners
  int sum = 0;
  int non_zero_nums = 0;
  for (int i = 0; i < 4; ++i) {
    if (corners[i] != 0) {
      ++non_zero_nums;
      sum += corners[i];
    }
  }

  // Calculate mean of the 4 corners, excluding zero-items
  if (non_zero_nums) {
    return sum / non_zero_nums;
  } else {
    return 0;
  }
}

// =============================================================================
// Heightmap Color Schemes
// =============================================================================

void PrimaryColors(float height) {
  glColor3f(
    std::cos((height - 1.0/6.0) * M_PI),
    std::cos((height - 3.0/6.0) * M_PI),
    std::cos((height - 5.0/6.0) * M_PI));
}

void OrangeToAzure(float height) {
  glColor3f(
    std::pow(std::cos((height - 0)   * M_PI / 2), 2),
    std::pow(std::cos((height - 1/2) * M_PI / 2), 2),
    std::pow(std::cos((height - 1)   * M_PI / 2), 2));
}

void GreyScale(float height) {
  glColor3f(
    height,
    height,
    height);
}

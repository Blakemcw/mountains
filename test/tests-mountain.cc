#include "../src/mountain.h"

#include <vector>
#include <iostream>

#include "catch.h"

TEST_CASE("heightmap is initialized", "[mountain][heightmap]") {
  std::size_t mountain_size = 5;
  int seed = 10;
  Mountain mountain = Mountain(mountain_size, seed);

  std::vector<std::vector<int> > heightmap = mountain.GetHeightmap();

  SECTION("the number of rows and columns is equal to 2^size + 1") {
    // Check row size
    REQUIRE(heightmap.size() == pow(2, mountain_size) + 1);

    // Check column size
    REQUIRE(heightmap[0].size() == pow(2, mountain_size) + 1);
  }

  SECTION("the number of rows and columns in the heightmap is odd") {
    // Check rows
    REQUIRE(heightmap.size() % 2 >= 1);

    // Check columns
    REQUIRE(heightmap[0].size() % 2 >= 1);
  }
}

TEST_CASE("heightmap corners are initialized", "[mountain][heightmap]") {
  std::size_t mountain_size = 5;
  int seed = 10;
  Mountain mountain = Mountain(mountain_size, seed);

  // Get corners from mountain
  std::vector<int> corners(4);
  corners[0] = mountain.GetHeightmap()[0][0];           // top-left
  corners[1] = mountain.GetHeightmap()[0].back();       // top-right
  corners[2] = mountain.GetHeightmap().back()[0];       // bottom-left
  corners[3] = mountain.GetHeightmap().back().back();   // bottom-right

  SECTION("all corners are set to values greater than 0") {
    for (int corner : corners) {
      REQUIRE(corner > 0);
    }
  }
}

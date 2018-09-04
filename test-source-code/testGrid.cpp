#include "Grid.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("The Grid's width and height are initialized with default values and be retrieved properly"){

    Grid testGrid{};

    CHECK(testGrid.getWidth()==800);
    CHECK(testGrid.getHeight()==600);
}

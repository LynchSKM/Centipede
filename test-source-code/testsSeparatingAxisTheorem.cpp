#include "SeparatingAxisTheorem.h"
#include "Rectangle.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


//
TEST_CASE("Separating Axes Theorem detects overlap between two Rectangles.")
{

    struct Rectangle rectA{};
    rectA.upperLeft   = Position(6, 8);
    rectA.bottomLeft  = Position(6, 6);
    rectA.upperRight  = Position(10, 8);
    rectA.bottomRight = Position(10, 6);

    struct Rectangle rectB;
    rectB.upperLeft   = Position(9, 4);
    rectB.bottomLeft  = Position(9, 7);
    rectB.upperRight  = Position(11, 4);
    rectB.bottomRight = Position(11, 7);

    SeparatingAxisTheorem sat_algorithm{};

    CHECK(sat_algorithm.checkOverlap(rectA, rectB));
}

TEST_CASE("Separating Axes Theorem detects no overlap between two Rectangles.")
{

    struct Rectangle rectA{};
    rectA.upperLeft   = Position(6, 8);
    rectA.bottomLeft  = Position(6, 6);
    rectA.upperRight  = Position(10, 8);
    rectA.bottomRight = Position(10, 6);

    struct Rectangle rectB;
    rectB.upperLeft   = Position(12, 4);
    rectB.bottomLeft  = Position(12, 6);
    rectB.upperRight  = Position(15, 4);
    rectB.bottomRight = Position(15, 6);

    SeparatingAxisTheorem sat_algorithm{};

    CHECK_FALSE(sat_algorithm.checkOverlap(rectA, rectB));
}


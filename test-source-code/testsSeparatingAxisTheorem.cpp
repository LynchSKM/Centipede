#include "SeparatingAxisTheorem.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Separating Axes Theorem detects overlap between two Rectangles.")
{

    auto width  = 30.0f;
    auto height = 40.0f;
    auto rotationAngle = 0.0f;

    Position center1{325.0f, 480.0f};
    BoundaryBox rectA{center1, width, height, rotationAngle};

    Position center2(326.0f, 485.0f);
    BoundaryBox rectB(center2, width, height, rotationAngle);

    SeparatingAxisTheorem sat_algorithm{};

    CHECK(sat_algorithm.checkOverlap(rectA, rectB));
}

TEST_CASE("Separating Axes Theorem detects no overlap between two Rectangles.")
{
    auto width = 30;
    auto height = 40;
    auto rotationAngle = 0.0f;
    Position center1(325.0f, 480.0f);
    BoundaryBox rectA(center1, width, height, rotationAngle);

    Position center2(100.0f, 100.0f);
    BoundaryBox rectB(center2, width, height, rotationAngle);

    SeparatingAxisTheorem sat_algorithm{};

    CHECK_FALSE(sat_algorithm.checkOverlap(rectA, rectB));
}

TEST_CASE("Separating Axes Theorem returns correct penetration distance.")
{

    auto width  = 30.0f;
    auto height = 40.0f;
    auto rotationAngle = 0.0f;

    Position center1{325.0f, 480.0f};
    BoundaryBox rectA{center1, width, height, rotationAngle};

    Position center2(352.0f, 480.0f);
    BoundaryBox rectB(center2, width, height, rotationAngle);

    SeparatingAxisTheorem sat_algorithm{};

    CHECK(sat_algorithm.checkOverlap(rectA, rectB));
    auto penetration_dist = sat_algorithm.getPenetrationDistance(center1, center2);

    CHECK(penetration_dist == Position{-3.0f, 0.0f});
}

#include "POSITION.H"

//#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Position x and y can be set and retrieved"){

    Position testPosition{};
    auto xPos = 5.8f;
    auto yPos = 0.8f;

    testPosition.setX_pos(xPos);
    testPosition.setY_pos(yPos);

    CHECK(testPosition.getX_pos() == xPos);
    CHECK(testPosition.getY_pos() == yPos);
}

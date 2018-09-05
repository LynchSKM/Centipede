#include "POSITION.H"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Position x and y can be set and retrieved"){

    Position testPosition{5.8f, 0.8f};
    auto xPos = 5.8f;
    auto yPos = 0.8f;

    CHECK(testPosition.getX_pos() == xPos);
    CHECK(testPosition.getY_pos() == yPos);
}


TEST_CASE("Positions can be checked for equality successfully"){

    Position testPosition{5.8f, 0.8f};
    Position testPosition2{5.8f, 0.8f};

    CHECK(testPosition == testPosition2);
}

TEST_CASE("Two Positions can be subtracted."){

    Position positionA{10.0,10.0};
    Position positionB{5.0,5.0};
    auto xPos = 5.0f;
    auto yPos = 5.0f;

    auto positionC = positionA-positionB;

    CHECK(positionC.getX_pos() == xPos);
    CHECK(positionC.getY_pos() == yPos);
}

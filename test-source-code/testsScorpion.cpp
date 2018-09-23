#include "Scorpion.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Scorpion can be created at a specified position, facing the given Direction"){

    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid, Position(24.0,56.0),Direction::RIGHT);

    CHECK(testScorpion.getPosition() == Position(24.0,56.0));
    CHECK(testScorpion.getDirection() == Direction::RIGHT);
}

TEST_CASE("Scorpion can move in the given Direction"){

    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid, Position(24.0,56.0),Direction::RIGHT);

    struct ScorpionDimensions dimensions;

    auto x = testScorpion.getPosition().getX_pos() + (2.0f*dimensions.speed);
    auto y = testScorpion.getPosition().getY_pos();

    testScorpion.move();
    testScorpion.move();

    CHECK(testScorpion.getPosition() == Position(x,y));
}

TEST_CASE("Scorpion gets eliminated when it goes out of boundary"){

    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid, Position(575.5,56.0),Direction::RIGHT);

    testScorpion.move();
    testScorpion.move();

    CHECK(!testScorpion.isAlive());
}

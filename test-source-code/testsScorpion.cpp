#include "Scorpion.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Scorpion can be created at a random position in its allocated range"){
    srand(time(0));
    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid);
    struct ScorpionDimensions dimensions;
    auto maxRow = 25.0f;
    auto minRow = 10.0f;

    auto maxY = round(maxRow*16.0f +24.0f);
    auto minY = round(minRow*16.0f +24.0f);

    auto minX = dimensions.width/2.0f + 1.0f;
    auto maxX = testGrid.getWidth()-(dimensions.width/2.0f + 1.0f);

    bool isInXRange = testScorpion.getPosition().getX_pos() == minX
                     || testScorpion.getPosition().getX_pos() == maxX;
    bool isInYRange = testScorpion.getPosition().getY_pos() >= minY
                     && testScorpion.getPosition().getY_pos() <= maxY;

    CHECK(isInXRange);
    CHECK(isInYRange);
    if(testScorpion.getPosition().getX_pos() == minX)
        CHECK(testScorpion.getDirection()==Direction::RIGHT);
    else CHECK(testScorpion.getDirection()==Direction::LEFT);
}

TEST_CASE("Scorpion can move in a Direction"){

    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid);
    struct ScorpionDimensions dimensions;

    auto x = testScorpion.getPosition().getX_pos();
    if(testScorpion.getDirection()==Direction::RIGHT)
        x+=(2.0f*dimensions.speed);
    else x-=(2.0f*dimensions.speed);

    auto y = testScorpion.getPosition().getY_pos();

    testScorpion.move();
    testScorpion.move();

    CHECK(testScorpion.getPosition() == Position(x,y));
}

TEST_CASE("Scorpion gets eliminated when it goes out of boundary"){

    Grid testGrid{592,640};
    Scorpion testScorpion(testGrid);
    struct ScorpionDimensions dimensions;

    auto minX = dimensions.width/2.0f + 1.0f;

    auto moves_to_be_made = testScorpion.getPosition().getX_pos();
    if(testScorpion.getPosition().getX_pos() == minX)
    {
        testScorpion.setDirection(Direction::LEFT);
    }
    else
    {
        testScorpion.setDirection(Direction::RIGHT);
        moves_to_be_made -= testGrid.getWidth();
    }

    moves_to_be_made = std::abs(moves_to_be_made);
    moves_to_be_made /= dimensions.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        testScorpion.move();
    }
    CHECK(!testScorpion.isAlive());
}

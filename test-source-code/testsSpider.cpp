#include "Spider.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Spider can be created at a random position in its allocated range")
{

    Grid testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;


    bool israndom = (testSpider.getPosition()==
                    Position(testGrid.getWidth()-(dimensions.width/2.0f + 1.0f),
                             testGrid.getHeight()- testGrid.getHeight()*0.2f)) ||
                    (testSpider.getPosition()==
                    Position(dimensions.width/2.0f + 1.0f),
                             testGrid.getHeight()- testGrid.getHeight()*0.2f);
    bool directionIsRandom = (testSpider.getDirection() == Direction::LEFT) ||
                             (testSpider.getDirection() == Direction::RIGHT);

    CHECK(israndom);
    CHECK(directionIsRandom);
}

TEST_CASE("Spider can move in a Direction"){

    Grid testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;

    auto initiaPos = testSpider.getPosition();

    testSpider.move();
    testSpider.move();

    CHECK_FALSE(testSpider.getPosition() == initiaPos);
}

TEST_CASE("Spider can be eliminated"){

    Grid testGrid{592,640};
    Spider testSpider(testGrid);
    struct SpiderDimensions dimensions;

    testSpider.eliminated();


    CHECK_FALSE(testSpider.isAlive());
}

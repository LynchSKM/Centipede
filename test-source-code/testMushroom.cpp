#include "Mushroom.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Mushroom can be created at a specified position."){

    Mushroom testMushroom(Position(8.0f, 24.0f));

    CHECK(testMushroom.getPosition()==Position(8.0f, 24.0f));

}

TEST_CASE("Mushroom's number of lives can be decreased and retrieved."){

    Mushroom testMushroom(Position(8.0f, 24.0f));
    testMushroom.decrementLives();
    CHECK(testMushroom.getRemainingLives()==3);

}

TEST_CASE("Mushroom's dies after being shot 4 times"){

    Mushroom testMushroom(Position(8.0f, 24.0f));

    testMushroom.decrementLives();
    testMushroom.decrementLives();
    testMushroom.decrementLives();
    testMushroom.decrementLives();
    CHECK(!testMushroom.isAlive());

}

TEST_CASE("Mushroom can get poisoned."){

    Mushroom testMushroom(Position(8.0f, 24.0f));

    testMushroom.poison();
    CHECK(testMushroom.isPoisoned());

}

#include "MushroomFactory.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Mushrooms can be created."){

    Grid testGrid{592,648};
    MushroomFactory testMFactory{testGrid};

    auto mushrooms = testMFactory.generateMushrooms();

    CHECK(!mushrooms.empty());
}

TEST_CASE("A mushroom can be created at a specified position."){

    Grid testGrid{592,648};
    MushroomFactory testMFactory{testGrid};

    auto mushroom = testMFactory.generateAMushroom(Position(24.0f,24.0f));

    CHECK(mushroom->getPosition() == Position(24.0f,24.0f));
}

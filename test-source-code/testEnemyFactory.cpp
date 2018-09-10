#include "EnemyFactory.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Centipede segments can be created."){

    Grid testGrid{600,648};
    EnemyFactory testEFactory{testGrid};

    auto CentiSegments = testEFactory.generateNormalCentipede();

    CHECK(!CentiSegments.empty());
}

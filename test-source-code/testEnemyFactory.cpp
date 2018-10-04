#include "EnemyFactory.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Centipede segments can be created.")
{
    Grid testGrid{600,648};
    EnemyFactory testEFactory{testGrid};

    auto CentiSegments = testEFactory.generateNormalCentipede();

    CHECK_FALSE(CentiSegments.empty());
}

TEST_CASE("A scorpion can be created.")
{
    Grid testGrid{592,640};
    EnemyFactory testEFactory{testGrid};

    auto scorpions  = testEFactory.generateAScorpion();

    CHECK_FALSE(scorpions.empty());
}

TEST_CASE("A Spider can be created.")
{
    Grid testGrid{592,640};
    EnemyFactory testEFactory{testGrid};
    auto delay = 0.0;
    testEFactory.setSpiderReleaseTime(delay);
    auto spider  = testEFactory.generateASpider();

    CHECK_FALSE(spider.empty());
}

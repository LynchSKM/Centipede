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

TEST_CASE("A Spider is not created before the delay time elapses.")
{
    Grid testGrid{592,640};
    EnemyFactory testEFactory{testGrid};
    auto delay = 15.0;
    testEFactory.setSpiderReleaseTime(delay);

    StopWatch testStopWatch{};
    testStopWatch.start();

    auto stop_watch_delay = 2.0;

    //Add delay
    while(true)
    {
        testStopWatch.pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>stop_watch_delay) break;
        testStopWatch.resume();
    }

    auto spider  = testEFactory.generateASpider();
    CHECK(spider.empty());
}

TEST_CASE("Centipede Heads can be created.")
{
    Grid testGrid{592,640};
    EnemyFactory testEFactory{testGrid};
    auto delay = 0.0;
    auto number_of_heads = 2;

    testEFactory.setCentipedeHeadsReleaseTime(delay);
    auto centipedeHeads  = testEFactory.generateCentipedeHeads(number_of_heads);

    CHECK_FALSE(centipedeHeads.empty());
}

TEST_CASE("Centipede Heads are not created before the delay time elapses.")
{
    Grid testGrid{592,640};
    EnemyFactory testEFactory{testGrid};
    auto delay = 15.0;
    auto number_of_heads = 2;
    testEFactory.setCentipedeHeadsReleaseTime(delay);

    StopWatch testStopWatch{};
    testStopWatch.start();

    auto stop_watch_delay = 2.0;

    //Add delay
    while(true)
    {
        testStopWatch.pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>stop_watch_delay) break;
        testStopWatch.resume();
    }

    auto centipedeHeads  = testEFactory.generateCentipedeHeads(number_of_heads);
    CHECK(centipedeHeads.empty());
}

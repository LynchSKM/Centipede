#include "Weapon.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("A Player Bullet is successfully generated at a position.")
{
    Grid testGrid{592, 640};
    Weapon testWeapon{};
    StopWatch testStopWatch{};
    testStopWatch.start();

    auto delay = 2.0*testWeapon.getReloadTime();

    //Add delay
    while(true)
    {
        testStopWatch.pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>delay) break;
        testStopWatch.resume();
    }

    auto bullet = testWeapon.fire(testGrid, Position{325, 400});
    CHECK_FALSE(bullet.empty());
    CHECK(bullet.at(0)->getPosition() == Position{325, 400});
}

TEST_CASE("A Player Bullet is not generated before reload time elapses.")
{
    Grid testGrid{592, 640};
    Weapon testWeapon{};
    StopWatch testStopWatch{};
    testStopWatch.start();

    auto delay = 0.1;

    //Add delay
    while(true)
    {
        testStopWatch.pause();
        auto time_elapsed = testStopWatch.getPauseTime();
        if(time_elapsed>delay) break;
        testStopWatch.resume();
    }

    auto bullet = testWeapon.fire(testGrid, Position{325, 400});
    CHECK(bullet.empty());
}

TEST_CASE("Weapon can be upgraded.")
{
    Grid testGrid{592, 640};
    Weapon testWeapon{};
    auto reload_time = testWeapon.getReloadTime();
    testWeapon.upgradeWeapon();

    CHECK(testWeapon.getReloadTime() < reload_time);
}

#include "PlayerBullet.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Bullet is created at the right position."){

    Grid testGrid{650,600};
    PlayerBullet testBullet{Position{325.0f,580.0f}, testGrid};

    CHECK(testBullet.getPosition() == Position{325.0f,580.0f});
}

TEST_CASE("Bullet can move"){

    Grid testGrid{650,600};
    PlayerBullet testBullet{Position{325.0f,580.0f}, testGrid};

    testBullet.move();
    testBullet.move();
    CHECK(testBullet.getPosition() == Position{325.0f,548.0f});
}

TEST_CASE("Bullet is not alive outside the grid"){

    Grid testGrid{650,600};
    PlayerBullet testBullet{Position{325.0f,10.0f}, testGrid};

    testBullet.move();
    CHECK_FALSE(testBullet.isAlive());
}

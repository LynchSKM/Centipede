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
    struct PlayerBulletDimensions dimensions_bullet;
    auto x_pos = testBullet.getPosition().getX_pos();
    auto y_pos = testBullet.getPosition().getY_pos()-(2.0f*dimensions_bullet.speed);

    testBullet.move();
    testBullet.move();

    CHECK(x_pos == doctest::Approx(testBullet.getPosition().getX_pos()));
    CHECK(y_pos == doctest::Approx(testBullet.getPosition().getY_pos()));
}

TEST_CASE("Bullet is not alive outside the grid"){

    Grid testGrid{650,600};
    PlayerBullet testBullet{Position{325.0f,8.2f}, testGrid};

    testBullet.move();
    CHECK_FALSE(testBullet.isAlive());
}

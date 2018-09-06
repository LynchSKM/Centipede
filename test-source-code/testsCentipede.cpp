#include "Centipede.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>


TEST_CASE("Centipede is placed at the right position."){

    Grid testGrid{650,600};
    Centipede centipede(Direction::DOWN, Centipede::BodyType::HEAD, ObjectType::CENTIPEDE,Position{325.0f,580.0f},testGrid);

    CHECK(centipede.getPosition() == Position{325.0f,580.0f});
}

TEST_CASE("Centipede can be moved up, down, left and right."){

    Grid testGrid{650,600};
    Centipede centipede(Direction::DOWN, Centipede::BodyType::HEAD, ObjectType::CENTIPEDE,Position{325.0f,300.0f},testGrid);
    centipede.move();

    CHECK(centipede.getPosition() == Position{325.0f,305.0f});

    centipede.move();
    CHECK(centipede.getPosition() == Position{320.0f,305.0f});

    centipede.changeDirection();
    centipede.move();
    CHECK(centipede.getPosition() == Position{320.0f,310.0f});

    centipede.move();
    CHECK(centipede.getPosition() == Position{325.0f,310.0f});
}

TEST_CASE("Centipede move down when poisoned."){

    Grid testGrid{650,600};
    Centipede centipede(Direction::LEFT, Centipede::BodyType::HEAD, ObjectType::CENTIPEDE,Position{325.0f,300.0f},testGrid);

    centipede.poison();
    centipede.move();
    centipede.move();
    CHECK(centipede.getPosition() == Position{325.0f,310.0f});
}

TEST_CASE("Centipede turns when it hits the screen boundary."){

    Grid testGrid{650,600};
    Centipede centipede(Direction::RIGHT, Centipede::BodyType::HEAD, ObjectType::CENTIPEDE,Position{645.0f,300.0f},testGrid);

    centipede.move();
    centipede.move();
    CHECK(centipede.getPosition() == Position{640.0f,305.0f});
    CHECK(centipede.getDirection()== Direction::LEFT);
}


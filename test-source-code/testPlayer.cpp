#include "Player.h"
#include "POSITION.H"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Player placed at the right position"){

    Grid testGrid{650,600};
    Player testPlayer{testGrid};
    struct PlayerDimension playerDimension;

    Position playerPosition{325.0f,600.0f-playerDimension.height*0.5f};

    CHECK(playerPosition == testPlayer.getPosition());
}

TEST_CASE("Player's score can be increased and retrieved"){

    Grid testGrid{650,600};
    Player testPlayer{testGrid};

    testPlayer.addScore(50);
    testPlayer.addScore(55);

    CHECK(testPlayer.getScore() == 105);

}

TEST_CASE("Player's lives can be decreased, retrieved and knows if it's alive"){

    Grid testGrid{650,600};
    Player testPlayer{testGrid};
    auto numberOfLives = testPlayer.getRemainingLives();
    // Player initially has 3 lives;
    testPlayer.eliminated();
    testPlayer.reincarnate();

    CHECK(testPlayer.getRemainingLives() == (numberOfLives-1));
    CHECK(testPlayer.isAlive());

}

TEST_CASE("Player's knows its new Position after being moved, and knows its type"){

    Grid testGrid{650,600};
    Player testPlayer{testGrid};
    struct PlayerDimension playerDimension;
    testPlayer.setDirection(Direction::UP);
    testPlayer.move();

    auto x_pos = testGrid.getWidth()/2.0f;
    auto y_pos = testGrid.getHeight()-(playerDimension.height*0.5f+playerDimension.speed);
    Position playerPosition{x_pos, y_pos};

    CHECK(playerPosition == testPlayer.getPosition());
    CHECK(testPlayer.getObjectType() == ObjectType::PLAYER);

}

TEST_CASE("Player's boundary box is constructed correctly"){

    Grid testGrid{650,600};
    Player testPlayer{testGrid};
    auto origin = testPlayer.getPosition();
    struct PlayerDimension dimesions_player;
    auto half_width  = dimesions_player.width/2.0f;
    auto half_height = dimesions_player.height/2.0f;

    // Order of points in vector
    // upperLeft
    // upperRight
    // bottomLeft
    // bottomRight
    auto x = origin.getX_pos();
    auto y = origin.getY_pos();
    vector<Position> rectA{Position{x-half_width,y-half_height}, Position{x+half_width,y-half_height},
                           Position{x-half_width, y+half_height}, Position{x+half_width,y+half_height}};

    auto playerRect = testPlayer.getBoundaryBox().getVertices();

    CHECK(rectA.at(0) == playerRect.at(0));
    CHECK(rectA.at(1) == playerRect.at(1));
    CHECK(rectA.at(2) == playerRect.at(2));
    CHECK(rectA.at(3) == playerRect.at(3));
}

TEST_CASE("Player can shoot"){

    Grid testGrid{650,600};
    StopWatch reloadTimer;
    Player testPlayer{testGrid};
    struct PlayerDimension playerDimension;

    Position playerPosition{325.0f,600.0f-playerDimension.height*0.5f};

    auto bullets = testPlayer.shoot();
    while(true)
    {
        bullets = testPlayer.shoot();
        if(!bullets.empty()) break;
    }

    CHECK(!bullets.empty());
}

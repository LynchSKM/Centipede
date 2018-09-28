#include "CollisionHandler.h"
#include "Mushroom.h"
#include "Player.h"
#include "Scorpion.h"

using std::make_shared;
using std::dynamic_pointer_cast;

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

// PLAYER BULLET COLLISIONS
TEST_CASE("Collision between PlayerBullet and Mushroom is detected")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct MushroomDimensions dimension_mushroom;
    struct PlayerBulletDimensions dimension_bullet;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;
    // Create mushrooms:
    auto mushroom1 = make_shared<Mushroom>(Position{100, 100});
    game_objects.push_back(mushroom1);
    auto mushroom2 = make_shared<Mushroom>(Position{100+dimension_mushroom.width, 100});
    game_objects.push_back(mushroom2);

    auto bullet = make_shared<PlayerBullet>(Position{100, 114}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    auto moves_to_be_made = bullet->getPosition().getY_pos();
    moves_to_be_made -= (mushroom1->getPosition().getY_pos()+(dimension_mushroom.width/2)-1);
    moves_to_be_made /= dimension_bullet.speed;

    for(auto moves_made = 0; moves_made<=moves_to_be_made; moves_made++)
    {
        bullet->move();
        collision_handler.checkCollisions(game_objects, moving_game_objects);
    }

    CHECK(mushroom1->getRemainingLives()==3);
    CHECK(mushroom2->getRemainingLives()==4);
    CHECK(collision_handler.getPointsObtained()==1);
    CHECK_FALSE(bullet->isAlive());
}

TEST_CASE("Collision between PlayerBullet and Centipede Head is detected and next Head is set")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{100,100}, Direction::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 4)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{100+counter,100}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto y_pos  = centipede_seg_ptr->getPosition().getY_pos()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(Position{100,y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    collision_handler.checkCollisions(game_objects, moving_game_objects);
    CHECK_FALSE(game_objects.at(0)->isAlive());
    CHECK_FALSE(bullet->isAlive());

    centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(game_objects.at(1));
    CHECK(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD);
}

TEST_CASE("Collision between PlayerBullet and Centipede Body is detected and next Head is set")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{100,100}, Direction::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 4)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{100+counter,100}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto x_pos  = centipede_seg_ptr->getPosition().getX_pos()+2.0f*(dimension_centipede.width+1);
    auto y_pos  = centipede_seg_ptr->getPosition().getY_pos()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(Position{x_pos, y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    collision_handler.checkCollisions(game_objects, moving_game_objects);

    CHECK_FALSE(game_objects.at(2)->isAlive());
    CHECK_FALSE(bullet->isAlive());
    CHECK(collision_handler.getPointsObtained()==100);

    centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(game_objects.at(3));
    CHECK(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD);
}

TEST_CASE("Collision between PlayerBullet and Centipede Body is detected while multiple Centipede heads are in game objects vector")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{100,100}, Direction::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{100+counter,100}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create PlayerBullet at position near head to cause overlap:
    auto x_pos  = centipede_seg_ptr->getPosition().getX_pos()+4.0f*(dimension_centipede.width+1);
    auto y_pos  = centipede_seg_ptr->getPosition().getY_pos()+dimension_centipede.height-1;
    auto bullet = make_shared<PlayerBullet>(Position{x_pos, y_pos}, grid);
    game_objects.push_back(bullet);
    moving_game_objects.push_back(bullet);

    // HEAD 2
    centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                  Position{100,300}, Direction::RIGHT);
    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                  Position{85,300}, Direction::RIGHT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);


    collision_handler.checkCollisions(game_objects, moving_game_objects);
    CHECK_FALSE(game_objects.at(4)->isAlive());
    CHECK_FALSE(bullet->isAlive());
    CHECK(collision_handler.getPointsObtained()==100);

    // Check that direction of last head is not changed.
    centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(game_objects.at(game_objects.size()-2));
    CHECK(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD);
    CHECK(centipede_seg_ptr->getDirection()== Direction::RIGHT);

    centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(game_objects.at(game_objects.size()-1));
    CHECK(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::BODY);
    CHECK(centipede_seg_ptr->getDirection()== Direction::RIGHT);
}

//
TEST_CASE("Collision between Centipede and Mushroom is detected")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    struct MushroomDimensions dimension_mushroom;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto x = 80.0f;
    auto y = 56.0f;
    auto centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{x, y}, Direction::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{x+counter, y}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while

    // Create Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<Mushroom>(Position{56.0f, y});
    game_objects.push_back(mushroom);

    auto centipede_tail_index = game_objects.size()-2;
    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_pos();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_pos()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.checkCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK(mushroom->isAlive());

    // Check if directions have changed:
    for(auto& object : moving_game_objects)
        CHECK(object->getDirection()==Direction::RIGHT);

}

TEST_CASE("Collision between Centipede and poisoned Mushroom is detected")
{
    const Grid grid{1920, 1080};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    struct MushroomDimensions dimension_mushroom;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto x = 71.3f;
    auto y = 56.0f;
    auto centipede_head_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{x, y}, Direction::LEFT);

    game_objects.push_back(centipede_head_ptr);
    moving_game_objects.push_back(centipede_head_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 2)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{x+counter, y}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while
    auto centipede_tail_index = game_objects.size()-1;

    // Create poisoned Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<Mushroom>(Position{56.0f, y});
    mushroom->poison();
    game_objects.push_back(mushroom);

    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_pos();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_pos()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.checkCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK(mushroom->isAlive());
    CHECK(mushroom->isPoisoned());
    // Check if directions have changed:
    for(auto& object : moving_game_objects)
    {
        CHECK(object->isPoisoned());
    }

}

TEST_CASE("Centipede train follows head's collision with Mushroom even after Mushroom dies.")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    struct CentipedeSegmentDemensions dimension_centipede;
    struct MushroomDimensions dimension_mushroom;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto x = 400.0f;
    auto y = 56.0f;
    auto centipede_seg_ptr = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{x, y}, Direction::LEFT);

    game_objects.push_back(centipede_seg_ptr);
    moving_game_objects.push_back(centipede_seg_ptr);

    auto counter = 0.0f;
    while(game_objects.size() != 5)
    {
        counter +=(dimension_centipede.width+1);
        auto segment = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::BODY,
                                      Position{x+counter, y}, Direction::LEFT);

        game_objects.push_back(segment);
        moving_game_objects.push_back(segment);
    }//while
    auto centipede_tail_index = game_objects.size()-1;

    // Create Mushroom at position in direction of head to check collisions:
    auto mushroom = make_shared<Mushroom>(Position{382.0f, y});
    game_objects.push_back(mushroom);

    auto moves_to_be_made = game_objects.at(centipede_tail_index)->getPosition().getX_pos();
    moves_to_be_made -= (dimension_centipede.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_pos()+dimension_mushroom.width/2.0f);
    moves_to_be_made /= dimension_centipede.speed;

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.checkCollisions(game_objects, moving_game_objects);
        // move
        int half_way = moves_to_be_made/2.0f;
        if(moves_made == half_way)
        {
            for(auto i = 0; i<4; i++)
                mushroom->eliminated();
        }

        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK_FALSE(mushroom->isAlive());

    // Check if directions have changed:
    for(auto& object : moving_game_objects)
        CHECK(object->getDirection()==Direction::RIGHT);

}

// ================ SCORPION COLLISION ================

TEST_CASE("Collision between Scorpion and Mushroom poisons the Mushroom")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    SeparatingAxisTheorem sat_algorithm{};
    struct MushroomDimensions dimensions_mushroom;
    struct ScorpionDimensions dimensions_scorpion;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto x = 400.0f;
    auto y = 56.0f;

    auto scorpion = make_shared<Scorpion>(grid);
    auto mushroom = make_shared<Mushroom>(Position(x, scorpion->getPosition().getY_pos()));

    game_objects.push_back(mushroom);
    game_objects.push_back(scorpion);
    moving_game_objects.push_back(scorpion);

    auto moves_to_be_made = game_objects.at(1)->getPosition().getX_pos();
    moves_to_be_made -= (dimensions_scorpion.width/2.0f);
    moves_to_be_made -= (mushroom->getPosition().getX_pos()+dimensions_mushroom.width/2.0f);
    moves_to_be_made /= dimensions_scorpion.speed;
    moves_to_be_made = static_cast<int>(moves_to_be_made);

    for(auto moves_made = 0; moves_made<=moves_to_be_made+1; moves_made++)
    {
        collision_handler.checkCollisions(game_objects, moving_game_objects);
        // move
        for(auto& object : moving_game_objects)
            object->move();
    }//for

    CHECK(mushroom->isPoisoned());
}

// ================ PLAYER COLLISIONS ================
TEST_CASE("Collision between Player and Mushroom is detected successfully and collision resolution is performed")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    SeparatingAxisTheorem sat_algorithm{};
    struct MushroomDimensions dimensions_mushroom;
    struct PlayerDimension dimensions_player;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto player = make_shared<Player>(grid);
    player->setDirection(Direction::RIGHT);
    game_objects.push_back(player);
    moving_game_objects.push_back(player);

    auto player_pos = player->getPosition();
    auto x = player_pos.getX_pos()+(dimensions_mushroom.width)-dimensions_player.speed;
    auto y = player_pos.getY_pos();
    auto mushroom = make_shared<Mushroom>(Position{x, y});
    game_objects.push_back(mushroom);

    CHECK(sat_algorithm.checkOverlap(player->getBoundaryBox(), mushroom->getBoundaryBox()));
    // Resolve collision:
    collision_handler.checkCollisions(game_objects, moving_game_objects);

    CHECK_FALSE(sat_algorithm.checkOverlap(player->getBoundaryBox(), mushroom->getBoundaryBox()));
    CHECK(player->getDirection()==Direction::NONE);
}


TEST_CASE("Collision between Player and Centipede is detected successfully")
{
    const Grid grid{592, 640};
    CollisionHandler collision_handler{grid};
    SeparatingAxisTheorem sat_algorithm{};
    struct CentipedeSegmentDemensions dimensions_centipede_seg;
    struct PlayerDimension dimensions_player;
    vector<IEntity_ptr> game_objects;
    vector<IMovingEntity_ptr> moving_game_objects;

    auto player = make_shared<Player>(grid);
    player->setDirection(Direction::RIGHT);
    auto player_lives = player->getRemainingLives();
    game_objects.push_back(player);
    moving_game_objects.push_back(player);

    auto player_pos = player->getPosition();
    auto x = player_pos.getX_pos()+(dimensions_centipede_seg.width)-dimensions_player.speed;
    auto y = player_pos.getY_pos();

    auto centipede_head = make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                      Position{x, y}, Direction::LEFT);
    game_objects.push_back(centipede_head);
    moving_game_objects.push_back(centipede_head);

    CHECK(sat_algorithm.checkOverlap(player->getBoundaryBox(), centipede_head->getBoundaryBox()));

    //Check:
    collision_handler.checkCollisions(game_objects, moving_game_objects);
    player_lives-=1;

    CHECK(player->isHit());
    CHECK(player->isAlive());
    CHECK(player->getRemainingLives()==player_lives);
    CHECK_FALSE(centipede_head->isAlive());
}


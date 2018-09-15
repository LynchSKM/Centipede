#include "SpatialHash.h"
#include "IEntity.h"
#include "CentipedeSegment.h"


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Objects in the same cell as object of interest are found successfully"){
    vector<IEntity_ptr> game_objects;

    Grid grid{592, 640};
    auto counter = 0.0f;
    while(game_objects.size() != 4){
        game_objects.push_back(
        std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                           Position{10+counter,10+counter}, Direction::LEFT));
        counter +=10.0f;
    }//while
    SpatialHash spatial_hash{grid};
    spatial_hash.generateSpatialHashTable(game_objects);
    auto near_by_objects = spatial_hash.retrieveNearbyObjects(game_objects.at(0));

    CHECK(near_by_objects.at(0)==game_objects.at(1));
    CHECK(near_by_objects.at(1)==game_objects.at(2));
    CHECK(near_by_objects.at(2)==game_objects.at(3));
}

TEST_CASE("No other objects found in a cell when object of interest is the only one"){
    vector<IEntity_ptr> game_objects;

    Grid grid{592, 640};
    auto counter = 0.0f;
    while(game_objects.size() != 3){
        game_objects.push_back(
        std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                           Position{10+counter,10+counter}, Direction::LEFT));
        counter +=90.0f;
    }//while
    SpatialHash spatial_hash{grid};
    spatial_hash.generateSpatialHashTable(game_objects);
    auto near_by_objects = spatial_hash.retrieveNearbyObjects(game_objects.at(0));

    CHECK(near_by_objects.size()==0u);
}

TEST_CASE("Objects in multiple cells are retrieved when object of interest is on cell boundary"){
    vector<IEntity_ptr> game_objects;

    Grid grid{592, 640};
    // On cell boundary :
    game_objects.push_back(
    std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                       Position{80, 80}, Direction::LEFT));

    // Cell ID are created column wise
    // Cell 0
    game_objects.push_back(
    std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                       Position{20, 20}, Direction::RIGHT));
    // Cell 1
    game_objects.push_back(
    std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                       Position{40, 120}, Direction::LEFT));
    // Cell 8
    game_objects.push_back(
    std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                       Position{120, 40}, Direction::DOWN));
    // Cell 9
    game_objects.push_back(
    std::make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD,
                                       Position{120, 100}, Direction::UP));
    SpatialHash spatial_hash{grid};
    spatial_hash.generateSpatialHashTable(game_objects);
    auto near_by_objects = spatial_hash.retrieveNearbyObjects(game_objects.at(0));

    CHECK(near_by_objects.size()==4u);
}

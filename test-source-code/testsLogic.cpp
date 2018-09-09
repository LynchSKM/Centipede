#include <memory>
#include <vector>
using std::vector;
using std::shared_ptr;
using std::make_shared;

#include "Grid.h"
#include "Logic.h"
#include "IMovingEntity.h"
#include "IEntity.h"
#include "CentipedeSegment.h"

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest.h>

TEST_CASE("Deletion function in Logic can successfully remove dead entities")
{
    Grid grid{600, 648};
    vector<shared_ptr<IEntity>> game_objects;
    auto counter = 0.0f;
    while(game_objects.size() != 10){
        game_objects.push_back(
        make_shared<CentipedeSegment>(grid,CentipedeSegment::BodyType::HEAD, Position{300,250+counter}, Direction::LEFT));
        counter +=10.0f;
    }//while

    for(auto &object : game_objects) {object->eliminated();}

    container_erase_if(game_objects, [](shared_ptr<IEntity>& gameObject){
                       return (!gameObject->isAlive());
                       });
    CHECK(game_objects.size() == 0);
}

#include "CollisionHandler.h"

CollisionHandler::CollisionHandler(const Grid& grid):
spatial_hash_{grid}, points_obtained_{0}
{

}

int CollisionHandler::getPointsObtained()
{
    auto points = points_obtained_;
    points_obtained_ = 0;
    return points;
}

int CollisionHandler::countObjects(vector<IMovingEntity_ptr>::iterator game_objects_begin,
                                   vector<IMovingEntity_ptr>::iterator game_objects_end,
                                   ObjectType object_type)
{
    return (count_if(game_objects_begin,
                     game_objects_end,
                     [&, object_type](const IMovingEntity_ptr& object)
                     {
                        return(object->getObjectType()==object_type);
                     }));
}

vector<IMovingEntity_ptr> CollisionHandler::copyObjects(vector<IMovingEntity_ptr>::iterator game_objects_begin,
                                   vector<IMovingEntity_ptr>::iterator game_objects_end,
                                   ObjectType object_type)
{
    auto number_of_objects = countObjects(game_objects_begin, game_objects_end,
                                          object_type);

    vector<IMovingEntity_ptr> copied_elements(number_of_objects);
    copy_if(game_objects_begin,
            game_objects_end,
            copied_elements.begin(),
            [&, object_type](const IMovingEntity_ptr& object)
            {
                return(object->getObjectType()==object_type);
            });
    return copied_elements;
}


void CollisionHandler::checkCollisions(vector<IEntity_ptr>& game_objects,
                                       vector<IMovingEntity_ptr>& moving_game_objects)
{
    // Generate Spatial Hash:
    spatial_hash_.generateSpatialHashTable(game_objects);

    auto player_bullets = copyObjects(moving_game_objects.begin(), moving_game_objects.end(),
                ObjectType::PLAYER_LASER_BULLET);

    auto centipede = copyObjects(moving_game_objects.begin(), moving_game_objects.end(),
                ObjectType::CENTIPEDE);
    auto player = copyObjects(moving_game_objects.begin(), moving_game_objects.end(),
                ObjectType::PLAYER);

    playerBulletCollidesWithEnemies(player_bullets);
    playerBulletCollidesWithCentipede(player_bullets, centipede);
    playerCollidesWithObjects(player);
    centipedeCollidesWithMushroomOrCentipede(centipede);
}

void CollisionHandler::playerCollidesWithObjects(vector<IMovingEntity_ptr>& player)
{
    for(auto& thePlayer : player)
    {
        auto near_by_objects = spatial_hash_.retrieveNearbyObjects(thePlayer);
        for(auto& object : near_by_objects)
        {
            if(!thePlayer->isAlive()) return;
            if(sat_algorithm_.checkOverlap(thePlayer->getBoundaryBox(), object->getBoundaryBox()))
            {
                if(object->getObjectType() == ObjectType::MUSHROOM)
                {
                    struct PlayerDimension dimensions_player;
                    auto position_player = thePlayer->getPosition();
                    auto position_object = object->getPosition();
                    auto penetration_dist = sat_algorithm_.getPenetrationDistance(position_player,
                                                                                      position_object);

                    // Resolve collision if penetration is greater than zero in x or y:
                    //auto moving_player  = std::dynamic_pointer_cast<IMovingEntity>(thePlayer);
                    Direction direction;
                    if(std::abs(penetration_dist.getX_pos())>=(0.1f*dimensions_player.width))
                    {
                        // Resolve in y direction:
                        if(thePlayer->getDirection()==Direction::UP)
                            direction = Direction::DOWN;
                        else if (thePlayer->getDirection()==Direction::DOWN)
                            direction = Direction::UP;
                    }
                    else
                    {
                        // Resolve in y direction:
                        if(thePlayer->getDirection()==Direction::LEFT)
                            direction = Direction::RIGHT;
                        else if (thePlayer->getDirection()==Direction::RIGHT)
                            direction = Direction::LEFT;
                    }

                    // Move Player by at least one point
                    thePlayer->setDirection(direction);
                    while(true){
                        if(!sat_algorithm_.checkOverlap(thePlayer->getBoundaryBox(), object->getBoundaryBox()))
                           break;
                        thePlayer->move();
                    }

                    thePlayer->setDirection(Direction::NONE);
                }
                else if(object->getObjectType()!=ObjectType::PLAYER_LASER_BULLET)
                { // Anything else will kill player immediately besides it's bullets

                    object->eliminated();
                    thePlayer->eliminated();
                    return;
                }//else
            }//if
        }//for
    }//for
}

void CollisionHandler::playerBulletCollidesWithEnemies(vector<IMovingEntity_ptr>& player_bullets)
{
    for(auto& bullet : player_bullets){
        auto near_by_objects = spatial_hash_.retrieveNearbyObjects(bullet);
        for(auto& object : near_by_objects)
        {
            if(!bullet->isAlive()) break;
            if(object->getObjectType() != ObjectType::CENTIPEDE &&
               object->getObjectType() != ObjectType::PLAYER &&
               object->getObjectType() != ObjectType::PLAYER_LASER_BULLET &&
               object->isAlive())
            {
                if(sat_algorithm_.checkOverlap(bullet->getBoundaryBox(), object->getBoundaryBox()))
                {
                    bullet->eliminated();
                    object->eliminated();

                    // Get points:
                    switch(object->getObjectType())
                    {
                        case ObjectType::MUSHROOM :
                            points_obtained_+=1;
                            break;
                        default:
                            break;
                    }//switch
                }//if
            }//if

        }//for
    }//for
}

void CollisionHandler::playerBulletCollidesWithCentipede(vector<IMovingEntity_ptr>& player_bullets,
                                                         vector<IMovingEntity_ptr>& centipede)
{
    for(auto& bullet : player_bullets){
        auto near_by_objects = spatial_hash_.retrieveNearbyObjects(bullet);
        for(auto& object : near_by_objects)
        {
            if(!bullet->isAlive()) break;
            if(object->getObjectType() == ObjectType::CENTIPEDE && object->isAlive())
            {
                if(sat_algorithm_.checkOverlap(bullet->getBoundaryBox(), object->getBoundaryBox()))
                {
                    bullet->eliminated();
                    object->eliminated();
                    points_obtained_+=100;

                    //Reorder centipede:
                    auto iter_segment = find(centipede.begin(), centipede.end(), object);
                    ++iter_segment;
                    //auto centipede_new_head_ptr = (*iter_segment);
                    if(iter_segment!=centipede.end()){
                        auto centipede_seg_ptr = std::dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                        centipede_seg_ptr->setBodyType(CentipedeSegment::BodyType::HEAD);
                        //++iter_segment;
                    }//if

                    // Set Direction of other segments to follow new head if they are of BodyType::BODY:
                    /*for( ; iter_segment!=centipede.end(); ++iter_segment)
                    {
                        auto centipede_seg_ptr = std::dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                        if(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD) break;
                        centipede_seg_ptr->setDirection(centipede_new_head_ptr->getDirection());
                    }//for*/

                }//if
            }//if

        }//for
    }//for
}

void CollisionHandler::centipedeCollidesWithMushroomOrCentipede(vector<IMovingEntity_ptr>& centipede)
{
    for(auto& segment : centipede)
    {
        auto centipede_ptr = std::dynamic_pointer_cast<CentipedeSegment>(segment);
        if(centipede_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD
           && segment->isAlive() && centipede_ptr->getDirection()!=Direction::DOWN)
        {
            auto near_by_objects = spatial_hash_.retrieveNearbyObjects(segment);
            for(auto& object : near_by_objects)
            {
                if(object->isAlive() && object->getObjectType()==ObjectType::MUSHROOM ||
                   object->getObjectType()==ObjectType::CENTIPEDE)
                {
                    if(sat_algorithm_.checkOverlap(segment->getBoundaryBox(), object->getBoundaryBox()))
                    {

                        auto number_of_heads = 1;

                        if(object->getObjectType() == ObjectType::CENTIPEDE)
                        {
                            auto centipede_head_ptr = std::dynamic_pointer_cast<CentipedeSegment>(object);
                            if(centipede_head_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD)
                                number_of_heads++;
                        }//if

                        auto iter_segment = find(centipede.begin(), centipede.end(), segment);
                        for(auto i=0; i<number_of_heads; i++)
                        {
                            for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
                            {
                                auto centipede_seg_ptr = std::dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                                if(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD) break;
                                centipede_seg_ptr->collisionAt(centipede_ptr->getPosition());
                            }//for
                            centipede_ptr->changeDirection();

                            if(number_of_heads==2)
                            {
                                iter_segment  = find(centipede.begin(), centipede.end(), object);
                                centipede_ptr = std::dynamic_pointer_cast<CentipedeSegment>(object);
                            }//if
                        }
                    }//if

                }//if

            }//for
        }//if
    }//for
}

CollisionHandler::~CollisionHandler()
{
    //dtor
}

#include "CollisionHandler.h"
#include <iostream>
using std::cout;
using std::endl;
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


    playerCollidesWithObjects(player);
    playerBulletCollidesWithEnemies(player_bullets);
    playerBulletCollidesWithCentipede(player_bullets, centipede);
    centipedeCollidesWithMushroom(centipede);
    centipedeCollidesWithCentipede(centipede);
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
                    // Resolve collision if penetration is greater than zero in x or y:
                    Direction direction;
                    if(thePlayer->getDirection()==Direction::UP)
                        direction = Direction::DOWN;
                    else if (thePlayer->getDirection()==Direction::DOWN)
                        direction = Direction::UP;
                    else if(thePlayer->getDirection()==Direction::LEFT)
                        direction = Direction::RIGHT;
                    else if (thePlayer->getDirection()==Direction::RIGHT)
                        direction = Direction::LEFT;

                    // Move Player by at least one point
                    thePlayer->setDirection(direction);
                    thePlayer->move();
                    thePlayer->move();
                    thePlayer->setDirection(Direction::NONE);
                }
                else if(object->getObjectType()!=ObjectType::PLAYER_LASER_BULLET)
                { // Anything else will kill player immediately besides its bullets

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
                    if(iter_segment!=centipede.end())
                    {
                        auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                        centipede_seg_ptr->setBodyType(CentipedeSegment::BodyType::HEAD);
                        auto centipede_new_head_y_pos = centipede_seg_ptr->getPosition().getY_pos();
                        // Update train:
                        for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
                        {
                            auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                            if(centipede_seg_ptr->getBodyType() == CentipedeSegment::BodyType::HEAD) break;

                            if(centipede_seg_ptr->isAlive() &&
                               centipede_seg_ptr->getPosition().getY_pos() == centipede_new_head_y_pos)
                                centipede_seg_ptr->clearHeadCollisions();
                        }//for
                    }//if

                }//if
            }//if

        }//for
    }//for
}

void CollisionHandler::centipedeCollidesWithCentipede(vector<IMovingEntity_ptr>& centipede)
{
    for(auto& segment : centipede)
    {
        auto centipede_head_ptr = dynamic_pointer_cast<CentipedeSegment>(segment);
        if(segment->isAlive()
           && centipede_head_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD
           && segment->getDirection()!=Direction::DOWN
           && segment->getDirection()!=Direction::UP)
        {
            auto near_by_objects = spatial_hash_.retrieveNearbyObjects(segment);
            for(auto& object : near_by_objects)
            {
                if(object->isAlive() && object->getObjectType()==ObjectType::CENTIPEDE)
                {
                    if(sat_algorithm_.checkOverlap(segment->getBoundaryBox(), object->getBoundaryBox()))
                    {

                        auto number_of_heads = 1;

                        auto centipede_ptr = dynamic_pointer_cast<CentipedeSegment>(object);
                        if(centipede_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD
                           && centipede_ptr->getDirection()!=Direction::DOWN
                           && centipede_ptr->getDirection()!=Direction::UP)
                            number_of_heads++;

                        auto iter_segment = find(centipede.begin(), centipede.end(), segment);
                        for(auto i=0; i<number_of_heads; i++)
                        {
                            for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
                            {
                                auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                                if(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD) break;

                                if(centipede_seg_ptr->isAlive())
                                    centipede_seg_ptr->collisionAt(centipede_head_ptr->getPosition(), false);
                            }//for
                            centipede_head_ptr->changeDirection();

                            if(number_of_heads==2)
                            {
                                iter_segment = find(centipede.begin(), centipede.end(), object);
                                centipede_head_ptr = centipede_ptr;
                            }//if
                        }//for
                    }//if

                }//if

            }//for
        }//if
    }//for
}

void CollisionHandler::centipedeCollidesWithMushroom(vector<IMovingEntity_ptr>& centipede)
{
    for(auto& segment : centipede)
    {
        auto centipede_ptr = dynamic_pointer_cast<CentipedeSegment>(segment);
        if(segment->isAlive() &&
           centipede_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD &&
           !segment->isPoisoned())
        {
            auto near_by_objects = spatial_hash_.retrieveNearbyObjects(segment);
            for(auto& object : near_by_objects)
            {
                if(object->isAlive() && object->getObjectType()==ObjectType::MUSHROOM)
                {
                    if(sat_algorithm_.checkOverlap(segment->getBoundaryBox(), object->getBoundaryBox()))
                    {
                        auto iter_segment = find(centipede.begin(), centipede.end(), segment);
                        // Update train of bodies:
                        for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
                        {
                            auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
                            if(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD) break;

                            if(centipede_seg_ptr->isAlive())
                            {
                                centipede_seg_ptr->collisionAt(centipede_ptr->getPosition(),
                                                               object->isPoisoned());
                            }//if

                        }//for

                        if(object->isPoisoned())
                            segment->poison();
                        else
                            centipede_ptr->changeDirection();
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

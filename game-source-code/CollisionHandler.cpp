#include "CollisionHandler.h"
#include <cmath>
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
    auto scorpion = copyObjects(moving_game_objects.begin(), moving_game_objects.end(),
                ObjectType::SCORPION);
    auto spider = copyObjects(moving_game_objects.begin(), moving_game_objects.end(),
                ObjectType::SPIDER);

    playerCollidesWithObjects(player);
    playerBulletCollidesWithEnemies(player_bullets, centipede);
    centipedeCollidesWithCentipede(centipede);
    centipedeCollidesWithMushroom(centipede);
    scorpionCollidesWithMushroom(scorpion);
    spiderCollidesWithMushroom(spider);
    spatial_hash_.clearAll();
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
            }
        }
    }
}

void CollisionHandler::playerBulletCollidesWithEnemies(vector<IMovingEntity_ptr>& player_bullets,
                                                       vector<IMovingEntity_ptr>& centipede)
{
    for(auto& bullet : player_bullets){
        auto near_by_objects = spatial_hash_.retrieveNearbyObjects(bullet);
        for(auto& object : near_by_objects)
        {
            if(!bullet->isAlive()) break;
            if(object->getObjectType() != ObjectType::PLAYER &&
               object->getObjectType() != ObjectType::PLAYER_LASER_BULLET &&
               object->isAlive())
            {
                if(sat_algorithm_.checkOverlap(bullet->getBoundaryBox(), object->getBoundaryBox()))
                {
                    bullet->eliminated();
                    object->eliminated();
                    points_obtained_+=object->getHitPoints();

                    if(object->getObjectType()==ObjectType::CENTIPEDE)
                        splitCentipedeTrain(centipede, object);
                }
            }
        }
    }
}

void CollisionHandler::splitCentipedeTrain(vector<IMovingEntity_ptr>& centipede,
                                           IEntity_ptr& segment)
{
    //Reorder centipede:
    auto iter_new_head = find(centipede.begin(), centipede.end(), segment);
    auto iter_segment  = find(centipede.begin(), centipede.end(), segment);
    ++iter_new_head;
    ++iter_segment;
    if(iter_new_head!=centipede.end())
    {
        auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_new_head);
        centipede_seg_ptr->setBodyType(CentipedeSegment::BodyType::HEAD);

        auto centipede_new_head_y_pos = centipede_seg_ptr->getPosition().getY_pos();

        // Update train:
        for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
        {
            auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
            if(centipede_seg_ptr->getBodyType() == CentipedeSegment::BodyType::HEAD) break;
            if(centipede_seg_ptr->isAlive()
               && centipede_seg_ptr->getPosition().getY_pos() == centipede_new_head_y_pos)
                centipede_seg_ptr->clearHeadCollisions();
        }
    }
}

void CollisionHandler::updateCentipedeTrain(vector<IMovingEntity_ptr>& centipede,
                                            IEntity_ptr segment,
                                            Position collision_point,
                                            bool poisoned_position,
                                            bool move_out_of_collision)
{
    auto iter_segment = find(centipede.begin(), centipede.end(), segment);
    for(++iter_segment; iter_segment!=centipede.end(); ++iter_segment)
    {
        auto centipede_seg_ptr = dynamic_pointer_cast<CentipedeSegment>(*iter_segment);
        if(centipede_seg_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD) break;
        if(centipede_seg_ptr->isAlive())
        {
            centipede_seg_ptr->collisionAt(collision_point, poisoned_position);
            if(move_out_of_collision)
                centipede_seg_ptr->move();
        }
    }//for
}

void CollisionHandler::centipedeCollidesWithCentipede(vector<IMovingEntity_ptr>& centipede)
{
    for(auto& segment : centipede)
    {
        auto centipede_head_ptr = dynamic_pointer_cast<CentipedeSegment>(segment);
        if(segment->isAlive() && !segment->isPoisoned() &&
           centipede_head_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD)
        {
            auto near_by_objects = spatial_hash_.retrieveNearbyObjects(segment);
            for(auto& object : near_by_objects)
            {
                if(object->isAlive() && object->getObjectType()==ObjectType::CENTIPEDE)
                {
                    if(sat_algorithm_.checkOverlap(segment->getBoundaryBox(), object->getBoundaryBox()))
                    {
                        auto posioned_collison = false;
                        auto move_out_of_collision = true;
                        updateCentipedeTrain(centipede, segment,
                                             centipede_head_ptr->getPosition(),
                                             posioned_collison, move_out_of_collision);
                        centipede_head_ptr->changeDirection();
                        centipede_head_ptr->move();
                    }
                }
            }
        }
    }
}

void CollisionHandler::centipedeCollidesWithMushroom(vector<IMovingEntity_ptr>& centipede)
{
    for(auto& segment : centipede)
    {
        auto centipede_head_ptr = dynamic_pointer_cast<CentipedeSegment>(segment);
        if(segment->isAlive() &&
           centipede_head_ptr->getBodyType()==CentipedeSegment::BodyType::HEAD &&
           !segment->isPoisoned())
        {
            auto near_by_objects = spatial_hash_.retrieveNearbyObjects(segment);
            for(auto& object : near_by_objects)
            {
                if(object->isAlive() && object->getObjectType()==ObjectType::MUSHROOM)
                {
                    if(sat_algorithm_.checkOverlap(segment->getBoundaryBox(), object->getBoundaryBox()))
                    {
                        auto move_out_of_collision = false;
                        updateCentipedeTrain(centipede, segment,
                                             centipede_head_ptr->getPosition(),
                                             object->isPoisoned(), move_out_of_collision);

                        if(object->isPoisoned()) segment->poison();
                        else centipede_head_ptr->changeDirection();
                    }
                }
            }
        }
    }
}

void CollisionHandler::scorpionCollidesWithMushroom(vector<IMovingEntity_ptr>& scorpions)
{
   for(auto& scorpion :scorpions)
   {
       if(scorpion->isAlive())
       {
          auto near_by_objects = spatial_hash_.retrieveNearbyObjects(scorpion);
          for(auto& object: near_by_objects)
          {
              if(object->isAlive() && object->getObjectType()==ObjectType::MUSHROOM)
              {
                 if(sat_algorithm_.checkOverlap(scorpion->getBoundaryBox(), object->getBoundaryBox()))
                    object->poison();
              } //if
          } // for
       }//if
   }//for
}
void CollisionHandler::spiderCollidesWithMushroom(vector<IMovingEntity_ptr>& spiders)
{
   for(auto& spider :spiders)
   {
       if(spider->isAlive())
       {
          auto near_by_objects = spatial_hash_.retrieveNearbyObjects(spider);
          for(auto& object: near_by_objects)
          {
              if(object->isAlive() && object->getObjectType()==ObjectType::MUSHROOM)
              {
                 if(sat_algorithm_.checkOverlap(spider->getBoundaryBox(), object->getBoundaryBox()))
                    while(object->isAlive()) object->eliminated();
              } //if
          } // for
       }//if
   }//for
}

CollisionHandler::~CollisionHandler()
{
    //dtor
}

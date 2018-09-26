#include "CentipedeSegment.h"
#include <cmath>

using std::round;

CentipedeSegment::CentipedeSegment(const Grid& grid, BodyType bodytype, Position position, Direction cur_Direction):
cur_Direction_{cur_Direction},
bodytype_{bodytype},
objectType_{ObjectType::CENTIPEDE},
position_{position}, grid_{grid}
{
    prev_Direction_ = Direction::DOWN;
    moveDownCount_ = 0;
    changeWhenPoisoned_ = false;
    centAtbottom_ = false;

}

bool CentipedeSegment::isEntryMovement()
{

    struct CentipedeSegmentDemensions dimensions;
    auto speed = dimensions.speed;
    auto half_screen_width = grid_.getWidth()/2.0f;

    if(position_.getY_pos() < 0 && cur_Direction_==Direction::LEFT ){
        if(position_.getX_pos() < half_screen_width){
            moveDown();
            moveDown();
            return true;
        }
    }else if(position_.getY_pos() < 0 && cur_Direction_==Direction::RIGHT ){
        if(position_.getX_pos() > half_screen_width){
            moveDown();
            moveDown();
            return true;
        }
    }

    return false;
}

void CentipedeSegment::clearHeadCollisions()
{
    head_collision_positions_.clear();
    are_head_collision_positions_poisioned_.clear();
}

void CentipedeSegment::collisionAt(Position position, bool poisionedCollision)
{   if(bodytype_ == BodyType::HEAD)
    {
        clearHeadCollisions();
        return;
    }//if
    if(std::count(head_collision_positions_.begin(),
                  head_collision_positions_.end(), position)==0)
    {
        are_head_collision_positions_poisioned_.push_back(poisionedCollision);
        head_collision_positions_.push_back(position);
    }
}

void CentipedeSegment::checkHeadCollisions()
{
    if(head_collision_positions_.empty()) return;
    auto iter_vec_position = head_collision_positions_.begin();
    auto iter_vec_posioned_pos = are_head_collision_positions_poisioned_.begin();

    if(position_ == (*iter_vec_position))
    {
        if(*iter_vec_posioned_pos) poison();
        else changeDirection();

        head_collision_positions_.erase(iter_vec_position);
        are_head_collision_positions_poisioned_.erase(iter_vec_posioned_pos);
    }//if
    return;
}


void CentipedeSegment::moveUp()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    auto newYPos = position_.getY_pos() - dimensions.speedY;
    if(newYPos > maxHeight){
        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT){
            setDirection(Direction::RIGHT);
            moveRight();
            rotationAngle_ = 45.0f;
            prev_Direction_ = Direction::UP;
        }else{
            setDirection(Direction::LEFT);
            moveLeft();
            rotationAngle_ = -45.0f;
            prev_Direction_ = Direction::UP;
        }//if

    }else{
        moveDown();
    }//if
}

void CentipedeSegment::moveDown()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxHeight = grid_.getHeight()-(dimensions.height/2.0f);
    auto newYPos = position_.getY_pos() + dimensions.speedY;

    if(newYPos <= maxHeight)
    {

        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT){
            setDirection(Direction::RIGHT);
            moveRight();
            rotationAngle_ = 45.0f;
            prev_Direction_ = Direction::DOWN;

         }else{
            setDirection(Direction::LEFT);
            moveLeft();
            rotationAngle_ = -45.0f;
            prev_Direction_ = Direction::DOWN;
         }

    }else{
        centAtbottom_ = true;
        moveUp();
        centAtbottom_ = false;
        isPoisonedMovementComplete_= true;
    }
}

void CentipedeSegment::moveLeft()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxWidth = grid_.getWidth()-(dimensions.width/2.0f);
    auto newXPos = position_.getX_pos()- dimensions.speed;

    if(isPoisoned() && centAtbottom_)newXPos = position_.getX_pos()-(dimensions.width+1);

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > (dimensions.width/2.0f)){
        position_.setX_pos(newXPos);
    }else{
        if(prev_Direction_==Direction::UP){
            setDirection(Direction::UP);
            moveUp();
        }else if(prev_Direction_==Direction::DOWN){
            setDirection(Direction::DOWN);
            moveDown();
        }
    }
}

void CentipedeSegment::moveRight()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxWidth = grid_.getWidth()-(dimensions.width/2.0f);
    auto newXPos = position_.getX_pos()+ dimensions.speed;

    if(isPoisoned() && centAtbottom_)newXPos = position_.getX_pos()+ (dimensions.width+1);

    newXPos = (round(newXPos*10))/10;

    if(newXPos < maxWidth){
        position_.setX_pos(newXPos);

    }else{
        if(prev_Direction_==Direction::UP){
            setDirection(Direction::UP);
            moveUp();
        }else if(prev_Direction_==Direction::DOWN){
            setDirection(Direction::DOWN);
            moveDown();
        }
    }
}

void CentipedeSegment::move()
{
    if(isEntryMovement())return;
    if(isPoisonedMovementComplete_) isPoisoned_ = false;
    if(!isPoisoned_)//Normal movement
    {   struct CentipedeSegmentDemensions dimensions;

        if(bodytype_==BodyType::BODY) checkHeadCollisions();
        switch (cur_Direction_){

            case Direction::DOWN:
                moveDown();
                break;

            case Direction::LEFT:
                rotationAngle_ = 0.0f;
                moveLeft();
                break;

            case Direction::RIGHT:
                rotationAngle_ = 0.0f;
                moveRight();
                break;

            case Direction::UP:
                moveUp();
                break;

            default :
                break;
        }//switch
    }
    else
    {
        //poisoned movement
        //setDirection(Direction::DOWN);
        isPoisonedMovement();
    }
}

void CentipedeSegment::isPoisonedMovement()
{
    isPoisonedMovementComplete_ = false;
    if(moveDownCount_ == 0)
    {   setDirection(Direction::DOWN);
        moveDown();
        changeWhenPoisoned_ = !changeWhenPoisoned_;
    }
    else
    {
        if(changeWhenPoisoned_)
        {
            setDirection(Direction::LEFT);
            moveLeft();
        }//if
        if(!changeWhenPoisoned_)
        {
            setDirection(Direction::RIGHT);
            moveRight();
        }//if
    }//if
    moveDownCount_ = (++moveDownCount_)%50;
}


void CentipedeSegment::setDirection(Direction direction)
{
    prev_Direction_ = cur_Direction_;
    cur_Direction_ = direction;
}

ObjectType CentipedeSegment::getObjectType() const
{
    return objectType_;
}

CentipedeSegment::BodyType CentipedeSegment::getBodyType() const{
    return bodytype_;
}

void CentipedeSegment::setBodyType(BodyType body_type)
{
    bodytype_ = body_type;
}


Position CentipedeSegment::getPosition() const
{
    return position_;
}

BoundaryBox CentipedeSegment::getBoundaryBox()
{
    struct CentipedeSegmentDemensions Dimension;
    BoundaryBox box{position_,Dimension.width,Dimension.height,0};
    return box;
}


int CentipedeSegment::getRemainingLives() const
{
    if(isAlive()) return 1;

    return 0;
}

void CentipedeSegment::reincarnate()
{

}

bool CentipedeSegment::isAlive() const
{
    return alive_;
}

void CentipedeSegment::eliminated()
{
    alive_ = false;
}

void CentipedeSegment::poison()
{
    isPoisoned_ = true;
}

bool CentipedeSegment::isPoisoned() const
{
    return isPoisoned_;
}

Direction CentipedeSegment::getDirection() const
{
    return cur_Direction_;
}
Direction CentipedeSegment::getPrevDirection() const
{
    return prev_Direction_;
}
void CentipedeSegment::changeDirection()
{
    if(prev_Direction_==Direction::DOWN)setDirection(Direction::DOWN);
    else if(prev_Direction_==Direction::UP)setDirection(Direction::UP);

}
float CentipedeSegment::getRotationAngle() const
{
    return rotationAngle_;
}

CentipedeSegment::~CentipedeSegment()
{
    //dtor
}

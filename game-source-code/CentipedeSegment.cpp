#include "CentipedeSegment.h"
#include <cmath>

using std::round;

CentipedeSegment::CentipedeSegment(Grid grid, BodyType bodytype, Position position, Direction cur_Direction):
cur_Direction_{cur_Direction},
bodytype_{bodytype},
objectType_{ObjectType::CENTIPEDE},
position_{position}, grid_{grid}
{
    prev_Direction_ = Direction::DOWN;
}

bool CentipedeSegment::isEntryMovement(){

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
void CentipedeSegment::moveUp()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    auto newYPos = position_.getY_pos() - dimensions.speedY;
    if(newYPos > maxHeight){
        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT){
                setDirection(Direction::RIGHT);
                prev_Direction_ = Direction::UP;
        }else{
            setDirection(Direction::LEFT);
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

    if(newYPos <= maxHeight){
        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT){
            setDirection(Direction::RIGHT);
            prev_Direction_ = Direction::DOWN;

         }else{
            setDirection(Direction::LEFT);
            prev_Direction_ = Direction::DOWN;
         }

    }else{
        isPosoned_=false;
        moveUp();
    }
}

void CentipedeSegment::moveLeft()
{
    struct CentipedeSegmentDemensions dimensions;
    float maxWidth = grid_.getWidth()-(dimensions.width/2.0f);
    auto newXPos = position_.getX_pos()- dimensions.speed;


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
    //Normal movement
    struct CentipedeSegmentDemensions dimensions;
    if(!isPosoned_){
    switch (cur_Direction_){

        case Direction::DOWN:
            moveDown();
            break;

        case Direction::LEFT:
            moveLeft();
            break;

        case Direction::RIGHT:
            moveRight();
            break;

        case Direction::UP:
            moveUp();
            break;

        default :
            break;
    }//switch
    }else{
        //poisoned movement
        moveDown();
    }
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
    BoundaryBox box{position_,Dimension.width,Dimension.height,rotationAngle_};
    return box;
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
    isPosoned_ = true;
}

Direction CentipedeSegment::getDirection() const
{
    return cur_Direction_;
}
Direction CentipedeSegment::getPrevDirection() const
{
    return prev_Direction_;
}
void CentipedeSegment::changeDirection(){
    setDirection(Direction::DOWN);
}
CentipedeSegment::~CentipedeSegment()
{
    //dtor
}

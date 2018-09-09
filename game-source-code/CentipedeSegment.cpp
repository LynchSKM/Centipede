#include "CentipedeSegment.h"

CentipedeSegment::CentipedeSegment(Grid grid, BodyType bodytype, Position position, Direction cur_Direction):
cur_Direction_{cur_Direction},
bodytype_{bodytype},
objectType_{ObjectType::CENTIPEDE},
position_{position}, grid_{grid}
{
    //ctor
}
void CentipedeSegment::moveUp(float speed)
{
    float maxHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    auto newYPos = position_.getY_pos() - speed;

    if(newYPos > maxHeight){
        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT)setDirection(Direction::RIGHT);
        else setDirection(Direction::LEFT);

    }else{
        moveDown(speed);
    }
}

void CentipedeSegment::moveDown(float speed)
{
    float maxHeight = grid_.getHeight();
    auto newYPos = position_.getY_pos() + speed;

    if(newYPos < maxHeight){
        position_.setY_pos(newYPos);
        if(prev_Direction_==Direction::LEFT)setDirection(Direction::RIGHT);
        else setDirection(Direction::LEFT);

    }else{
        isPosoned_=false;
        moveUp(speed);
    }
}

void CentipedeSegment::moveLeft(float speed)
{
    float maxWidth = grid_.getWidth();
    auto newXPos = position_.getX_pos()- speed;

    if(newXPos < maxWidth){
        position_.setX_pos(newXPos);
    }else{
        setDirection(Direction::DOWN);
        moveDown(speed);
    }
}

void CentipedeSegment::moveRight(float speed)
{
    float maxWidth = grid_.getWidth();
    auto newXPos = position_.getX_pos()+ speed;

    if(newXPos < maxWidth){
        position_.setX_pos(newXPos);
    }else{
        setDirection(Direction::DOWN);
        moveDown(speed);
    }
}


void CentipedeSegment::move()
{
    //Normal movement
    struct CentipedeSegmentDemensions dimensions;
    auto speed = dimensions.speed;
    if(!isPosoned_){
    switch (cur_Direction_){

        case Direction::DOWN:
            moveDown(speed);
            break;

        case Direction::LEFT:
            moveLeft(speed);
            break;

        case Direction::RIGHT:
            moveRight(speed);
            break;

        case Direction::UP:
            moveUp(speed);
            break;

        default :
            break;
    }//switch
    }else{
        //poisoned movement
        moveDown(speed);
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

#include "Centipede.h"

Centipede::Centipede(Direction cur_Direction, BodyType bodytype, ObjectType objectType,Position position,Grid grid): cur_Direction_{cur_Direction},
bodytype_{bodytype}, objectType_{objectType}, position_{position}, grid_{grid}
{
    //ctor
}
void Centipede::moveUp(float speed)
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

void Centipede::moveDown(float speed)
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

void Centipede::moveLeft(float speed)
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

void Centipede::moveRight(float speed)
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


void Centipede::move()
{
    //Normal movement
    auto speed = 5.0f;
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

void Centipede::setDirection(Direction direction)
{
    prev_Direction_ = cur_Direction_;
    cur_Direction_ = direction;
}

ObjectType Centipede::getObjectType() const
{
    return objectType_;
}

Position Centipede::getPosition() const
{
    return position_;
}

BoundaryBox Centipede::getBoundaryBox()
{
    struct CentipedeDemensions Dimension;
    BoundaryBox box{position_,Dimension.width,Dimension.height,rotationAngle_};
    return box;
}

bool Centipede::isAlive() const
{
    return alive_;
}

void Centipede::eliminated()
{
    alive_ = false;
}

void Centipede::poison()
{
    isPosoned_ = true;
}

Direction Centipede::getDirection() const
{
    return cur_Direction_;
}
Direction Centipede::getPrevDirection() const
{
    return prev_Direction_;
}
void Centipede::changeDirection(){
    setDirection(Direction::DOWN);
}
Centipede::~Centipede()
{
    //dtor
}

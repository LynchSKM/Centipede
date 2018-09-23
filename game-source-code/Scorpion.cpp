#include "Scorpion.h"

Scorpion::Scorpion(const Grid& grid, Position position, Direction direction):grid_{grid},position_{position}, direction_{direction}
{
        objectType_ = ObjectType::SCORPION;
        isPoisoned_ = false;
        isAlive_    = true;
        numberOfLives_ = 1;
}
void Scorpion::moveLeft()
{
    struct ScorpionDimensions dimensions;
    float maxWidth = grid_.getWidth()-(dimensions.width/2.0f);
    auto newXPos = position_.getX_pos()- dimensions.speed;

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > (dimensions.width/2.0f))
    {
        position_.setX_pos(newXPos);
    }
    else
    {
        eliminated();
    }
}

void Scorpion::moveRight()
{
    struct ScorpionDimensions dimensions;
    float maxWidth = grid_.getWidth()-(dimensions.width/2.0f);
    auto newXPos = position_.getX_pos()+ dimensions.speed;

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > (dimensions.width/2.0f))
    {
        position_.setX_pos(newXPos);
    }
    else
    {
        eliminated();
    }
}

void Scorpion::move()
{
    if(direction_ == Direction::LEFT) moveLeft();
    else if(direction_ == Direction::RIGHT) moveRight();
}

Direction Scorpion::getDirection() const
{
    return direction_;
}

void Scorpion::setDirection(Direction direction)
{
    direction_ = direction;
}

ObjectType Scorpion::getObjectType() const
{
    return objectType_;
}

Position Scorpion::getPosition() const
{
    return position_;
}

BoundaryBox Scorpion::getBoundaryBox()
{
    struct ScorpionDimensions dimension;
    BoundaryBox box{position_,dimension.width,dimension.height,0};
    return box;
}

bool Scorpion::isAlive() const
{
    return isAlive_;
}

void Scorpion::eliminated()
{
    if(isAlive_) --numberOfLives_;
    isAlive_ = false;
}

void Scorpion::reincarnate()
{
    isAlive_ = true;
}

int Scorpion::getRemainingLives() const
{
    return numberOfLives_;
}

bool Scorpion::isPoisoned() const
{
    return isPoisoned_;
}

void Scorpion::poison()
{
    //Scorpion can not be poisoned
    isPoisoned_ = false;
}

Scorpion::~Scorpion()
{
    //dtor
}

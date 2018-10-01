#include "Mushroom.h"

struct MushroomDimensions Mushroom::dimensions_;

Mushroom::Mushroom(Position position):
    position_{position},
    isPoisoned_{false},
    isAlive_{true},
    numberOfLives_{4}
{
    //ctor
}

ObjectType Mushroom::getObjectType() const
{
    return ObjectType::MUSHROOM;
}

Position Mushroom::getPosition() const
{
    return position_;
}

BoundaryBox Mushroom::getBoundaryBox()
{
    return BoundaryBox{position_, dimensions_.width, dimensions_.height, 0.0};
}

bool Mushroom::isAlive() const
{
    if(numberOfLives_<=0) return false;
    else return true;
}

void Mushroom::eliminated()
{
    decrementLives();
    if(numberOfLives_<=0)isAlive_ = false;
}
void Mushroom::decrementLives()
{
    numberOfLives_--;
}

bool Mushroom::isPoisoned() const
{
    return isPoisoned_;
}

void Mushroom::poison()
{
    isPoisoned_ = true;
}

int Mushroom::getRemainingLives() const
{
    return numberOfLives_;
}

void Mushroom::reincarnate()
{
    if(!isAlive()) return;
    numberOfLives_ = 4;
    isPoisoned_ = false;
}

int Mushroom::getHitPoints() const
{
    if(isPoisoned()) return 2;
    return 1;
}

Mushroom::~Mushroom()
{
    //dtor
}

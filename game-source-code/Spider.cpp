#include "Spider.h"
#include <ctime>
#include <cmath>

Spider::Spider(const Grid& grid):
    grid_{grid},
    isAlive_{true}
{
    srand(time(0));
}

void Spider::move()
{
    float maxWidth  = grid_.getWidth();
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.25;
    float maxHeight = grid_.getHeight();


}

Direction Spider::getDirection() const
{
    return direction_;
}

ObjectType Spider::getObjectType() const
{
    return ObjectType::SCORPION;
}

Position Spider::getPosition() const
{
    return position_;
}

BoundaryBox Spider::getBoundaryBox()
{
    return BoundaryBox{position_, dimensions_.width, dimensions_.height, 0.0f};
}

bool Spider::isAlive() const
{
    return isAlive_;
}

void Spider::eliminated()
{
    isAlive_ = false;
}

int Spider::getRemainingLives() const
{
    if(isAlive()) return 1;
    return 0;
}

void Spider::setDirection(Direction direction)
{

}

void Spider::reincarnate()
{

}

bool Spider::isPoisoned() const
{
    return false;
}

void Spider::poison()
{

}

Spider::~Spider()
{

}

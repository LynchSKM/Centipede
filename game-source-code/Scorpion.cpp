#include "Scorpion.h"
#include <ctime>

struct ScorpionDimensions Scorpion::dimensions_;

Scorpion::Scorpion(const Grid& grid):
    grid_{grid},
    isAlive_{true}
{
    srand(time(0));
    auto row = rand()%15 + 10;
    auto xPos = 0.0f;
    position_.setY_pos(round(row*16.0f +24.0f));
    direction_ = static_cast<Direction>(rand()%2 + 2);

    if(direction_ == Direction::LEFT)
       position_.setX_pos(grid_.getWidth()-(dimensions_.width/2.0f + 1.0f));
    else position_.setX_pos(dimensions_.width/2.0f + 1.0f);

}
void Scorpion::moveLeft()
{
    float maxWidth = grid_.getWidth();
    auto newXPos = position_.getX_pos()- dimensions_.speed;

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > 0)
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
    float maxWidth = grid_.getWidth();
    auto newXPos = position_.getX_pos()+ dimensions_.speed;

    newXPos = (round(newXPos*10))/10;


    if(newXPos < maxWidth && newXPos > 0)
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
    return ObjectType::SCORPION;
}

Position Scorpion::getPosition() const
{
    return position_;
}

BoundaryBox Scorpion::getBoundaryBox()
{
    return BoundaryBox{position_, dimensions_.width, dimensions_.height, 0.0f};
}

bool Scorpion::isAlive() const
{
    return isAlive_;
}

void Scorpion::eliminated()
{
    isAlive_ = false;
}

void Scorpion::reincarnate()
{
    isAlive_ = true;
}

int Scorpion::getRemainingLives() const
{
    if(isAlive()) return 1;
    return 0;
}

bool Scorpion::isPoisoned() const
{
    return false;
}

void Scorpion::poison()
{
    return;
}

int Scorpion::getHitPoints() const
{
    auto hitPoints = 40;
    return hitPoints;
}


Scorpion::~Scorpion()
{
    //dtor
}

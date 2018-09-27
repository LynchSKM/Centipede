#include "Spider.h"
#include <ctime>
#include <cmath>

struct SpiderDimensions Spider::dimensions_;

Spider::Spider(const Grid& grid):
    grid_{grid},
    isAlive_{true},
    turningPointAvailable_{false}
{
    srand(time(0));
    movementDirection_ = Direction::DOWN;
    major_direction_ = static_cast<Direction>(rand()%2+2);// LEFT or RIGHT

    if(major_direction_ == Direction::LEFT)
    {
        position_.setX_pos(grid_.getWidth()-(dimensions_.width/2.0f + 1.0f));
        position_.setY_pos(grid_.getHeight()- grid_.getHeight()*0.2f);

    }else{
        position_.setX_pos(dimensions_.width/2.0f + 1.0f);
        position_.setY_pos(grid_.getHeight()- grid_.getHeight()*0.2f);
    }
}

void Spider::CalculateSlope()
{
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.25;
    float maxHeight = grid_.getHeight();
    auto multFactor = 5;

    if(movementDirection_ == Direction::DOWN)
    {
        auto xpos = rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width;
        auto ypos = rand()%static_cast<int>(maxHeight - position_.getY_pos()) + position_.getY_pos();

        turningPoint_.setX_pos(xpos);
        turningPoint_.setY_pos(ypos);

        slope_ = (position_.getY_pos() - ypos)/(position_.getX_pos() - xpos);
        turningPointAvailable_ = true;
    }
    else
    {
        auto xpos = rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width;
        auto ypos = rand()%static_cast<int>(position_.getY_pos() - minHeight) + position_.getY_pos();

        turningPoint_.setX_pos(xpos);
        turningPoint_.setY_pos(ypos);

        slope_= (position_.getY_pos() - ypos)/(position_.getX_pos() - xpos);
        turningPointAvailable_ = true;
    }
}

void Spider::moveUp()
{
    float maxWidth  = grid_.getWidth();
    auto newXpos = 0.f;
    auto newYpos = 0.f;

    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ == Direction::LEFT)newXpos = position_.getX_pos()-dimensions_.speed;
    else newXpos = position_.getX_pos()+dimensions_.speed;

    newYpos = position_.getY_pos()- abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }

    if(newYpos >= turningPoint_.getY_pos()){
        position_.setX_pos(newXpos);
        position_.setY_pos(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = Direction::DOWN;
    }//if-else
}

void Spider::moveDown()
{
    float maxWidth  = grid_.getWidth();
    auto newXpos = 0.f;
    auto newYpos = 0.f;

    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ == Direction::LEFT)newXpos = position_.getX_pos()-dimensions_.speed;
    else newXpos = position_.getX_pos()+dimensions_.speed;

    newYpos = position_.getY_pos()+ abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }
    if(newYpos <= turningPoint_.getY_pos()){
        position_.setX_pos(newXpos);
        position_.setY_pos(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = Direction::UP;
    }//if-else
}

void Spider::move()
{
    float maxWidth  = grid_.getWidth();
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.25;
    float maxHeight = grid_.getHeight();

    switch(movementDirection_)
    {
        case Direction::UP:
            moveUp();
            break;
        case Direction::DOWN:
            moveDown();
            break;
        default:
            break;
    }//switch
}

Direction Spider::getDirection() const
{
    return major_direction_;
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
    major_direction_ = direction;
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

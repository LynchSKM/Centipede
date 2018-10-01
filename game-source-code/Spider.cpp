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
    auto xpos = 0.0f;
    auto ypos = 0.0f;
    auto multFactor = 4;

    if(movementDirection_ == Direction::DOWN)
    {
        if(major_direction_ == Direction::LEFT)
             xpos = rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width + position_.getX_pos();
        else  xpos = position_.getX_pos() - rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width;

        auto y_difference = 0.5f*(maxHeight - position_.getY_pos());
         ypos = rand()%static_cast<int>(y_difference) + position_.getY_pos() + y_difference;

        turningPoint_.setX_pos(xpos);
        turningPoint_.setY_pos(ypos);

        slope_ = std::abs(position_.getY_pos() - ypos)/std::abs(position_.getX_pos() - xpos);
        turningPointAvailable_ = true;
    }
    else
    {
        if(major_direction_ == Direction::LEFT)
             xpos = rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width + position_.getX_pos();
        else  xpos = position_.getX_pos() - rand()%static_cast<int>(multFactor*dimensions_.width) + multFactor*dimensions_.width;

        auto y_difference = 0.5f*(position_.getY_pos()-minHeight);
         ypos =  position_.getY_pos() - rand()%static_cast<int>(y_difference);

        turningPoint_.setX_pos(xpos);
        turningPoint_.setY_pos(ypos);

        slope_= std::abs(position_.getY_pos() - ypos)/std::abs(position_.getX_pos() - xpos);
        turningPointAvailable_ = true;
    }
}

void Spider::moveUp()
{
    float maxWidth  = grid_.getWidth();
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.25;
    auto newXpos = 0.f;
    auto newYpos = 0.f;

    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ == Direction::LEFT)newXpos = position_.getX_pos()-dimensions_.speed;
    else newXpos = position_.getX_pos()+dimensions_.speed;

    newYpos = position_.getY_pos()- std::abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }

    if(newYpos >= turningPoint_.getY_pos() && newYpos >= minHeight)
    {
        position_.setX_pos(newXpos);
        position_.setY_pos(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = Direction::DOWN;
        moveDown();
    }//if-else
}

void Spider::moveDown()
{
    float maxWidth  = grid_.getWidth();
    float maxHeight = grid_.getHeight();
    auto newXpos = 0.f;
    auto newYpos = 0.f;

    if(!turningPointAvailable_)CalculateSlope();

    if(major_direction_ == Direction::LEFT)newXpos = position_.getX_pos()-dimensions_.speed;
    else newXpos = position_.getX_pos()+dimensions_.speed;

    newYpos = position_.getY_pos()+ std::abs(slope_*dimensions_.speed);
    if(newXpos < 0 || newXpos > maxWidth){
        isAlive_ = false;
        return;
    }
    if(newYpos <= turningPoint_.getY_pos() && newYpos <= maxHeight){
        position_.setX_pos(newXpos);
        position_.setY_pos(newYpos);
    }
    else
    {
        turningPointAvailable_ = false;
        movementDirection_ = Direction::UP;
        moveUp();
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
    return ObjectType::SPIDER;
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
    return;
}

bool Spider::isPoisoned() const
{
    return false;
}

void Spider::poison()
{
    return;
}

int Spider::getHitPoints() const
{
    auto hitPoints = 300;
    return hitPoints;
}

Spider::~Spider()
{

}

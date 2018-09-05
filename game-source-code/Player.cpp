#include "Player.h"

Player::Player(Grid grid):grid_{grid},objectType_{ObjectType::PLAYER}, numberOfLives_{5}, direction_{Direction::NONE}{
    position_.setX_pos(grid_.getWidth()/2.0);
    struct PlayerDimension playerDimension;
    position_.setY_pos(grid_.getHeight()-playerDimension.height*0.5);


}

Player::~Player(){

}

void Player::move()
{
    auto speed = 5.0f;
    float maxWidth = grid_.getWidth();
    float minHeight = grid_.getHeight();
    float maxHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    auto newXPos = 0.0f;
    auto newYPos = 0.0f;

    switch (direction_){

        case Direction::DOWN:
            newYPos = position_.getY_pos() + speed;

            if(newYPos <= minHeight) position_.setY_pos(newYPos);

            break;

        case Direction::LEFT:
            newXPos = position_.getX_pos()- speed;

            if(newYPos >= 0) position_.setX_pos(newXPos);

            break;

        case Direction::RIGHT:
            newXPos = position_.getX_pos()+speed;

            if(newXPos <= minHeight) position_.setX_pos(newXPos);

            break;

        case Direction::UP:
            newYPos = position_.getY_pos() - speed;

            if(newYPos>= maxHeight) position_.setY_pos(newYPos);

            break;
        default :
            break;
    }//switch
}

ObjectType Player::getObjectType() const
{
    return objectType_;
}

Position Player::getPosition() const
{
    return position_;
}

BoundaryBox Player::getBoundaryBox()
{
    BoundaryBox box{position_,30.0,40.0,0.0};
    //boundary_box_ = box;
    return box;
}

bool Player::isAlive() const
{
    if(numberOfLives_>0) return true;

    return false;
}

void Player::eliminated()
{

}

Direction Player::getDirection() const
{
    return direction_;
}

void Player::setDirection(Direction direction)
{
    direction_ = direction;
}

int Player::getRemainingLives() const
{
    return numberOfLives_;
}

vector <shared_ptr<IMovingEntity>> Player::shoot()
{

}

void Player::addScore(int score)
{
    score_ += score;
}

int Player::getScore() const
{
    return score_;
}

void Player::reincarnate()
{
    if(isAlive()){
        struct PlayerDimension playerDimension;
        numberOfLives_--;
        position_.setX_pos(grid_.getWidth()/2.0);
        position_.setY_pos(grid_.getHeight()-playerDimension.height*0.5);
    }//if
}

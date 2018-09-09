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
    struct PlayerBulletDimentions Dimension;
    float maxWidth = grid_.getWidth()-16.0f;
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    float maxHeight = grid_.getHeight();
    auto newXPos = 0.0f;
    auto newYPos = 0.0f;

    switch (direction_){

        case Direction::DOWN:
            newYPos = position_.getY_pos() + Dimension.speed;

            if(newYPos <= (maxHeight-8.0f)) position_.setY_pos(newYPos);

            break;

        case Direction::LEFT:
            newXPos = position_.getX_pos()- Dimension.speed;

            if(newXPos >= 8.0f) position_.setX_pos(newXPos);

            break;

        case Direction::RIGHT:
            newXPos = position_.getX_pos()+ Dimension.speed;

            if(newXPos <= (maxWidth+8.0f)) position_.setX_pos(newXPos);

            break;

        case Direction::UP:
            newYPos = position_.getY_pos() - Dimension.speed;

            if(newYPos>= minHeight) position_.setY_pos(newYPos);

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
    struct PlayerDimension player_box;
    BoundaryBox box{position_,player_box.width, player_box.height, 0.0};
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
    struct PlayerBulletDimentions dimension;
    auto xVal = position_.getX_pos()-dimension.speed;
    auto yVal = position_.getY_pos()-dimension.height/2.0f;


    vector<shared_ptr<IMovingEntity>> bullets;
    bullets.push_back(std::make_shared<PlayerBullet>(Position{xVal,yVal},grid_));
    return bullets;
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

#include "Player.h"

Player::Player(const Grid& grid):
    grid_{grid},
    numberOfLives_{3},
    direction_{Direction::NONE}
{
    position_.setX_pos(grid_.getWidth()/2.0);
    position_.setY_pos(grid_.getHeight()-dimensions_.height*0.5);
}

Player::~Player()
{

}

void Player::move()
{
    float maxWidth  = grid_.getWidth()-16.0f;
    float minHeight = grid_.getHeight()- grid_.getHeight()*0.2;
    float maxHeight = grid_.getHeight();
    auto newXPos = 0.0f;
    auto newYPos = 0.0f;

    switch (direction_)
    {
        case Direction::DOWN:
            newYPos = position_.getY_pos() + dimensions_.speed;

            if(newYPos <= (maxHeight-8.0f)) position_.setY_pos(newYPos);

            break;

        case Direction::LEFT:
            newXPos = position_.getX_pos()-dimensions_.speed;

            if(newXPos >= 8.0f) position_.setX_pos(newXPos);

            break;

        case Direction::RIGHT:
            newXPos = position_.getX_pos()+dimensions_.speed;

            if(newXPos <= (maxWidth+8.0f)) position_.setX_pos(newXPos);

            break;

        case Direction::UP:
            newYPos = position_.getY_pos() - dimensions_.speed;

            if(newYPos>= minHeight) position_.setY_pos(newYPos);

            break;
        default :
            break;
    }//switch
}

ObjectType Player::getObjectType() const
{
    return ObjectType::PLAYER;
}

Position Player::getPosition() const
{
    return position_;
}

BoundaryBox Player::getBoundaryBox()
{
    return BoundaryBox{position_,dimensions_.width, dimensions_.height, 0.0};
}

bool Player::isAlive() const
{
    if(numberOfLives_>0) return true;

    return false;
}

void Player::eliminated()
{
    hasBeenHit_ = true;
    numberOfLives_--;
}

bool Player::isHit()
{
    return hasBeenHit_;
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

bool Player::isPoisoned() const
{
    return false;
}

vector<shared_ptr<PlayerBullet>> Player::shoot()
{
    auto x = position_.getX_pos()-dimensions_.speed;
    auto y = position_.getY_pos()-dimensions_.height/2.0f;

    return weapon_.fire(grid_, Position{x, y});
}


void Player::upgradePlayerWeapon()
{
    weapon_.upgradeWeapon();
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
    if(isAlive())
    {
        position_.setX_pos(grid_.getWidth()/2.0);
        position_.setY_pos(grid_.getHeight()-dimensions_.height*0.5);
        hasBeenHit_ = false;
        weapon_.reset();
    }//if
}

void Player::poison()
{

}

int Player::getHitPoints() const
{
    return 0;
}
